/*
 * fork_bomb.c
 *
 *  Created on: Dec 25, 2015
 *      Author: duolu
 */

#include <stdio.h>

#include <unistd.h>




int main(void)
{
	int pid;

	pid = getpid();
	printf("%d\n", pid);
	fflush(stdout);
    
	while(1) {
		pid = fork();

		if(pid > 0) {

			printf("%d\n", pid);
			fflush(stdout);

		}
	}
}

