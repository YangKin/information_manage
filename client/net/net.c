/*************************************************************************
    > File Name: net.c
    > Author: Yangyang 
    > Created Time: Mon 03 Sep 2018 10:12:10 AM CST
 ************************************************************************/

#include<stdio.h>
#include "../my.h"

int socket_init()
{

	int socket_fd;
	struct sockaddr_in server;
	socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if(socket_fd < 0)
	{
		perror("socket");	
		exit(-1);
	}
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	int ret = connect(socket_fd,(struct sockaddr *)&server,sizeof(server));
	if(ret < 0)
	{
		perror("connect failed");	
		exit(-1);
	}
	return socket_fd;
}




