/* CAUSE */
#define RO 0
#define RW 1
#define IV 2

/* EFFECT */
#define PREAD 3
#define PWRITE 4
#define NREAD 5
#define NRDEX 6
#define NINV 7

/* 
 * This vector stores the necessary information of declared variables 
 * (right now implementing global vars) in order to retrieve information
 * from the directory 
*/
typedef std::vector<std::tuple<void*, unsigned int, unsigned int>> psu_localh_var_info;
psu_localh_var_info psu_var_info;

/*
 The following GV stores the necessary var info for the directory node
*
typedef std::tuple<std::vector<bool>, std::tuple<int, pthread_mutex_t*>> psu_dir_tup;
typedef std::vector<psu_dir_tup> psu_dir_var_info;
psu_dir_var_info psu_dvar_info;
*/
/* Directory Node address (Fixed)*/
std::string directory_node_addr = "e5-cse-135-19.cse.psu.edu:5011";

/* Stores the most recent tag given to the most recent registered variable. Also used to calculate the next tag. */
unsigned int var_tags = 0;

/* Array to keep track of the last ACK */
int ack_wait[3] = {0};

/* The following struct is used to send as an argument to the Run command */
typedef struct ds_info {
        unsigned long ds_start;
        unsigned int tag;
        unsigned int curr_pg;
        unsigned int tot_pg;
	unsigned int node_id;
} ds_info;

/* Struct for state transition. Input for the Run() */
typedef struct st_trans {
	unsigned int tag;
	unsigned int state;
	unsigned int effect;
	unsigned int node_id;
	/* maybe used to get the recent value of a variable */
	int page_data;
	int page[1024]; 
} st_trans; 
