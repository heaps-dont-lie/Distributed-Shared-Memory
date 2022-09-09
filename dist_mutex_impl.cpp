#include "psu_lock.h"
	
int main(int argc, char* argv[]){
    pthread_t srvr_thread;
    psu_init_mtx_gv();
    if (argc != 2) {
	std::cout<<"Missing inputs\n";
	return 0;
    }
    mynodeid = (unsigned int)atoi(argv[1]);
    psu_init_host();
    int t = pthread_create(&srvr_thread, NULL, Run_srvr, (void*)HOSTNAME);

    /* To check if all the other nodes are listening or not */
    srvr_check(); 
    std::cout<<"All Servers are up and running........\n";
    
    /* Distributed Mutual Exclusion */
    psu_init_lock(highestseqnum);
    psu_mutex_lock(myseqnum);
      //Some Critical section
    std::cout<<"Print the critical section\n";
    std::cout<<"MY SEQ # = "<<myseqnum<<"\tMY NODE ID = "<<mynodeid<<"\n";   
    psu_mutex_unlock(myseqnum); //not too sure about the argument

    /* Wainting for the server thread to finish */
    pthread_join(srvr_thread, NULL);

    return 0;
}
