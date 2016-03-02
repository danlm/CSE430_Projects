/*	CSE 430 Assignment 1
martin_liao_van.c
Description: Kernel module to print out names of the team members to the kernel log.
*/

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>

static int __init my_name(void)
{
	printk(KERN_INFO "Daniel Martin, Kevin Liao, Kevin Van\n");
	return 0;
}

static void __exit cleanup_names(void)
{
	printk(KERN_INFO "\n");
}

module_init(my_name);
module_exit(cleanup_names);