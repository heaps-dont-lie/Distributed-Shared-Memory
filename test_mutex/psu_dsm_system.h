//#include "psu_comms.h"

/* CAUSE
#define RO 0
#define RW 1
#define IV 2

/EFFECT 
#define PREAD 3
#define PWRITE 4
#define NRERAD 5
#define NRDEX 6
#define NINV 7*/

/* defining the signal.h struct here as a GV & a global bool variable to see if the SEG handler is initialized*/
struct sigaction sa;
/* Raising a falg as soon as a signal handler is initialized */
bool seghand_flag = false;


unsigned long nearest_multiple(unsigned long p, unsigned long q) {
	unsigned long quo; 
	quo = p/q;
	return quo*q;
}

/* Get the details of the variable at the segfault address */
void get_var_info(void* addr, st_trans* args) {
	int i = 0;
	while (i < psu_var_info.size()) {
		if (std::get<0>(psu_var_info[i]) == addr || (void*)nearest_multiple((unsigned long)addr, (unsigned long)4096) == std::get<0>(psu_var_info[i])) {
			args->tag = std::get<1>(psu_var_info[i]);
			args->state = std::get<2>(psu_var_info[i]);
			break;
		}
		i++;
	}
	return;
}	

/* TO START NEXT: Implement a SEGFAULT Handler */
void put_page_data(void* base_addr, st_trans* args) {
	int* buff = (int*)base_addr;
	for (int i = 0; i < 1024; i++) {
		buff[i] = args->page[i];
	} 
}


static void seg_handler(int sig, siginfo_t* si, void* unused) {
	//printf("GOT SIGSEGV at address: %x\n", si->si_addr);
	st_trans* args = (st_trans*)malloc(sizeof(st_trans));
	args->node_id = mynodeid;
	get_var_info((void*)si->si_addr, args); //set the args.
	switch(args->state) {
		case RO:					//P-WRITE(NINV)
			args->effect = NINV;
			Run(5, (char*)directory_node_addr.c_str(), (void*)args);
			mprotect((int*)(si->si_addr), (size_t)4096, PROT_WRITE);
			std::get<2>(psu_var_info[args->tag-1]) = RW;
			break;
			//change state to RW
		case IV:					//P-WRITE(NRDEX) Here I am directly taking this node to the read write state. Not implementing PREAD
			args->effect = NRDEX;
			Run(5, (char*)directory_node_addr.c_str(), (void*)args);
			mprotect((int*)nearest_multiple((unsigned long)si->si_addr, (unsigned long)4096), (size_t)4096, PROT_WRITE);
			*((int*)(si->si_addr)) = args->page_data;
			put_page_data((void*)nearest_multiple((unsigned long)si->si_addr, (unsigned long)4096), args);
			//*((int*)(si->si_addr)) = args->page[0];
			std::get<2>(psu_var_info[args->tag-1]) = RW;
			break;
			//change state to RW
	}
	/* Send an ACK so that directory node will release its lock */
	Run(7, (char*)directory_node_addr.c_str(), (void*)args);
	free(args);
	//exit(EXIT_FAILURE);
}

void segfault_handler_init() {
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = seg_handler;
	sigaction(SIGSEGV, &sa, NULL);
	seghand_flag = true;
	return;
}

void send_var_dir(unsigned long psu_ds_start, unsigned int tag, size_t curr_page, size_t tot_pages) {
	ds_info* args = (ds_info*)malloc(sizeof(ds_info));
	//doing long for the moment as dont know how to make a 32 bit compiler
	args->ds_start = psu_ds_start;
	args->tag = tag;
	args->curr_pg = curr_page;
	args->tot_pg = tot_pages;
	args->node_id = mynodeid;
	Run(4, (char*)directory_node_addr.c_str(), (void*)args);
	free(args);
	return;
}

void psu_dsm_register_datasegment(void* psu_ds_start, size_t psu_ds_size) {

	/* Initiating all the servers */
	initiate_server();

	/* Improvement to be made: Here I am not checking that whether a variable has already been declared or not */
	size_t num_pages = size_t(psu_ds_size/4096);
	
	/* Here and at any registering event I need to check if a SEGFAULT handler has been initialized or not */
	if (!seghand_flag)
		segfault_handler_init();

	/* Initially revoking WRITE access to each nodes. Initially GV is set to 0 for evryone hence READ is fine. */
	mprotect((void*)psu_ds_start, psu_ds_size, PROT_READ);

	/* Registering the declared GV in the directory at the directory node (DN) */
	for (size_t i = 0; i < num_pages; i++) {
		var_tags++;
		void* temp = (void*)((unsigned long)psu_ds_start + (unsigned long)(4096*i));
		//mprotect((void*)temp, (size_t)4096, PROT_READ);
		/* Pushing the necessary info of GV at the local node before sending it to the directory server */
		psu_var_info.push_back(tuple<void*, unsigned int, unsigned int>(temp, var_tags, RO));

		//printf("%x, %u\n", get<0>(psu_var_info[i]), get<1>(psu_var_info[i]));

		/* Now here we will send the GV info to the directory node one-by-one */
		send_var_dir((unsigned long)psu_ds_start, var_tags, i+1, num_pages);
		printf("Added Page number %d to the local node directory\n", var_tags);
	}
	// Like srvr_check() keep checking the directory 
	//printf("size = %d\n", psu_var_info.size());
	sleep(10);
}
