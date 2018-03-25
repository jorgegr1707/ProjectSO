#ifndef PROCESS_H
#define PROCESS_H


//Possible attributes of a process
//TODO: Is possible that we need to add more
struct process
{
	int process_id;
	int burst;
	int priority;
};

#endif