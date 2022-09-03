#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int o1;
	int o2;
	int o3;
	int ot1;
	int ot2;
	int ot3;
	int fd1 = open("test1", O_RDONLY);
	int fd2 = open("test2", O_RDONLY);
	int fd3 = open("test3", O_RDONLY);
	char *c1 = (char *) calloc (5000, sizeof(char));
	char *c2 = (char *) calloc (5000, sizeof(char));
	char *c3 = (char *) calloc (5000, sizeof(char));	
	char *c4 = (char *) calloc (5000, sizeof(char));
    char *c5 = (char *) calloc (5000, sizeof(char));
    char *c6 = (char *) calloc (5000, sizeof(char));

	if (fd1 < 0 || fd2 <0 || fd3 < 0)
	{
		printf("file cannot be open\n");
		return (0);
	}
	o1 = read(fd1, c1, 5000);
	o2 = read(fd2, c2, 5000);
	o3 = read(fd3, c3, 5000);
	ot1 = read(3, c4, 5000);
	ot2 = read(4, c5, 5000);
	ot3 = read(5, c6, 5000);
	printf(" %d\n %d\n %d\n", fd1, fd2, fd3);
	printf(" %d\n %d\n %d\n %d\n %d\n %d\n", o1, o2, o3, ot1, ot2, ot3);
	return (0);
}
