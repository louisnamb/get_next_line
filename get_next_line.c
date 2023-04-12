#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include <fcntl.h>

int main()
{
	FILE *fp;
   	fp = fopen("/tmp/test.txt", "w");
	fprintf(fp, "This is testing...\n");
	fclose(fp;);
	return (0);
}
