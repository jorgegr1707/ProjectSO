#include "../headers/linked_list.h"
#include "../headers/variables.h"

//Add a new node at the end of the double linked list
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

void insert_by_burst(int id, int burst, int priority, int waiting_time, int arrival_time, int turn_around_time, int burst_original, int arrival_time_original)
{
	struct dnode *nptr, *temp = start;
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
	else if(burst < temp->process->burst)
	{	
		nptr->next = start;
		start->prev = nptr;
		start = nptr;
	}
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

void insert_by_priority(int id, int burst, int priority, int waiting_time, int arrival_time, int turn_around_time, int burst_original, int arrival_time_original)
{
	struct dnode *nptr, *temp = start;
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
	else if(priority < temp->process->priority)
	{	
		nptr->next = start;
		start->prev = nptr;
		start = nptr;
	}
	else
	{
		while(temp->next != NULL && temp->next->process->priority < priority)
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

//Deletes the first node from the double linked list
struct dnode* remove_first()
{
	if(start == NULL)
	{
		//printf("Linked List is empty\n");
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
		//free(temp);
	}
}

//Displays the contents of the linked 
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

//Displays the final results
void final_display()
{
	struct dnode *temp = start;
	printf("\n");
	printf("------------------------- Final results -------------------------\n\n");

	printf("--------- Unfinished processes ---------\n\n");

	while(temp != NULL)
	{
		printf("id:\t%d\tburst:\t%d\tpriority:\t%d\t",temp->process->process_id, temp->process->burst, temp->process->priority);
		printf("WT:\t%d\tTAT:\t%d\tarrival time:\t%d\n",temp->process->waiting_time, temp->process->turn_around_time, temp->process->arrival_time_original);
		temp = temp->next;
	}

	temp = end;

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

