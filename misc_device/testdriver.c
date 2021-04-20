#include <stdio.h>
#include <fcntl.h>

int main() {
	int fd = open("/dev/misc_sample", O_RDWR);
	char * buffer;
	int size = 10;
	int result = read(fd, buffer, size);

	printf("%s \n", buffer);

	return 0;
}
