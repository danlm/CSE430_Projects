/*	CSE 430 Project 2
test_mycall.c
Description: User-space program to test a system call.
*/
#include <stdio.h>
#include <linux/unistd.h>
#define __NR_my_syscall 359

/** The following is a structure that will store only 4 out of the many fields in task_struct*/
struct task_info
{
	//Create a variable to store the PID
	int PID;
	
    //Create a variable to store the tty
    char tty[64];
    
    //Create a variable to store the time
    unsigned long long time;
    
    //Create a variable to store the command that started the process
    char cmd[16];
};

int main()
{
	char* buffer;
	int size = 1024;
	syscall(__NR_my_syscall, buffer, size);
	printf("%5s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
	for (char *i=buffer; i < buffer+size*sizeof(task_info); i = i+sizeof(taskinfo))
	{
		printf("%5d %-8s\t", i->PID, i->tty);
		unsigned long long temp = i->time/250;
		int hours = temp/3600;
		int minutes = (temp-hours*3600)/60;
		int seconds = (temp-hours*3600-minutes*60);
		printf("%02d:%02d:%02d %-8s\n", hours, minutes, seconds, i->cmd);
	}
	
	return 0;
}
