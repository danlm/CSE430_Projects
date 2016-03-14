// CSE 430 Project 2
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
	int PID;
	
    //Create a variable to store the tty
    char tty[64];
    
    //Create a variable to store the time
    unsigned long long time;
    
    //Create a variable to store the command that started the process
    char cmd[16];
};

/** This function generates the required task list and send it to user space. */
static void generate_Tasklist(void *buf, int size)
{
	// Create a temporary structure variable of type task_info
	struct task_info temp;
	
	// Create a pointer of type task_struct
	struct task_struct *task;
	
	// You will need to use a variable to iterate through the buffer that stores the information
	read_lock(&tasklist_lock); // This will lock the overall task list
	for_each_process(task)
	{
		// Lock each task before you do any reading from it
		read_lock(&task);
		
		// Extract each of the 4 fields needed - PID, tty, time and command from the task and into the temp variable of type task_info
		temp.PID = task->PID;
		if(task->signal == NULL || task->signal->tty == NULL)
		{
			strncpy(temp.tty, "?", 64);
		}
		else {
			strncpy(temp.tty, task->signal->tty->name, 64);
		}
		temp.time = task->time;
		strncpy(temp.cmd, task->comm, 16);
		
		// Unlock the task
		read_unlock(&task);
		
		// Copy the contents of the temp variable into the variable buf using the right command
		copy_to_user(buf, &temp, sizeof(temp));
		
		// You may print the values you extracted to the kernel log just to be sure
		printk(KERN_INFO "%d\t%s\t%d\t%s\n", temp.pid, temp.tty, temp.time, temp.cmd);
	}
	// Unlock the overall task list
	read_unlock(&tasklist_lock);
}

/** This is the system call. */
asmlinkage long sys_mylistprocess(char *buffer, int size)
{
	// Call generate_Tasklist() with the appropriate arguments and return the right value.
	generate_Tasklist(buf, size);
	return 0;
}


