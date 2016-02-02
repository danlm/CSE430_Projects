#include <linux/kernel.h>
#include <linux/syscalls.h>

asmlinkage long sys_mycall(void)
{
	printk(KERN_INFO "Daniel Martin, Kevin Liao, Kevin Van\n");
	return 0;
}