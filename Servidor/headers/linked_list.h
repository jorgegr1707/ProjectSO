#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "process.h"

//Struct of the node (double linked list)
struct dnode
{
	struct process *process;
	struct dnode *prev;
	struct dnode *next;
};

struct dnode *start = NULL;

void append(int);
void insert(int, int, int);
void insert_by_burst(int);
void insert_by_priority(int);
void remove_first();
void display();

#endif