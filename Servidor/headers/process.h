#ifndef PROCESS_H
#define PROCESS_H


//Possible attributes of a process
//TODO: Is possible that we need to add more
struct process
{
	int process_id;
	int burst;
	int burst_original;
	int priority;
	int waiting_time;
	int arrival_time;
	int arrival_time_original;
	int turn_around_time;
	int conection_id;
};

#endif