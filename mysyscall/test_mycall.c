/*	CSE 430 Assignment 1
test_mycall.c
Description: User-space program to test a system call.
*/

#include <linux/unistd.h>
#define __NR_my_syscall 359

int main()
{
	syscall(__NR_my_syscall);
	return 0;
}
