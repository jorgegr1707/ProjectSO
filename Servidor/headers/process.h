#ifndef PROCESS_H
#define PROCESS_H


//Possible attributes of a process
//TODO: Is possible that we need to add more
struct process
{
	int process_id;
	int burst;
	int priority;
	int waiting_time;
	int arrival_time;
	int turn_around_time;
};

#endif