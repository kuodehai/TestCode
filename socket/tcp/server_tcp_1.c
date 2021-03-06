#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>

#define SERVER_PORT    8745
//#define SERVER_IPADDR  0x7F000001 

int main()
{
	char buf[256];
	int listenfd,connfd;
	int nbytes;
	struct sockaddr_in serveraddr;

	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("create socket error\n");
        return 0;
    };

	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVER_PORT);
	//serveraddr.sin_addr.s_addr = htonl(SERVER_IPADDR);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1){
        printf("bink socket error\n");
    	close(listenfd);
        return 0;
    }

	if(listen(listenfd,10) == -1){
        printf("listen socket error\n");
    	close(listenfd);
        return 0;
    }

	printf("=====waiting for client`s request=====\n");
	if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL)) == -1){
        printf("accept socket error\n");
    	close(listenfd);
        return 0;
    }
        
    while (1) {
        nbytes = recv(connfd,buf,sizeof(buf),0);
        if (nbytes != 0)
        {
            buf[nbytes] = '\0';
            printf("receive:%s\n", buf);
        }
		memset(buf, 0, sizeof(buf));
    }
    close(connfd);
    close(listenfd);
}
