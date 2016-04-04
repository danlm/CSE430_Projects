#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/tty.h>
#include <linux/kthread.h>
#include <linux/list.h>

#define START_FBD						1
#define STOP_FBD						2
#define FBD_TOGGLE_DEBUG				3
#define FBD_SET_DESCENDANT_THRESHOLD	4
#define FBD_SET_PID_THRESHOLD			5
#define FBD_TOGGLE_KILL					6

volatile unsigned long fdb_flag = 0;
volatile unsigned int fdb_debug = 1;
volatile unsigned int fdb_kill = 0;
volatile unsigned int fdb_fork_threshold = 10;
volatile unsigned int fdb_descendant_threshold = 10;
volatile unsigned int fdb_pid_threshold = 1700;

struct task_struct *fdb_suspect = NULL;
struct task_struct *hello_kthread = NULL;
struct semaphore *semap_lock = NULL;

struct hello_task_info 
{
	int pid;
	unsigned long long time;
	int fork_count;
	int descendant_count;
	char tty[64];
	char cmd[16];
};

}

static void kill_family(struct task_struct *p) 
{
	//Create a pointer to task_struct
	struct task_struct *task;
	//Create a pointer to list_head
	struct list_head *list;
	INIT_LIST_HEAD(list);
	//Use the following loop to iterate through each child of the parent
	list_for_each(list, &p->children) 
	{
		// Assign to the pointer of tast_struct the return value of the list_entry() function
		// by passing the appropriate arguments to the function
		task = list_entry(list, struct task_struct, sibling);
		// Call the function kill_family() recursively with the task_struct pointer as its 
		// argument.
		kill_family(task);
	}

	// The following condition will simply print the pid of the 
	if(fdb_debug > 0 && p != NULL)
		// Add printk() here to print the pid of the fork bomb processes to the kernel log
		printk("%d\n", p->pid); 
	if(fdb_kill > 0)
		// If this condition is true, send a signal to kill the process p
		kill(p->pid, SIGKILL);
}

static int fbd_kthread_function(void *data) 
{
	while(!kthread_should_stop()) 
	{
		// Lock the semap_lock variable using down()
		down(semap_lock);
		if(fdb_debug > 0)
			printk("fbd_kthread wake up\n");

		// Check if the fdb_flag variable is 0 or if there no fdb_suspects found
		// If either of the conditions are true, then continue the loop
		if ((fdb_flag == 1) && (fdb_suspect != NULL))	break;	
		// Use an appropriate function to disable the pre-empting of processes
		preempt_disable();
		// Lock the tasklist using a read lock
		read_lock(&tasklist_lock);
		if(fdb_suspect != NULL) 
		{
			// Check if the fdb_debug variable has any other value than 0
			// If it does then a fork bomb is detected and you must print
			// the pid of that process to the kernel log. 
			// NOTE : The variable fdb_suspect contains the required process
			if (fdb_debug != 0)
			{
				printk("%d\n", fdb_suspect->pid);
			// Call the function kill_family() with the suspect as the argument
				kill_family(fdb_suspect);
			}
		} 
		else 
		{
			if(fdb_debug > 0)
				printk("No fork bomb identified.\n");
		}
		// Unlock the task list
		read_unlock(&tasklist_lock);
		// Enable pre-empting of processes
		preempt_enable();
	}
	return 0;
}
