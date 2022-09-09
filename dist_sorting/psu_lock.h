//#include "psu_comms.h"

using namespace std;

/*Declaring Functions---------------------*/
void psu_init_gv();
void psu_init_lock(unsigned int lockno);
void psu_mutex_lock(unsigned int lockno);
void psu_mutex_unlock(unsigned int lockno);

void psu_mutex_lock(unsigned int lockno) {
	//srvr_check();
	//cout<<"All servers are up and running................\n";
        std::string hostname_server;
        ifstream myFile ("node_list.txt");
	lock_req* args = (lock_req*)malloc(sizeof(lock_req));
	mtx.lock();
        myseqnum = highestseqnum + 1;
        outs_rply_cnt = N-2;
        req_critical_sec = true;
	args->seq_num = myseqnum;
	args->node_num = mynodeid; 
        mtx.unlock();
        if (myFile.is_open()) {
                for (int i = 0; i < N-1; i++) {
                        getline(myFile, hostname_server);
                        if (strcmp((char*)hostname_server.c_str(), HOSTNAME) == 0) {
                                continue;
			}
			sleep(1);	
                        Run(LOCK, (char*)hostname_server.c_str(), (void*)args); //Have to send all the addreses of the nodee to ask for locks. Use node_add.txt file. 
                }
                while (outs_rply_cnt != 0) {  //Wait for all the other N-1 nodes to respond. Can also use semaphore for this variable. Or Condition Variable.
			sleep(1);
		}
        }
	free(args);
        myFile.close();
        return;
}

void psu_mutex_unlock(unsigned int lockno) {
        std::string hostname_server;
	mtx.lock();
        req_critical_sec = false;
	mtx.unlock();
        ifstream myFile ("node_list.txt");
        if (myFile.is_open()) {
                for (int i = 0; i < N-1; i++) {
                        getline(myFile, hostname_server);
                        if (reply_deferred[i]) {
                                reply_deferred[i] = false;
				sleep(1);
                                Run(UNLOCK, (char*)hostname_server.c_str(), NULL);
                        }
                }
        }
        myFile.close();
        return;
}

void psu_init_mtx_gv() {
	highestseqnum = 0;
	for(int i = 0; i < N-1; i++) {
		reply_deferred[i] = false;
	}
	return;
}

void psu_init_lock(unsigned int lockno) {
	psu_init_mtx_gv();
	initiate_server();
	return;
}
