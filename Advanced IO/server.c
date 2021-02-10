#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/uio.h>
int main()
{
	struct iovec iov[3];
	ssize_t nr;
	int fd,i;
	char buf1[10],buf2[10],buf3[10];
	char *fifoo="/tmp/fifoo";
    	mkfifo(fifoo,0666);
    	fd=open(fifoo,O_WRONLY);
	iov[0].iov_base=buf1;
	iov[0].iov_len=sizeof(buf1);
	iov[1].iov_base=buf2;
	iov[1].iov_len=sizeof(buf2);
	iov[2].iov_base=buf3;
	iov[2].iov_len=sizeof(buf3);
	printf("Enter string : ");
	scanf("%s",buf1);
	printf("Enter string : ");
	scanf("%s",buf2);
	printf("Enter string : ");
	scanf("%s",buf3);
	nr=writev(fd,iov,3);
	if(nr==-1) 
	{
		perror("writev");
		return 1;
	}
	printf("Server wrote %d bytes\n",nr);
	close(fd);
}
