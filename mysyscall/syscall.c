#include <linux/kernel.h>
#include <linux/syscalls.h>

asmlinkage long sys_opsyscall(void)
{
	printk(KERN_INFO "This is the new system call Daniel Martin, Kevin Liao, and Kevin Van implemented.\n");
	return 0;
}
