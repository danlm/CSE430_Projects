/*	CSE 430 Assignment 1
syscall.c
Description: A system call that prints the names of the team members to the kernel log.
*/

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <stdio.h>
#include <stdlib.h>


asmlinkage char* sys_opsyscall(void)
{
	char ps_output[999];
	FILE *f;
	char output[9999];
	f = popen("ps -e", "r");

	while (fgets(ps_output, sizeof(ps_output)-1, f) != NULL) {
		strcat(output, ps_output);
	}

	pclose(f);
	return output;
}
