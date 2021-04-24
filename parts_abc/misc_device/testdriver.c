#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#define DEVICE_NAME "misc_sample"

int main() {
	char * buffer = malloc(10*sizeof(char));
	int size = 10;
	
	int fd = open("/dev/misc_sample", O_RDWR);
	assert(fd > 0);
	int result = read(fd, buffer, size);

	printf("is this working\n");
	printf("%s \n", buffer);

	return 0;
}
