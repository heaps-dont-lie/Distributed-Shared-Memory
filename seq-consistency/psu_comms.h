#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mutex>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <signal.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>
#include <bits/stdc++.h>
#include <grpcpp/grpcpp.h>
#include "psu_dsm_var.h"
#include "psu_mtx_var.h"
#include "psu_dirn_func.h"
#include "communicate.pb.h"
#include "communicate.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using communicate::DistributedSystemsService;
using communicate::ReqLock;
using communicate::Ack;
using communicate::Var_Ds_Info;
using communicate::Node_state_info;
using communicate::GetInfo;

using namespace std;

pthread_t srvr_thread;
bool server_initiated = false;

char HOSTNAME[255];

/* Function Declarations */
st_trans* do_state_trans_dirn(unsigned int tag, unsigned int effect, unsigned int node_id);
st_trans* do_state_trans_node(unsigned int tag, unsigned int effect, unsigned int node_id);
void Run(int op_flag, char* hostname_server, void* args);

/***********************************SERVER************************************************************************
 *  *                      Handling the server/service in this region of the code.
 *   * ***************************************************************************************************************/
class DistributedSystemsImplementation final : public DistributedSystemsService::Service {

/**************************Distributed Mutual Exclusion*****************************************************************/
        Status recv_request (ServerContext* context, const ReqLock* request, Ack* reply) override {
                unsigned int seq_num = request->seq_num();
                unsigned int node_num = request->node_num();
                //highestseqnum = (highestseqnum < lockno) ? lockno : highestseqnum;
                mtx.lock();
		highestseqnum = (highestseqnum < seq_num) ? seq_num : highestseqnum;
                //May have to put internal lock here for local threads
                if (((req_critical_sec) && (seq_num > myseqnum)) || ((req_critical_sec) && (seq_num == myseqnum) && (node_num > mynodeid))) { //Defer the reply.
                        reply_deferred[node_num] = true;
                        reply->set_ack(0);
                }
                else { //Send the reply immiediately
                        reply->set_ack(1);
                }
                mtx.unlock();
                return Status::OK;
        }

        Status recv_reply (ServerContext* context, const Ack* request, Ack* reply) override {
                unsigned int ack = request->ack();
                if (ack) {
			mtx1.lock();
                        outs_rply_cnt = outs_rply_cnt - 1;
			mtx1.unlock();
		}
                reply->set_ack(1);
                return Status::OK;
        }

        Status roll_call (ServerContext* context, const Ack* request, Ack* reply) override { //To ensure the server is up and running
                unsigned int ack = request->ack();
                reply->set_ack(1);
                return Status::OK;
        }
/************************************************************END OF DISTRIBUTED MUTUAL EXCLUSION*********************************************/

/**********************************************************DISTRIBUTED MEMORY SERVICES********************************************************/
	Status recv_page_req (ServerContext* context, const Ack* request, Ack* reply) override { //Basic Implementation for basic purposes. For Debugging Purposes Only.
		unsigned int ack = request->ack();
		reply->set_ack(1);
		printf("SERVICING THE PAGING REQUEST..............................\n");
		return Status::OK;
	}

	Status recv_var_node (ServerContext* context, const Var_Ds_Info* request, Ack* reply) override {
		reply->set_ack(1);
		unsigned int tag = request->tag();
		unsigned int node_id = request->node_id();
		/* Locking before checking or/and updating the directory */
		pthread_mutex_lock(&dir_lck);
		if (check_dir_entry(tag, node_id)) {
			printf("PAGE ALREADY IN THE DIRECTORY, added 1 bit to the requesting node -> %lu, %u, %u, %u, %u\n", request->psu_ds_start(), request->tag(), request->curr_page(), request->tot_pages(), request->node_id());
			/* Unlock */
			pthread_mutex_unlock(&dir_lck);
                	return Status::OK;
		}
		push_pg_entry_dir(tag, node_id);
		printf("PUSHED THE FOLLWING CONTENTS: %lu, %u, %u, %u, %u\n", request->psu_ds_start(), request->tag(), request->curr_page(), request->tot_pages(), request->node_id());
		/* Unlock */
		pthread_mutex_unlock(&dir_lck);
		return Status::OK;
	}

	Status recv_state_trans_dirn_req (ServerContext* context, const Node_state_info* request, GetInfo* reply) override {
		//reply->set_ack(1);
		//reply->set_req_val(2);
		st_trans* result;
		unsigned int tag = request->tag();
        	unsigned int effect = request->effect();
        	unsigned int node_id = request->node_id();
	 	result = do_state_trans_dirn(tag, effect, node_id);
		if (effect == NRDEX) {	
			for (int i = 0; i < 1024; i++) {
                        	reply->add_pg_rq(result->page[i]);
                	}
		}
		reply->set_page_req(result->page_data);
                reply->set_ack(1);
		free(result);
		return Status::OK;		
	}

	Status recv_state_trans_node_req (ServerContext* context, const Node_state_info* request, GetInfo* reply) override {
		st_trans* result;
		unsigned int tag = request->tag();
                unsigned int effect = request->effect();
                unsigned int node_id = request->node_id();
		result = do_state_trans_node(tag, effect, node_id);
		if (effect == NRDEX) {
			for (int i = 0; i < 1024; i++) {
				//printf("i = %d\n", i);
				reply->add_pg_rq(result->page[i]);
			}
		}
		reply->set_page_req(result->page_data);
		reply->set_ack(1);
		free(result);
		return Status::OK;
	}

	Status recv_ack_wait_dirn (ServerContext* context, const Node_state_info* request, Ack* reply) override {
		unsigned int node_id = request->node_id();
		/* Node "node_id" has done its work and we can now unlock the page. (Note: We might need a lock if there are multiple threads of this node */
		ack_wait[node_id] = 0;
		pthread_mutex_unlock(std::get<2>(std::get<1>(psu_dvar_info[request->tag()-1])));
                reply->set_ack(1);
                return Status::OK;
	}
};

/* Implementing directory node related methods (Not a desirable file to implement these methods tbh......Maybe try to change later)*/
void contact_all_dirn(unsigned int node_id, unsigned int effect, st_trans* args) {

	/* Opening the file that has info of all the nodes */
	std::string hostname_node;
        ifstream myFile ("node_list.txt");

	if (effect == NINV) {
		/* Invalidate all nodes except the requesting node, "node_id". */
		if (myFile.is_open()) {
			for (int i = 0; i < N-1; i++) {
				getline(myFile, hostname_node);
				if ((i == node_id) || !((std::get<0>(psu_dvar_info[args->tag-1]))[i])){
					continue;
				}
				/* Contacting the node to ask it to invalidate the page number, "tag". */
				Run(6, (char*)hostname_node.c_str(), (void*)args);
				/* Invalidating this node */
				(std::get<0>(psu_dvar_info[args->tag-1]))[i] = 0;
			}
			/* Validating the requesting node */
			(std::get<0>(psu_dvar_info[args->tag-1]))[node_id] = 1;
		}
	}

	else if (effect == NRDEX) {
		bool flag = true;
		int hold_val;
		if (myFile.is_open()) {
			for (int i = 0; i < N-1; i++) {
				getline(myFile, hostname_node);
				/* Finding the first node that has the value and contacting it to get the value */
				if ((i != node_id) && ((std::get<0>(psu_dvar_info[args->tag-1]))[i]) && flag)	{
					Run(6, (char*)hostname_node.c_str(), (void*)args);
					hold_val = args->page_data;
					(std::get<0>(psu_dvar_info[args->tag-1]))[i] = 0;
					flag = false;
					args->effect = NINV;
					continue;
				}
				if ((i == node_id) || !((std::get<0>(psu_dvar_info[args->tag-1]))[i]))
                                        continue;
                                /* Contacting the node to ask it to invalidate the page number, "tag". */
				//args->effect = NINV;
				Run(6, (char*)hostname_node.c_str(), (void*)args);
				/* Invalidating this node */
				(std::get<0>(psu_dvar_info[args->tag-1]))[i] = 0;
			}
			/* Validating the requesting node */
                        (std::get<0>(psu_dvar_info[args->tag-1]))[node_id] = 1;
			args->page_data = hold_val;
		}		
	}

	else { /* NREAD */

	}

	myFile.close();
	return;
}

st_trans* do_state_trans_dirn(unsigned int tag, unsigned int effect, unsigned int node_id) {

	/* Preparing the arguments that will be sent to the nodes we are contacting */
        st_trans* args = (st_trans*)malloc(sizeof(st_trans));
        //args->tag = tag;
        args->effect = effect;
        args->node_id = node_id;
        //args->state = 0; Not required

	int i = 0;
	while (i < psu_dvar_info.size()) {
		if (std::get<0>(std::get<1>(psu_dvar_info[i])) == tag) {
			/* Lock the page */
			pthread_mutex_lock(std::get<2>(std::get<1>(psu_dvar_info[i])));
			ack_wait[node_id] = 1; //COULD BE A REASON FOR ERROR
			/* Do the necessary work */
			switch(effect) {
				case NINV:
					/* Invalidate all nodes except the requesting node. */
					args->tag = (unsigned int)(i+1);
					contact_all_dirn(node_id, NINV, args);
					/* Change the directory page state accordingly */
					std::get<1>(std::get<1>(psu_dvar_info[i])) = READ_WRITE;
					break;
				case NRDEX:
					/* Get the current value from the node that has the value and invalidate everyone and validate the requesting node */
					args->tag = (unsigned int)(i+1);
					contact_all_dirn(node_id, NRDEX, args);
					/* Change the directory page state accordingly */
					std::get<1>(std::get<1>(psu_dvar_info[i])) = READ_WRITE;	
					break;
				case NREAD:
					/* Get the current value from the node that has the value and add this node as "1" */
					args->tag = (unsigned int)(i+1);
					contact_all_dirn(node_id, NREAD, args);
					/* Change the directory page state accordingly */
					std::get<1>(std::get<1>(psu_dvar_info[i])) = READ_ONLY;
					break;
			}
			/* Give result (If any) back to the requesting node  --> DONE */		
			/* Change the directory page state accordingly --> DONE in above in SWITCH CASES*/
			/* Wait for the ACK from the requesting node and then UNLOCK --> DONE in rpc service and below*/
			/* Change the bit status for the calling/requesting node --> DONE in contact_all_dirn() */
			/* Unlock the page --> DONE Below*/
			//pthread_mutex_unlock(std::get<2>(std::get<1>(psu_dvar_info[i])));
			/* Done with the loop */
			break;
		}

		else {
			//continue;
		}
		i++;
	}

	return args;
}


/* Implementing node related methods (Not a desirable file to implement these methods tbh......Maybe try to change later) */

void get_page_data(st_trans* args, void* start_addr) {
	for (int i = 0; i < 1024; i++) {
		args->page[i] = *((int*)((unsigned long)start_addr + (unsigned long)(4*i)));
	}

}

st_trans* do_state_trans_node(unsigned int tag, unsigned int effect, unsigned int node_id) {

	/* Preparing the arguments that will be sent to the nodes we are contacting */
        st_trans* args = (st_trans*)malloc(sizeof(st_trans));
        //args->tag = tag;
        //args->effect = effect;
        //args->node_id = node_id;
        //args->state = 0; Not required	
	int i = 0;
	while (i < psu_var_info.size()) {
		if (std::get<1>(psu_var_info[i]) == tag) {
			switch (effect) {
				case NINV:
					args->page_data = 1729;
					std::get<2>(psu_var_info[i]) = IV;
					mprotect((void*)(std::get<0>(psu_var_info[i])), (size_t)4096, PROT_NONE);
					//std::get<2>(psu_var_info[i]) = IV;
					break;
				case NRDEX:
					/* Get the value stored */
					args->page_data = *((int*)(std::get<0>(psu_var_info[i])));
					get_page_data(args, std::get<0>(psu_var_info[i]));
					std::get<2>(psu_var_info[i]) = IV;
					mprotect((void*)(std::get<0>(psu_var_info[i])), (size_t)4096, PROT_NONE);
					//std::get<2>(psu_var_info[i]) = IV;
                                        break;
			}
			break;
		}
		i++;
	}

	return args;
}

void* Run_srvr(void * hostname) {

    std::string address((char*)hostname);
    DistributedSystemsImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
    return NULL;
}

/**********************************************END OF SERVER IMPLEMENTATION********************************************************************************/



/**********************************************************************************************************************************************************
 *  *                                              DISTRIBUTED SYSTEMS CLIENT                                                               
 *   *********************************************************************************************************************************************************/

class DistributedSystemsClient {
    public:
        DistributedSystemsClient(std::shared_ptr<Channel> channel) : stub_(DistributedSystemsService::NewStub(channel)) {}

    int send_request(unsigned int seq_num, unsigned int node_num) {
        ReqLock request;

        request.set_seq_num(seq_num);
        request.set_node_num(node_num);

        Ack reply;

        ClientContext context;

        Status status = stub_->recv_request(&context, request, &reply);

        if(status.ok()){
            return reply.ack();
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

    int send_reply(unsigned int ack) {
        Ack request;

        request.set_ack(ack);

        Ack reply;

        ClientContext context;

        Status status = stub_->recv_reply(&context, request, &reply);

        if(status.ok()){
            return reply.ack();
        } else {
            //std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

    int check_status (unsigned int ack) {
        Ack request;
        request.set_ack(ack);
        Ack reply;
        ClientContext context;

        Status status = stub_->roll_call(&context, request, &reply);

        if(status.ok()){
            return reply.ack();
        } else {
	    //std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

    int request_page (unsigned int ack) {
    	Ack request;
        request.set_ack(ack);
        Ack reply;
        ClientContext context;

        Status status = stub_->recv_page_req(&context, request, &reply);

        if(status.ok()){
            return reply.ack();
        } else {
            //std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

    int grpc_send_var_dir(unsigned long psu_ds_start, unsigned int tag, unsigned int curr_page, unsigned int tot_pages, unsigned int node_id){
	Var_Ds_Info request;
	//Ack request;
	request.set_psu_ds_start(psu_ds_start);
	request.set_tag(tag);
	request.set_curr_page(curr_page);
	request.set_tot_pages(tot_pages);
	request.set_node_id(node_id);
	
	Ack reply;
	
	ClientContext context;
	Status status = stub_->recv_var_node(&context, request, &reply);
	if(status.ok()){
            return reply.ack();
        } 
	else {
	    return -1;
    	}
    }

    int grpc_state_trans_dirn(unsigned int tag, unsigned int effect, unsigned int node_id, st_trans* temp){
	Node_state_info request;
	GetInfo reply;
	request.set_tag(tag);
	request.set_effect(effect);
	request.set_node_id(node_id);

	ClientContext context;
	Status status = stub_->recv_state_trans_dirn_req(&context, request, &reply);

	if(status.ok()){
	    if (effect == NRDEX) {
	    	for (int i = 0; i < reply.pg_rq_size(); i++) {
                        temp->page[i] = reply.pg_rq(i);
            	}
	    }
            return reply.page_req();
        }
        else {
            return -1;
        }
    }

    int grpc_state_trans_node(unsigned int tag, unsigned int effect, unsigned int node_id, st_trans* temp){
        Node_state_info request;
        GetInfo reply;
        request.set_tag(tag);
        request.set_effect(effect);
        request.set_node_id(node_id);

        ClientContext context;
        Status status = stub_->recv_state_trans_node_req(&context, request, &reply);

        if(status.ok()){
	    if (effect == NRDEX) {
	    	for (int i = 0; i < reply.pg_rq_size(); i++) {
                        temp->page[i] = reply.pg_rq(i);
            	}
	    }	
            return reply.page_req();
        }
        else {
            return -1;
        }
    }

    int grpc_send_ack_dirn(unsigned int node_id, unsigned int tag) {
	Node_state_info request;
	Ack reply;
	request.set_node_id(node_id);
	request.set_tag(tag);

	ClientContext context;
        Status status = stub_->recv_ack_wait_dirn(&context, request, &reply);
	if(status.ok()){
            return reply.ack();
        }
        else {
            return -1;
        }
    }	

    private:
        std::unique_ptr<DistributedSystemsService::Stub> stub_;
};


/* 
 * Client trying to contact the server for different purposes
 * OPFLAG = 1 --> Request Mutex Lock
 * OPFLAG = 2 --> Send REPLY to other waiting nodes after done with critical section
 * OPFLAG = 3 --> To check if all the other servers are running or not
 * OPFLAG = 4 --> To contact a particular server
*/
void Run(int op_flag, char* hostname_server, void* args) {
    std::string address(hostname_server);
    DistributedSystemsClient client(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        )
    );

    if (!op_flag) {

        int response;
	lock_req* temp = (lock_req*)args;
        unsigned int seq_num = temp->seq_num;
        unsigned int node_num = temp->node_num;
        response = client.send_request(seq_num, node_num);
        if (response == 1) {
		mtx1.lock();
                outs_rply_cnt = outs_rply_cnt - 1;
		mtx1.unlock();
	}
    }

    else if (op_flag == 1) {
        unsigned int ack = 1;
        client.send_reply(ack);
    }

    else if (op_flag == 2){
        int response;
        unsigned int ack = 1;
	//int retry = 50;
        while (true) {
            response = client.check_status(ack);
            if (response == -1)
               continue;
            else
               break;
        }
    }

    else if (op_flag == 3) {
	//pass
	int response;
        unsigned int ack = 1;
	client.request_page(ack);
    }

    else if (op_flag == 4) {
	int response;
	ds_info* temp = (ds_info*)args;
	unsigned long psu_ds_start = temp->ds_start;
	unsigned int tag = temp->tag;
	unsigned int curr_page = temp->curr_pg;
	unsigned int tot_pages = temp->tot_pg;
	unsigned int node_id = temp->node_id;
	unsigned int ack = 1;
        //client.request_page(ack);
        response = client.grpc_send_var_dir(psu_ds_start, tag, curr_page, tot_pages, node_id);
    }

    else if (op_flag == 5) {
	int response;
	st_trans* temp = (st_trans*)args;
	unsigned int tag = temp->tag;
	unsigned int effect = temp->effect;
	unsigned int node_id = temp->node_id;
	response = client.grpc_state_trans_dirn(tag, effect, node_id, temp);
	if (effect == NRDEX)
	   temp->page_data = response;
    }

    else if (op_flag == 6) {
	int response;
	st_trans* temp = (st_trans*)args;
        unsigned int tag = temp->tag;
        unsigned int effect = temp->effect;
        unsigned int node_id = temp->node_id;
        response = client.grpc_state_trans_node(tag, effect, node_id, temp);
        if (effect == NRDEX)
	   temp->page_data = response;
    }

    else {
	int response;
        st_trans* temp = (st_trans*)args;
        unsigned int node_id = temp->node_id;
	unsigned int tag = temp->tag;
	response = client.grpc_send_ack_dirn(node_id, tag);
    }

    return;
}

void psu_init_host()
{
  char buffer[255];
  std::string port = ":5012";
  int ret; 
  if ((ret = gethostname(buffer, sizeof(buffer))) == -1) {
    perror("gethostname");
    exit(1);
  }
  strcpy(HOSTNAME, buffer);
  strcat(HOSTNAME, (char*)port.c_str());
  printf("Hostname: %s\n", HOSTNAME);
}

/* To contact a particular node */
void contact_node(char* hostname_server) {
	Run(3, hostname_server, NULL);
        return;
}

/* To check if all the other nodes are up and running */
void srvr_check(){
        std::string hostname_server;
        ifstream myFile ("node_list.txt");
        if (myFile.is_open()) {
		int i = 0;
                while (i < N-1) {
			getline(myFile, hostname_server);
                        Run(SRVR_CHK, (char*)hostname_server.c_str(), NULL);
			i++;
                }
        }
        myFile.close();
        return;
}

unsigned int get_mynodeid() {
	std::string hostname_node;
	unsigned int nodeid;
	unsigned int i;
	ifstream myFile ("node_list.txt");
        if (myFile.is_open()) {
		unsigned int i = 0;
		while (i < N) {
			getline(myFile, hostname_node);
			if (strcmp((char*)hostname_node.c_str(), HOSTNAME) == 0) {
				nodeid = i;		
				break;
			}
			i++;
		}
	}
	myFile.close();
	return nodeid;	
}

void initiate_server() {
	//pthread_t srvr_thread;
        if (!server_initiated) {
		psu_init_host();
        	mynodeid = get_mynodeid(); //(unsigned int)atoi(argv[1]);
		printf("mynodeid = %u\n", mynodeid);
                int t = pthread_create(&srvr_thread, NULL, Run_srvr, (void*)HOSTNAME);
                server_initiated = true;
        }
	srvr_check();
	cout<<"All servers are up and runnning....\n";
        return;
}

void finish() {
	while(true);
	return;
}

/**********************************************************END OF CLIENT IMPLEMENTAION*******************************/
