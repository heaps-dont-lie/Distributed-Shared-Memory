#include "psu_comms.h"

int main (int argc, char* argv[]) {
	psu_init_host();
	Run_srvr((void*)HOSTNAME);
	return 0;
}
