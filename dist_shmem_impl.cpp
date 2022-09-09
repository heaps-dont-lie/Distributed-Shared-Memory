#include "psu_comms.h"
//#include "psu_lock.h"
#include <signal.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>

static char* buffer;


static void handler (int sig, siginfo_t *si, void *unused) {
	cout<<"Inside the signal handler. Now contacting the server of directory Node.......\n";
	std::string hostname_server = "e5-cse-135-32.cse.psu.edu:5000";
	contact_node((char*)hostname_server.c_str());
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	int pagesize;
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sigaction(SIGSEGV, &sa, NULL);

	pagesize = sysconf(_SC_PAGE_SIZE);
	
	buffer = (char*)memalign(pagesize, 4*pagesize);
	mprotect(buffer, pagesize, PROT_NONE);
	memset(buffer, 1, pagesize);
	cout<<"DONE......\n";
	return 0;
}
