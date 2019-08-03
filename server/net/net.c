/************************************************************************
    > File Name: net.c
    > Author: Yang
    > Mail: ma6174@163.com 
    > Created Time: Mon 03 Sep 2018 10:21:09 AM CST
 ************************************************************************/

#include<stdio.h>
#include "../my.h"
int socket_init()
{

	int listenfd, connfd;
	struct sockaddr_in servaddr, cliaddr;
	int ret;
	socklen_t addrlen = sizeof(addrlen);
	char buf[128] = "\0";
	//step 1: socket 创建socket 套接字
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == listenfd)
	{
		perror("socket failed");
		return -1;
	}
	//step 2: bind 绑定地址信息和端口号
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");						
	ret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(-1 == ret)
	{
		perror("bind failed");													
		return -1;
	}
	//step 3: listen 监听连接请求										
	ret = listen(listenfd, 5);
	if(-1 == ret)
	{																			
		perror("listen failed");
		return -1;
	}
	return listenfd;
}


