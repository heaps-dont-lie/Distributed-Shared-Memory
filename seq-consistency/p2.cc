//Program 2 of the sequential consistency check

#include "psu_comms.h"
#include "psu_dsm_system.h"

int a __attribute__ ((aligned (4096)));
int b __attribute__ ((aligned (4096)));
int c __attribute__ ((aligned (4096)));

int main(int argc, char* argv[])
{
	if (argc !=2 ) {
                printf("Specify the number of nodes participating (Inluding DIRECTORY NODE)\n");
                exit(0);
        }

        N = atoi(argv[1]);

	psu_dsm_register_datasegment(&a, 4096*3);
	while (a == 0);
	b = 1;
	finish();
	return 0;
}
