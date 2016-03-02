#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char ps_output[999];
	FILE *f;
	//char* output = (char*)malloc(1);
	char output[9999];
	f = popen("ps -e", "r");
	while (fgets(ps_output, sizeof(ps_output)-1, f) != NULL) {
		//output = realloc(output, sizeof(output)+sizeof(ps_output));
		//sprintf(output, "%s", ps_output);
		strcat(output, ps_output);
	}
	pclose(f);
	printf("%s", output);
	return 0;
}
