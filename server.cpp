#include <string>
#include <algorithm>
#include <dist_mutex_lock.h>
#include <grpcpp/grpcpp.h>
#include "communicate.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using communicate::DistributedMutualExclusion;
using communicate::ReqLock;
using communicate::Ack;

class DistributedMutualExclusionImplementation final : public DistributedMutualExclusion::Service {
	Status recv_request(ServerContext* context, const ReqLock* request, Ack* reply) override {
        	int lockno = request->lockno();
        	int nodeno = request->nodeno();
		highestseqnum = max(highestseqnum, lockno);
		//May have to put internal lock here for local threads
		if (((req_critical_sec) && (lockno > myseqnum)) || ((lockno == myseqnum) && (nodeno > mynodeid))) {
			reply_deferred[nodeno-1] = 1;
			reply->set_result(0);
		}

		else {
			reply->set_result(1);
		}

        	return Status::OK;
    	}

	Status recv_reply(ServerContext* context, const Ack* request, Ack* reply) override {
		int ack = request->ack();
		if (ack)
			outs_rply_cnt = outs_rply_cnt - 1;
		reply->set_result(1);
                return Status::OK;
        }
};

void Run() {
    std::string address("0.0.0.0:5000");
    DistributedMutualExclusionImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    Run();

    return 0;
}

