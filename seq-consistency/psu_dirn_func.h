#include <pthread.h>
#include <vector>
#include <tuple>

/* State of the directory at page level */
#define READ_ONLY 0
#define READ_WRITE 1

/*
 *The following GV stores the necessary var info for the directory node
 */
typedef std::tuple<std::vector<unsigned int>, std::tuple<unsigned int, unsigned int, pthread_mutex_t*>> psu_dir_tup;
typedef std::vector<psu_dir_tup> psu_dir_var_info;
psu_dir_var_info psu_dvar_info;

/* Pthread Mutex lock for updating the directory as a whole (like, checking the directory for any tag or adding a new tag)*/
pthread_mutex_t dir_lck = PTHREAD_MUTEX_INITIALIZER;

/* Debugging purposes */
void print() {
	size_t size = psu_dvar_info.size();
        for (size_t i = 0; i < size; i++) {
               printf("Bit Stat N1 = %u, Bit Stat N2 = %u, Bit Stat N3 = %u, Tag = %u, State = %d\n", ((std::get<0>(psu_dvar_info[i]))[0]), (std::get<0>(psu_dvar_info[i])[1]), ((std::get<0>(psu_dvar_info[i]))[2]), std::get<0>(std::get<1>(psu_dvar_info[i])), std::get<1>(std::get<1>(psu_dvar_info[i])));
	}
	return;
}

bool check_dir_entry(unsigned int tag, unsigned int node_id) {
        size_t size = psu_dvar_info.size();
	for (size_t i = 0; i < size; i++) {
		if (std::get<0>(std::get<1>(psu_dvar_info[i])) == tag) {
			std::get<0>(psu_dvar_info[i])[node_id] = 1;
			return true;
		}
	}
        return false;
}
void push_pg_entry_dir(unsigned int tag, unsigned int node_id) {
        //add new page in the directory
        std::vector<unsigned int> init_vec;
	for (int i = 0; i < N-1; i++) {
		if (i == node_id)
			init_vec.push_back(1);
		else
			init_vec.push_back(0);
	}
	pthread_mutex_t* mtx = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx, NULL);
        psu_dvar_info.push_back(psu_dir_tup(init_vec, std::tuple<unsigned int, unsigned int, pthread_mutex_t*>(tag, READ_ONLY, mtx)));
	//print();
        return;
}
