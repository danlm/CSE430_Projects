/*	CSE 430 Assignment 1
test_mycall.c
Description: User-space program to test a system call.
*/

#include <linux/unistd.h>
#define __NR_my_syscall 359

/** The following is a structure that will store only 4 out of the many fields in task_struct*/
struct task_info
{
	//Create a variable to store the PID
    //Create a variable to store the tty
    //Create a variable to store the time
    //Create a variable to store the command that started the process
};

int main()
{
	syscall(__NR_my_syscall);
	return 0;
}
