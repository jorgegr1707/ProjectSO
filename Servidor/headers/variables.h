#ifndef VARIABLES_H
#define VARIABLES_H

int rr;
int burst;
int algorithm_type;
int clock_cpu = 0;
int flag; 					//keep running or not
int id = 0;
int terminal_entry = 0;		//display queue or turn off server
int cpu_working_time;
sem_t semaphore_thread;

#endif