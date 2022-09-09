#include "psu_comms.h"
#include "psu_dsm_system.h"
#include "psu_lock.h"

using namespace std;
#define COUNT 4*4096
int global_array[COUNT] __attribute__ ((aligned (4096)));
int partition_num[1024] __attribute__ ((aligned (4096)));

int logbase2(int n);
int partitionn_num(int id, int level, int num);
void partial_sort(int process_num, int total_processes_num);
void merge(int process_num, int total_processes_num);

void wait_partition(int a)
{
	psu_mutex_lock(0);
	partition_num[a]++;
	psu_mutex_unlock(0);
	
	while(partition_num[a] < 2);

	return;
}

void initialize()
{
	time_t t;
	srand((unsigned) time(&t));
	for(int i = 0; i<COUNT; i++)
	{
		global_array[i] = rand()%500;
	}

}
int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("Format is <sort> <Process_num> <total_num_Proceses>\n");
		return 0;
	}

	N = atoi(argv[2]) + 1;

	psu_dsm_register_datasegment(&global_array, COUNT*sizeof(int)+(1024*sizeof(int)));
	psu_init_lock(0);
	int process_num;
	int total_processes_num;
	
	process_num = atoi(argv[1]);
	total_processes_num = atoi(argv[2]);

	if(process_num == 0)
	{
		initialize();
		psu_mutex_lock(0);
	 	partition_num[0]++;
		psu_mutex_unlock(0);
	}
	else
	{
		while(partition_num[0] < 1);
	}
	partial_sort(process_num, total_processes_num);

	//Do merging based on the process_num

	int p = process_num;
	int n = total_processes_num;
	//Do merging based on the lock for 2 processes
	int i = 0;
	while((1<<i) < n)
	{
		if(p % (1<<i) == 0)
		{
			merge(p/(1<<i),n/(1<<i));
			int b_id = partitionn_num(p,i,n);
			wait_partition(b_id);
		}
		++i;
	}

	if(process_num == 0)
	{
		merge(0,1);
		for(int i = 0; i<COUNT; i++)
			std::cout<<global_array[i]<<"\t";
			//CAT it to a file
	}
	printf("\nFinish\n");
	finish();
	return 0;
}

void partial_sort(int process_num, int total_processes_num)
{
	//choose the offset based on the process_num and total_processes_num
	int offset = process_num * (COUNT/total_processes_num);
	int size = COUNT/total_processes_num;
	int temp;
	
	for (int i = 0; i < size -1 ; i++)
	{	
		for(int j = 0 ; j < size-i-1; j++)
		{
			if(global_array[j+offset] > global_array[j+1+offset])
			{
				temp = global_array[j+offset];
				global_array[j+offset] = global_array[j+1+offset];
				global_array[j+1+offset] = temp;
			}	
		}
	}
	return;
}

void merge(int process_num, int total_processes_num)
{
	int offset = process_num * (COUNT/total_processes_num);
	int size = COUNT/total_processes_num/2;

	int* a = new int[size*2];
	int i = 0;
	int j = 0;
	int k = 0;
	while(i < size && j < size)
	{
		if(global_array[i+offset] < global_array[j+offset+size])
		{
			a[k++] = global_array[i+offset];
			i++;
		}
		else
		{
			a[k++] = global_array[j+offset+size];
			j++;	
		}
	}

	if(j == size)
	{
		while(i<size)
		{
			a[k++] = global_array[i+offset];
			i++;
		}
		
	}
	else
	{	while(j<size)
		{
			a[k++] = global_array[j+offset+size];
			j++;
		}
	}

	for(int i=0; i<size*2; ++i)
		global_array[i+offset] = a[i];

	delete [] a;

}


int logbase2(int n)
{
	int i = 0;
	while(n>1)
	{
		i++;
		n=n/2;
	}
	return i;
}

int partitionn_num(int id, int level, int num)
{
	int k = logbase2(num)-level-1;
	int s_k = 1 << k;
	int idx = id/(1 << (level+1));
	return s_k + idx;
}
