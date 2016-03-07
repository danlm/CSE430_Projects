/** The following template is the kernel space C program that you may use. Fill in the necessary code and try to compile it. Make sure you read the reference given in the hints to fully understand the given code.
 */


#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/tty.h>
#include <linux/kthread.h>

/** The following is a structure that will store only 4 out of the many fields in task_struct*/
struct task_info
{
	//Create a variable to store the PID
    //Create a variable to store the tty
    //Create a variable to store the time
    //Create a variable to store the command that started the process
};

/** This function generates the required task list and send it to user space. */
static void generate_Tasklist(void *buf, int size)
{
	// Create a temporary structure variable of type task_info
	// Create a pointer of type task_struct
    // You will need to use a variable to iterate through the buffer that stores the information
	read_lock(&tasklist_lock); // This will lock the overall task list
	for_each_process(task)
    {
		// Lock each task before you do any reading from it
		// Extract each of the 4 fields needed - PID, tty, time and command from the task and into the temp variable of type task_info
		// Unlock the task
		// Copy the contents of the temp variable into the variable buf using the right command
		// You may print the values you extracted to the kernel log just to be sure
	}
	// Unlcok the overall task list
}

/** This is the system call. */
asmlinkage long sys_mylistprocess(char *buffer,int size)
{
	// Call generate_Tasklist() with the appropriate arguments and return the right value.
}


