/*************************************************************************
    > File Name: server.c
    > Author: Yangyang
    > Mail: 980560264.com 
    > Created Time: Mon 03 Sep 2018 10:49:40 AM CST
 ************************************************************************/

#include"my.h"
#include"net/net.c"
char buf[10]="\0";
void main()
{
	USER user;
	INFO userinfo;
	int connect_fd ;
	int ret_logindeal,ret_add;
	pid_t pid;
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(addrlen);////注意此处一定要初始化，要把这个值传给accept函数,不然会发现32 行recv竟然不阻塞了
	int listen_fd = socket_init();
	Create_database();
	while(1)
	{
		connect_fd = accept(listen_fd,(struct sockaddr*)&cliaddr,&addrlen);//阻塞
		printf("connect from %s port %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		printf("accept success\n");
		//新用户登陆，创建一个进程处理,成功即为新用户
		if(fork() == 0)
		{
			do{
				printf("%s----%d\n",__FILE__,__LINE__);
				bzero(&user,sizeof(user));
				recv(connect_fd,&user,sizeof(user),0);
				//第一次进来时user只含有用户名和密码信息
				if(user.login_success_flag == 0)
				{
					printf("%s--%s----%s--%d\n",user.name,user.password,__FILE__,__LINE__);
					ret_logindeal = Login_deal(&user);
					if(ret_logindeal == User_gone)//User not exist
					{
						printf("User doesn't exist,Please checkout username or passwd\n");
						printf("%s----%d\n",__FILE__,__LINE__);
					}
					send(connect_fd,&user,sizeof(user),0);//返回用户是否存在，客户端可以进行下一步操作
				}
			}while(ret_logindeal == User_gone);
			//登陆系统成功
			do{
				bzero(&user,sizeof(user));
				recv(connect_fd,&user,sizeof(user),0);//成功登陆后,接收用户操作命令
				switch(user.user_commend){
					case 1:guest_modify_info(&user);
						   break;
					case 2:printf("Guest leave, will close this socket\n");
						   close(connect_fd);
						   exit(0);
						   break;
					case 3:select_info(&user,&userinfo);
						   send(connect_fd,&userinfo,sizeof(userinfo),0);
						   break;
					case 4:recv(connect_fd,&userinfo,sizeof(userinfo),0);//接收修改的数据
						   root_modify_info(&userinfo);
						   break;
					case 5:
						   printf("Root leave, will close this socket\n");
						   close(connect_fd);
						   exit(0);
						   break;
					case 6:bzero(&userinfo,sizeof(userinfo));
						   select_info(&user,&userinfo);
						   send(connect_fd,&userinfo,sizeof(userinfo),0);
						   break;
					case 7:ret_add = Add_deal(user);//需要在info，user 2张表里增添记录
						   send(connect_fd,&ret_add,sizeof(ret_add),0);
						   break;
					case 8:ret_add = Delete_deal(user);//删除记录
						   send(connect_fd,&ret_add,sizeof(ret_add),0);
						   break;
					case 9:ret_add = List_deal(&userinfo, connect_fd);
						   break;
					default:break;
				}
			}while(1);
		}
		else
		{
		//	close(connect_fd);
			printf("My is father==%d, %s----%d\n",getpid(),__FILE__,__LINE__);
		}
	//	print_userinfo();
	//	send(connect_fd,"Register Success!",20,0);
	}
}
