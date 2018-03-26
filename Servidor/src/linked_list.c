#include "../headers/linked_list.h"

int main()
{
    int n, ch;
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
                insert_by_burst(n);
                break;
            case 2:
            	remove_first();
                break;
            case 3:
                display();
                break;
        }
    }while (ch != 0);
}


//Add a new node at the end of the double linked list
void append(int num)
{
	struct dnode *nptr, *temp = start;

	//Create a new node
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = num;
	nptr->process->burst = num;
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

void insert_by_burst(int num)
{
	struct dnode *nptr, *temp = start;
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->burst = num;
	nptr->next = NULL;
	nptr->prev = NULL;

	//if linked list is empty
	if(start == NULL)
	{
		start = nptr;
	}
	else if(num < temp->process->burst)
	{	
		nptr->next = start;
		start->prev = nptr;
		start = nptr;
	}
	else
	{
		while(temp->next != NULL && temp->next->process->burst < num)
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

void insert_by_priority(int num)
{
	struct dnode *nptr, *temp = start;
	nptr = malloc(sizeof(struct dnode));
	nptr->process = malloc(sizeof(struct process));
	nptr->process->priority = num;
	nptr->next = NULL;
	nptr->prev = NULL;

	//if linked list is empty
	if(start == NULL)
	{
		start = nptr;
	}
	else if(num < temp->process->priority)
	{	
		nptr->next = start;
		start->prev = nptr;
		start = nptr;
	}
	else
	{
		while(temp->next != NULL && temp->next->process->priority < num)
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
void remove_first()
{
	if(start == NULL)
	{
		printf("Linked List is empty\n");
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
		free(temp);
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