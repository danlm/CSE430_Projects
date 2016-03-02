#include <linux/unistd.h>
#define __NR_my_syscall 359

int main()
{
	printf("%s", syscall(__NR_my_syscall));
	return 0;
}
