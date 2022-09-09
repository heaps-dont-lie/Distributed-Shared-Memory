#include "psu_comms.h"
#include "psu_lock.h"
#include "psu_dsm_system.h"

int a __attribute__ ((aligned (4096)));
int b __attribute__ ((aligned (4096)));

int main(int argc, char* argv[]) {

	if (argc != 2) {
                printf("Please give the total number of nodes participating, including the directory node\n");
                exit(0);
        }

        N = atoi(argv[1]);

	printf("Address of a, Size of a = %x, %d\n", &a, sizeof(a));
        printf("Address of b, Size of b = %x, %d\n", &b, sizeof(b));

        psu_dsm_register_datasegment(&a, 2*4096);

	psu_init_lock(0);

	psu_mutex_lock(0);
	a++;
	printf("***********a = %d***********\n", a);
	psu_mutex_unlock(0);

	psu_mutex_lock(0);
        a++;
        printf("***********a = %d***********\n", a);
        psu_mutex_unlock(0);  

	psu_mutex_lock(0);
        a++;
        printf("***********a = %d************\n", a);
        psu_mutex_unlock(0);

        psu_mutex_lock(0);
        a++;
        printf("***********a = %d************\n", a);
        psu_mutex_unlock(0);
	
	/* Wainting for the server thread to finish */
    	//pthread_join(srvr_thread, NULL);
    	finish();

	return 0;
}
