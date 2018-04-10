#include "../headers/linked_list.h"
#include "../headers/variables.h"


/****************************************************************
*Function that add a process at the end of double linked 		*
*list (ready queue)												*
*Parameters:													*
*	id = Process id.											*
*	burst = Actual burst of process.							*
*	priority = Process priority.								*
*	waiting_time = Time difference between turn arround time 	*
*				   and burst time.								*
*	arrival_time = Time which process arrives in the ready 		*
*				   queue.										*
*	turn_around_time = Time difference between completion		*
*					   time and arrival time.					*
*	burst_original = Original burst of process.					*
*	arrival_time_original = Original arrival time of process 	*
*****************************************************************/


void append(int id, int burst, int priority, int waiting_time, int arrival_time, int turn_around_time, int burst_original, int arrival_time_original)
{
	struct dnode *nptr, *temp = start;

	//Create a new node
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = priority;
	nptr->process->burst = burst;
	nptr->process->burst_original = burst_original;
	nptr->process->process_id = id;
	nptr->process->waiting_time = waiting_time;
	nptr->process->arrival_time = arrival_time;
	nptr->process->arrival_time_original = arrival_time_original;
	nptr->process->turn_around_time = turn_around_time;
	nptr->next = NULL;
	nptr->prev = NULL;

	// if linked list is empty
	if (start == NULL)
	{
		start = nptr;
	}
	else
	{
		//traverse the linked list till the last node is reached
		while(temp->next != NULL)
			temp = temp->next;

		nptr->prev = temp;
		temp->next = nptr;
	}
}

/****************************************************************
*Function that add a process at the end of double linked 		*
*list (end queue)												*
*Parameters:													*
*	id = Process id.											*
*	burst = Actual burst of process.							*
*	priority = Process priority.								*
*	waiting_time = Time difference between turn arround time 	*
*				   and burst time.								*
*	turn_around_time = Time difference between completion		*
*					   time and arrival time.					*
*	arrival_time = Time which process arrives in the ready 		*
*				   queue.										*
*	burst_original = Original burst of process.					*
*	arrival_time_original = Original arrival time of process 	*
*****************************************************************/


void append_end(int id, int burst, int priority, int waiting_time, int turn_around_time, int arrival_time, int burst_original, int arrival_time_original)
{
	struct dnode *nptr, *temp = end;

	//Create a new node
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = priority;
	nptr->process->burst = burst;
	nptr->process->burst_original = burst_original;
	nptr->process->process_id = id;
	nptr->process->waiting_time = waiting_time;
	nptr->process->turn_around_time = turn_around_time;
	nptr->process->arrival_time = arrival_time;
	nptr->process->arrival_time_original = arrival_time_original;
	nptr->next = NULL;
	nptr->prev = NULL;

	// if linked list is empty
	if (end == NULL)
	{
		end = nptr;
	}
	else
	{
		//traverse the linked list till the last node is reached
		while(temp->next != NULL)
			temp = temp->next;

		nptr->prev = temp;
		temp->next = nptr;
	}
}


/****************************************************************
*Function that make an ordered insert of the process in the 	*
*ready queue by burst 											*
*Parameters:													*
*	id = Process id.											*
*	burst = Actual burst of process.							*
*	priority = Process priority.								*
*	waiting_time = Time difference between turn arround time 	*
*				   and burst time.								*
*	turn_around_time = Time difference between completion		*
*					   time and arrival time.					*
*	arrival_time = Time which process arrives in the ready 		*
*				   queue.										*
*	burst_original = Original burst of process.					*
*	arrival_time_original = Original arrival time of process 	*
*****************************************************************/


void insert_by_burst(int id, int burst, int priority, int waiting_time, int arrival_time, int turn_around_time, int burst_original, int arrival_time_original)
{
	struct dnode *nptr, *temp = start;

	//Create a new node
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = priority;
	nptr->process->burst = burst;
	nptr->process->burst_original = burst_original;
	nptr->process->process_id = id;
	nptr->process->waiting_time = waiting_time;
	nptr->process->arrival_time = arrival_time;
	nptr->process->arrival_time_original = arrival_time_original;
	nptr->process->turn_around_time = turn_around_time;
	nptr->next = NULL;
	nptr->prev = NULL;

	//if linked list is empty
	if(start == NULL)
	{
		start = nptr;
	}

	/* Compare each process burst in the queue */

	//First case
	else if(burst < temp->process->burst)
	{	
		nptr->next = start;
		start->prev = nptr;
		start = nptr;
	}

	//Rest of the elements
	else
	{
		while(temp->next != NULL && temp->next->process->burst < burst)
			temp = temp->next;

		nptr->next = temp->next;

		if(temp->next != NULL)
		{
			nptr->next->prev = nptr;
		}

		temp->next = nptr;
		nptr->prev = temp;
	}
}


/****************************************************************
*Function that make an ordered insert of the process in the 	*
*ready queue by priority										*
*Parameters:													*
*	id = Process id.											*
*	burst = Actual burst of process.							*
*	priority = Process priority.								*
*	waiting_time = Time difference between turn arround time 	*
*				   and burst time.								*
*	turn_around_time = Time difference between completion		*
*					   time and arrival time.					*
*	arrival_time = Time which process arrives in the ready 		*
*				   queue.										*
*	burst_original = Original burst of process.					*
*	arrival_time_original = Original arrival time of process 	*
*****************************************************************/


void insert_by_priority(int id, int burst, int priority, int waiting_time, int arrival_time, int turn_around_time, int burst_original, int arrival_time_original)
{
	struct dnode *nptr, *temp = start;

	//Create a new node
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = priority;
	nptr->process->burst = burst;
	nptr->process->burst_original = burst_original;
	nptr->process->process_id = id;
	nptr->process->waiting_time = waiting_time;
	nptr->process->arrival_time = arrival_time;
	nptr->process->arrival_time_original = arrival_time_original;
	nptr->process->turn_around_time = turn_around_time;
	nptr->next = NULL;
	nptr->prev = NULL;

	//if linked list is empty
	if(start == NULL)
	{
		start = nptr;
	}

	/*Compare each process priority in the ready queue*/

	//First case
	else if(priority < temp->process->priority)
	{	
		nptr->next = start;
		start->prev = nptr;
		start = nptr;
	}

	//General case
	else
	{
		while(temp->next != NULL && temp->next->process->priority < priority)
			temp = temp->next;

		nptr->next = temp->next;

		//If next is not the last element, it assigned to the previous one
		if(temp->next != NULL)
		{
			nptr->next->prev = nptr;
		}

		temp->next = nptr;
		nptr->prev = temp;
	}
}


/********************************************************
*Function that return the first element of the queue and*
*remove it.												*
*Parameters:											*
*	No parameters 										*
*********************************************************/


struct dnode* remove_first()
{
	if(start == NULL)
	{
		return NULL;
	}

	else
	{
		struct dnode *temp = start;

		//If only one element
		if(temp->next == NULL)
		{
			start = NULL;
		}

		//Delete first element
		else
		{
			start = start->next;
			start->prev = NULL;
		}
		return temp;
	}
}


/********************************************************
*Function that clear all the elements of all the linked *
*linked list.											*
*Parameters:											*
*	No parameters 										*
*********************************************************/


void clear_linked_list()
{

	/* Clear the ready queue */
	struct dnode *curr = start;
	struct dnode *next;

	while(curr != NULL)
	{
		next = curr->next;
		free(curr->process);
		free(curr);
		curr = next;
	}

	start = NULL;


	/*Clear the end queue */

	curr = end;

	while(curr != NULL)
	{
		next = curr->next;
		free(curr->process);
		free(curr);
		curr = next;
	}

	end = NULL;


	/*Clear the temp_rr queue*/

	curr = temp_rr;

	while(curr != NULL)
	{
		next = curr->next;
		free(curr->process);
		free(curr);
		curr = next;
	}

	temp_rr = NULL;	

}


/************************************************************
*Function that print the info of each process in the queue.	*
*Parameters:												*
*	No parameters 											*
*************************************************************/


void display()
{
	struct dnode *temp = start;
	printf("\n");

	while(temp != NULL)
	{
		printf("id:\t");
		printf("%d\t", temp->process->process_id);

		printf("burst:\t");
		printf("%d\n", temp->process->burst);
		temp = temp->next;
	}

}


/************************************************************
*Function that print the info of each process in the queue.	*
*Parameters:												*
*	No parameters 											*
*************************************************************/


void final_display()
{
	struct dnode *temp = start;
	printf("\n");
	printf("------------------------- Final results -------------------------\n\n");

	/*Unfinished process*/
	printf("--------- Unfinished processes ---------\n\n");

	while(temp != NULL)
	{
		printf("id:\t%d\tburst:\t%d\tpriority:\t%d\t",temp->process->process_id, temp->process->burst, temp->process->priority);
		printf("WT:\t%d\tTAT:\t%d\tarrival time:\t%d\n",temp->process->waiting_time, temp->process->turn_around_time, temp->process->arrival_time_original);
		temp = temp->next;
	}

	temp = end;

	/*Finished process*/
	printf("\n--------- Finished processes ---------\n\n");

	int executed = 0;
	int w_time = 0;

	while(temp != NULL)
	{
		printf("id:\t%d\tburst:\t%d\tpriority:\t%d\t",temp->process->process_id, temp->process->burst_original, temp->process->priority);
		printf("WT:\t%d\tTAT:\t%d\tarrival time:\t%d\n",temp->process->waiting_time, temp->process->turn_around_time, temp->process->arrival_time_original);
		executed++;
		w_time += temp->process->waiting_time;
		temp = temp->next; 
	}

	printf("\n----> Average Waiting Time:\t%f\n", ((float) w_time/ (float) executed));
	printf("----> Executed processes:\t%d\n",executed);
	printf("----> Idle CPU time:\t%d\n",(clock_cpu - cpu_working_time));



}

