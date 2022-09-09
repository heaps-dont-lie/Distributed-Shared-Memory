#define LOCK 0
#define UNLOCK 1
#define SRVR_CHK 2
#define MISC 3

/*------------------------------------
 *  *      SHARED DATABASE
 *   * -----------------------------------*/

/*CONSTANTS--------*/
int N = 4 ;
unsigned int mynodeid;

/*INTEGERS----------*/
unsigned int myseqnum;
unsigned int highestseqnum;
unsigned int outs_rply_cnt;
/*BOOLEAN-----------*/
bool req_critical_sec;

/* Can work for 4 nodes excluding the one directory node */ 
bool reply_deferred[4];

/*BINARY SEMAPHORES/MUTEX LOCKS FOR THIS NODE---*/
std::mutex mtx;
std::mutex mtx1;

/* Struct for the lock */
typedef struct lock_req {
	unsigned int seq_num;
	unsigned int node_num;
} lock_req;
