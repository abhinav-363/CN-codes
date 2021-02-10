#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	char buf1[10],buf2[10],buf3[10];
	struct iovec iov[3];
	ssize_t nr;
	int fd,i;
	char *fifoo="/tmp/fifoo";
    	mkfifo(fifoo,0666);
    	fd=open(fifoo,O_RDONLY);
	iov[0].iov_base=buf1;
	iov[0].iov_len=sizeof(buf1);
	iov[1].iov_base=buf2;
	iov[1].iov_len=sizeof(buf2);
	iov[2].iov_base=buf3;
	iov[2].iov_len=sizeof(buf3);
	nr=readv(fd,iov,3);
	for(i=0;i<3;i++)
	printf("%d : %s\n",i,(char *)iov[i].iov_base);
	close(fd);
}
