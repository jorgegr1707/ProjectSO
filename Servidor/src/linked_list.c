#include "../headers/linked_list.h"

/*int main()
{
    int n, ch, id = 0;
    struct dnode *temp;
            	
    do
    {
        printf("\n\nOperations on doubly linked list");
        printf("\n1. Append \n2. Remove\n3. Display\n0. Exit\n");
        printf("\nEnter Choice 0-3? : ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                printf("\nEnter number: ");
                scanf("%d", &n);
                insert_by_burst(n, id);
                id++;
                break;
            case 2:
            	temp = remove_first();
            	printf("%d\n", temp->process->process_id);
                break;
            case 3:
                display();
                break;
        }
    }while (ch != 0);
}*/


//Add a new node at the end of the double linked list
void append(int id, int burst, int priority)
{
	struct dnode *nptr, *temp = start;

	//Create a new node
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = priority;
	nptr->process->burst = burst;
	nptr->process->process_id = id;
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

void insert_by_burst(int id, int burst, int priority)
{
	struct dnode *nptr, *temp = start;
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = priority;
	nptr->process->burst = burst;
	nptr->process->process_id = id;
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

void insert_by_priority(int id, int burst, int priority)
{
	struct dnode *nptr, *temp = start;
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = priority;
	nptr->process->burst = burst;
	nptr->process->process_id = id;
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
		printf("Linked List is empty\n");
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
		printf("%d\n", temp->process->burst);
		temp = temp->next;
	}

}