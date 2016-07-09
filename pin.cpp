#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include "cpucounters.h"
#include <time.h>
#include <sched.h>
#include <math.h>

#define EPSILON 0.2
#define setMark(address) ((node_lf *)((uintptr_t)address | 2))
#define setFlag(address) ((node_lf *)((uintptr_t)address | 1))
#define getMark(address) ((int)((uintptr_t)address & 0x00000002) == 2 ?1:0)
#define getFlag(address) ((int)((uintptr_t)address & 0x00000001))
typedef struct node
{
	int data;
	struct node * next;
	struct node * backlink;
}node_lf;

struct list
{
	node_lf * head;
	node_lf * (*init)();
	int (*insert)(int k,node_lf* head);
	int (*delete_node)(int,node_lf *);
	void (*print)(node_lf *);
	void (*destructor)(node_lf *);
};
typedef struct list * List;
typedef struct searchfrom
{
	node_lf * current;
	node_lf * next;
}return_sf;

typedef struct csArg
{
	int * node;
}cs_arg;

typedef struct return_tryFlag
{
	node_lf * node;
	int result;
}return_tf;

void HelpFlagged(node_lf * prev, node_lf * del_node);

/*node_lf * setMark(node_lf * p)
{
    return (node_lf *)((uintptr_t)p | 2);
}
node_lf * setFlag(node_lf * p)
{
    return (node_lf *)((uintptr_t)p | 1);
}
int getMark(node_lf * p)
{
	int r = (int)((uintptr_t)p & 0x00000002);
	if(r == 2)
		return 1;
	return r;
}
int getFlag(node_lf * p)
{
	return (int)((uintptr_t)p & 0x00000001);
}*/

node_lf * getNodeAddress(node_lf * p)
{
	return (node_lf * )((uintptr_t)p & (-4));
}


node_lf * constructArgs(node_lf * node, int mark, int flag)
{
	node_lf * temp = getNodeAddress(node);
	if(mark == 1)
		(temp) = setMark(temp);
	if(flag == 1)
		(temp) = setFlag(temp);
	return temp;
}

void HelpMarked(node_lf * prev, node_lf * del_node)
{
	node_lf * next = getNodeAddress(del_node)->next;

	node_lf * del = constructArgs(del_node,0,1);
	node_lf * next_node = constructArgs(next,0,0);
	//SystemCounterState before_sstate = getSystemCounterState();
	__sync_val_compare_and_swap ((unsigned long long *)&(getNodeAddress(prev)->next), (unsigned long long)del, (unsigned long long)next_node);
	//SystemCounterState after_sstate = getSystemCounterState();
	/*std::cout << "\nInstructions per clock:" << getIPC(before_sstate,after_sstate) << std::endl;
	std::cout << "\nBytes read:" << getBytesReadFromMC(before_sstate,after_sstate);
	std::cout << "\nL2 Misses:" << getL2CacheMisses(before_sstate,after_sstate);
	std::cout << "\nL2 HIts:" << getL2CacheHits(before_sstate,after_sstate)<< "\n";*/
	free(getNodeAddress(del_node));

}

return_sf * SearchFrom(int k,node_lf * curr)
{
	return_sf *s = (return_sf *)malloc(sizeof(return_sf));
	node_lf * next = curr->next;
	while(getNodeAddress(next)->data <= k)
	{
		while(getMark(next) == 1 && (getMark(curr) == 0 || getNodeAddress(curr)->next != getNodeAddress(next)))
		{
			if(getNodeAddress(curr)->next == getNodeAddress(next))
			{
				HelpMarked(curr,next);
			}
			next = getNodeAddress(curr)->next;
		}
		if(getNodeAddress(next)->data <= k)
		{
			curr = next;
			next = getNodeAddress(curr)->next;
		}

	}
	s->current = curr;
	s->next = next;
	return s;
}

void TryMark(node_lf * del_node)
{
	node_lf * next;
	node_lf * result;
	do
	{
		next = getNodeAddress(del_node)->next;

		node_lf * next_node = constructArgs(next,0,0);
		node_lf * next_node1 = constructArgs(next,1,0);

		result = (node_lf *)__sync_val_compare_and_swap((unsigned long long *)&(getNodeAddress(del_node)->next),
														(unsigned long long)(next_node),(unsigned long long)(next_node1));

		if(getMark(result) == 0 && getFlag(result) == 1)
			HelpFlagged(del_node,result);
	}while(getMark(getNodeAddress(del_node)->next) != 1);
}

void HelpFlagged(node_lf * prev, node_lf * del_node)
{
	getNodeAddress(del_node)->backlink = prev;
	if(getMark(getNodeAddress(del_node)->next) == 0)
		TryMark(del_node);
	HelpMarked(prev,del_node);
}

int insert(int k, node_lf * head)
{
	return_sf * s = SearchFrom(k,head);
	node_lf * prev;
	node_lf * next;
	node_lf * prev_succ;
	prev = s->current;
	next = s->next;
	free(s);
	if(getNodeAddress(prev)->data == k)
		return -1;
	node_lf * newNode = (node_lf *)malloc(sizeof(node_lf));
	newNode->data = k;
	while(1)
	{
		prev_succ = getNodeAddress(prev)->next;
		if(getFlag(prev_succ) == 1)
			HelpFlagged(prev,getNodeAddress(prev_succ)->next);
		else
		{
			newNode->next = next;

			node_lf * next_node = constructArgs(next,0,0);
			node_lf * new_Node = constructArgs(newNode,0,0);

			node_lf * result = (node_lf *)__sync_val_compare_and_swap((unsigned long long *)&(getNodeAddress(prev)->next),
																		(unsigned long long)(next_node),(unsigned long long)(new_Node));

			if(result == next)// || next == NULL)
			{
				return 0;
			}
			else
			{
				if(getFlag(result) == 1)
					HelpFlagged(prev,(result)->next);
				while(getMark(prev) == 1)
					prev = getNodeAddress(prev)->backlink;
			}

		}
		s = SearchFrom(k,prev);
		if(getNodeAddress(s->current)->data == k)
		{
			free(newNode);
			free(s);
			return -1;
		}
	}
	free(s);
	//return 0;
}

return_tf * TryFlag(node_lf * prev, node_lf * target)
{
	return_tf * r = (return_tf *)malloc(sizeof(return_tf));
	while(1)
	{
		if(getNodeAddress(prev)->next == target && getMark(getNodeAddress(prev)->next) == 0 && getFlag(getNodeAddress(prev)->next) == 1) // Already Flagged. Some other process would delete_node it.
		{
			r->node = prev;
			r->result = 0;
			return r;
		}
		node_lf * target_node = constructArgs(target,0,0);
		node_lf * target_node_new = constructArgs(target,0,1);

		node_lf * result = (node_lf *)__sync_val_compare_and_swap((unsigned long long *)&(getNodeAddress(prev)->next),
																	(unsigned long long)(target_node),(unsigned long long)(target_node_new));
		if(result == target && getMark(result) == 0 && getFlag(result) == 0)
		{
			r->node = prev;
			r->result = 1;
			return r;
		}
		if(result == target && getMark(result) == 0 && getFlag(result) == 1)
		{
			r->node = prev;
			r->result = 0;
			return r;
		}
		while(getMark(getNodeAddress(prev)->next) == 1)
			prev = getNodeAddress(prev)->backlink;
	}
	return_sf * s = SearchFrom((getNodeAddress(target)->data) - EPSILON,  prev);
	if(s->next != target)
	{
		r->node = NULL;
		r->result = 0;
		free(s);
		return r;
	}
	free(s);
}

int delete_node(int k, node_lf * head)
{
	return_sf * s = SearchFrom(k - EPSILON,head);
	node_lf * prev = s->current;
	node_lf * del = s->next;
	free(s);
	if(getNodeAddress(del)->data != k)
		return -1;
	return_tf * tf = TryFlag(prev, del);
	prev = tf->node;
	if(prev != NULL)
		HelpFlagged(prev, del);
	if(tf->result == 0)
	{
		free(tf);
		return -1;
	}
	free(tf);
	return 1;
}

node_lf * init_LF_list()
{
	node_lf * head = (node_lf *)malloc(sizeof(node_lf));
	node_lf * tail = (node_lf *)malloc(sizeof(node_lf));
	head->next = tail;
	head->data = -10000;
	tail->next = NULL;
	tail->data = 10000;
	return head;
}

void printlist(node_lf * head)
{
	head = getNodeAddress(head)->next;
	while(getNodeAddress(head)->data != 10000)
	{
		printf("%d\n",getNodeAddress(head)->data);
		head = head->next;
	}
}

void destroy(node_lf * head)
{
	node_lf * next;
	node_lf * curr = getNodeAddress(head);
	while(getNodeAddress(curr) != 0)
	{
		next = getNodeAddress(curr)->next;
		free(curr);
		curr = next;
	}
}

List list_init()
{
	List temp = (List)malloc(sizeof(struct list));
	temp->init = init_LF_list;
	temp->delete_node = delete_node;
	temp->insert = insert;
	temp->print = printlist;
	temp->destructor = destroy;
	return temp;
}

void *thread1(void *);
void *thread2(void *);
void *thread3(void *);
void *thread4(void *);
void *thread5(void *);
void *thread6(void *);
void *thread7(void *);
void *thread8(void *);
void *thread9(void *);
void *thread10(void *);
void *thread11(void *);
void *thread12(void *);
void *thread13(void *);
void *thread14(void *);
void *thread15(void *);
void *thread16(void *);
void *thread17(void *);
void *thread18(void *);
void *thread19(void *);
void *thread20(void *);
void *thread21(void *);
void *thread22(void *);
void *thread23(void *);
void *thread24(void *);
void *thread25(void *);
void *thread26(void *);
void *thread27(void *);
void *thread28(void *);
void *thread29(void *);
void *thread30(void *);
int main()
{
	PCM * m = PCM::getInstance();
	PCM::ErrorCode returnResult = m->program();
	if (returnResult != PCM::Success){
	  std::cerr << "Intel's PCM couldn't start" << std::endl;
	  std::cerr << "Error code: " << returnResult << std::endl;
	  exit(1);
	}
	int proc_0 = 0;
	int proc_1 = 1;
	int proc_2 = 2;
	int proc_3 = 3;


	clock_t begin = clock();	

	List mylist = list_init(); //initialize the list object. Can be called as constructor
	mylist->head = mylist->init(); //initialize the list;
	SystemCounterState before_sstate = getSystemCounterState();
	pthread_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24,t25,t26,t27,t28,t29,t30;
	pthread_create (&t2, NULL, thread2, (void *)mylist);
	pthread_create (&t1, NULL, thread1, (void *)mylist);
	pthread_create (&t3, NULL, thread3, (void *)mylist);
	pthread_create (&t4, NULL, thread4, (void *)mylist);
	pthread_create (&t5, NULL, thread5, (void *)mylist);
	pthread_create (&t6, NULL, thread6, (void *)mylist);
	pthread_create (&t7, NULL, thread7, (void *)mylist);
	pthread_create (&t8, NULL, thread8, (void *)mylist);
	pthread_create (&t9, NULL, thread9, (void *)mylist);
	pthread_create (&t10, NULL, thread10, (void *)mylist);
	pthread_create (&t11, NULL, thread11, (void *)mylist);
	pthread_create (&t12, NULL, thread12, (void *)mylist);
	pthread_create (&t13, NULL, thread13, (void *)mylist);
	pthread_create (&t14, NULL, thread14, (void *)mylist);
	pthread_create (&t15, NULL, thread15, (void *)mylist);
	pthread_create (&t16, NULL, thread16, (void *)mylist);
	pthread_create (&t17, NULL, thread17, (void *)mylist);
	pthread_create (&t18, NULL, thread18, (void *)mylist);
	pthread_create (&t19, NULL, thread19, (void *)mylist);
	pthread_create (&t20, NULL, thread20, (void *)mylist);
	pthread_create (&t21, NULL, thread21, (void *)mylist);
	pthread_create (&t22, NULL, thread22, (void *)mylist);
	pthread_create (&t23, NULL, thread23, (void *)mylist);
	pthread_create (&t24, NULL, thread24, (void *)mylist);
	pthread_create (&t25, NULL, thread25, (void *)mylist);
	pthread_create (&t26, NULL, thread26, (void *)mylist);
	pthread_create (&t27, NULL, thread27, (void *)mylist);
	pthread_create (&t28, NULL, thread28, (void *)mylist);
	pthread_create (&t29, NULL, thread29, (void *)mylist);
	pthread_create (&t30, NULL, thread30, (void *)mylist);
	pthread_join (t1, NULL);
	pthread_join (t2, NULL);
	pthread_join (t3, NULL);
	pthread_join (t4, NULL);
	pthread_join (t5, NULL);
	pthread_join (t6, NULL);
	pthread_join (t7, NULL);
	pthread_join (t8, NULL);
	pthread_join (t9, NULL);
	pthread_join (t10, NULL);
	pthread_join (t11, NULL);
	pthread_join (t12, NULL);
	pthread_join (t13, NULL);
	pthread_join (t14, NULL);
	pthread_join (t15, NULL);
	pthread_join (t16, NULL);
	pthread_join (t17, NULL);
	pthread_join (t18, NULL);
	pthread_join (t19, NULL);
	pthread_join (t20, NULL);
	pthread_join (t21, NULL);
	pthread_join (t22, NULL);
	pthread_join (t23, NULL);
	pthread_join (t24, NULL);
	pthread_join (t25, NULL);
	pthread_join (t26, NULL);
	pthread_join (t27, NULL);
	pthread_join (t28, NULL);
	pthread_join (t29, NULL);
	pthread_join (t30, NULL);
	SystemCounterState after_sstate = getSystemCounterState();
	//mylist->print(mylist->head);
	//mylist->destructor(mylist->head);
	//free(mylist);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	
	std::cout << "\nTime:" << time_spent << std::endl;
	std::cout << "\nInstructions per clock:" << getIPC(before_sstate,after_sstate) << std::endl;
	std::cout << "Bytes read:" << getBytesReadFromMC(before_sstate,after_sstate) << std::endl;
	std::cout << "Bytes Written:" << getBytesWrittenToMC(before_sstate,after_sstate) << std::endl;
	std::cout << "L2 Misses:" << getL2CacheMisses(before_sstate,after_sstate)<< std::endl;
	std::cout << "L2 HIts:" << getL2CacheHits(before_sstate,after_sstate)<< std::endl;
	std::cout << "L3 Misses:" << getL3CacheMisses(before_sstate,after_sstate)<< std::endl;
	std::cout << "L3 HIts:" << getL3CacheHits(before_sstate,after_sstate)<< std::endl;
	std::cout << "Cycles:" << getCycles(before_sstate,after_sstate)<<std::endl;
	std::cout << "Cycles Lost Due L3 Cache Misses:" << getCyclesLostDueL3CacheMisses(before_sstate,after_sstate)<<std::endl;
	std::cout << "Cycles Lost Due L2 Cache Misses:" << getCyclesLostDueL2CacheMisses(before_sstate,after_sstate)<<std::endl;
	mylist->print(mylist->head);
	return 0;
}

void * thread1(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(0,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(1);
	list->insert(12,list->head);
	list->insert(14,list->head);
	list->delete_node(12,list->head);
}

void * thread2(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(2,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(16,list->head);
	list->insert(18,list->head);
	list->delete_node(16,list->head);
	//list->delete_node(16,list->head);
	//insert(12,head);
}
void * thread3(void * args)
{
	
	cpu_set_t cpuset;
	CPU_SET(3,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(10,list->head);
	list->insert(8,list->head);
	list->delete_node(10,list->head);
	//list->delete_node(12,list->head);
	//insert(12,head);
}
void * thread4(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(4,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(6,list->head);
	list->insert(4,list->head);
	list->delete_node(6,list->head);
	//list->delete_node(26,list->head);
	//insert(12,head);
}
void * thread5(void * args)
{	
	cpu_set_t cpuset;
	CPU_SET(0,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(2,list->head);
	list->insert(0,list->head);
	list->delete_node(2,list->head);
	//list->delete_node(28,list->head);
	//insert(12,head);
}
void * thread6(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(2,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(20,list->head);
	list->insert(22,list->head);
	list->delete_node(20,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread7(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(3,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(120,list->head);
	list->insert(122,list->head);
	list->delete_node(120,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread8(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(4,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(201,list->head);
	list->insert(221,list->head);
	list->delete_node(201,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread9(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(0,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(9,list->head);
	list->insert(19,list->head);
	list->delete_node(9,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread10(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(2,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(39,list->head);
	list->insert(49,list->head);
	list->delete_node(39,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread11(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(3,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(69,list->head);
	list->insert(79,list->head);
	list->delete_node(69,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread12(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(4,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(99,list->head);
	list->insert(109,list->head);
	list->delete_node(99,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread13(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(0,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(129,list->head);
	list->insert(139,list->head);
	list->delete_node(129,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread14(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(2,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(159,list->head);
	list->insert(169,list->head);
	list->delete_node(159,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread15(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(3,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(189,list->head);
	list->insert(199,list->head);
	list->delete_node(189,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread16(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(4,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(219,list->head);
	list->insert(229,list->head);
	list->delete_node(219,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread17(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(0,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(200,list->head);
	list->insert(190,list->head);
	list->delete_node(200,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread18(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(2,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(170,list->head);
	list->insert(160,list->head);
	list->delete_node(170,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread19(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(3,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(140,list->head);
	list->insert(130,list->head);
	list->delete_node(140,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread20(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(4,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(145,list->head);
	list->insert(155,list->head);
	list->delete_node(145,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread21(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(0,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(165,list->head);
	list->insert(175,list->head);
	list->delete_node(165,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread22(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(2,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(185,list->head);
	list->insert(195,list->head);
	list->delete_node(185,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread23(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(3,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(1,list->head);
	list->insert(7,list->head);
	list->delete_node(1,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread24(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(4,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(13,list->head);
	list->insert(15,list->head);
	list->delete_node(13,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread25(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(0,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(17,list->head);
	list->insert(191,list->head);
	list->delete_node(17,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread26(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(2,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(21,list->head);
	list->insert(23,list->head);
	list->delete_node(21,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread27(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(3,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(27,list->head);
	list->insert(29,list->head);
	list->delete_node(27,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread28(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(4,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(31,list->head);
	list->insert(33,list->head);
	list->delete_node(31,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread29(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(0,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(35,list->head);
	list->insert(37,list->head);
	list->delete_node(35,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
void * thread30(void * args)
{
	cpu_set_t cpuset;
	CPU_SET(2,&cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) <0) {
	perror("pthread_setaffinity_np");
	}
	List list = (List)args;
	//sleep(2);
	list->insert(39,list->head);
	list->insert(41,list->head);
	list->delete_node(39,list->head);
	//list->delete_node(30,list->head);
	//insert(12,head);
}
