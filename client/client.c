/*************************************************************************
    > File Name: client.c
    > Author: Yangyang
    > Mail: 980560264@qq.com 
    > Created Time: Mon 03 Sep 2018 10:35:21 AM CST

 ************************************************************************/

//命令都封装在USER结构体中

#include "my.h"
#include "net/net.c"
char buf[30]="\0";
USER user;
int ret_add;
INFO userinfo;
void main()
{
	int socket_fd = socket_init();
	int login_success_flag = 0;
	int choice;
	while(1)
	{
		bzero(&user,sizeof(user));
		choice = init_menu();
		if(login_success_flag == 0)
		{
			switch(choice)
			{
				case 1:Login_menu(&user);
					   user.login_regi_flag=1;//登陆标志位
					   send(socket_fd, &user, sizeof(user), 0);
					   bzero(&user, sizeof(user));
					   //返回的user信息中包含用户权限，是普通还是管理员
					   recv(socket_fd, &user, sizeof(user), 0);
					   break;
				case 2:
					   printf("You choose exit, later will close this window ...\n");
					   sleep(2);
					   close(socket_fd);
					   exit(0);
			}
		}
		//把普通和root用户指令相同看待，只是user_command值大小不一样，
		//这样服务器端就不用区分是普通用户指令还是root用户指令，简化问题
		if(user.login_success_flag == User_exist && strcmp(user.type,"guest") == 0)
		{
			login_success_flag=1;
			printf("Guest Login Success, Welcome !!!\n");
			while(1){
				switch(guest_login_menu()){
					case 1:user.user_commend = 1;//修改密码
						   printf("Please input New Pawwword : ");
						   scanf("%s",user.password);
						   send(socket_fd, &user, sizeof(user), 0);
						   break;
					case 2:user.user_commend = 2;
						   send(socket_fd, &user, sizeof(user), 0);
					       close(socket_fd);
						   exit(0);
						   break;
					case 3:user.user_commend=3;//打印用户信息
						   send(socket_fd, &user, sizeof(user), 0);
						   bzero(&userinfo, sizeof(userinfo));
						   recv(socket_fd, &userinfo, sizeof(userinfo), 0);
						   print_info(&userinfo);
						   break;
					default:printf("Please input Again\n");
							break;
				}
			}
		}
		else if(user.login_success_flag == User_exist && strcmp(user.type,"root") == 0)
		{
			login_success_flag=1;
			printf("Root Login Success, Welcome !!!\n");
			while(1){
				switch(root_login_menu()){
					case 1:user.user_commend=1+3;//4 修改信息
						   bzero(user.name, sizeof(user.name));
						   printf("Please input The user's name : ");fflush(stdout);
						   scanf("%s", user.name);
						   printf("Please input New Addr : ");fflush(stdout);
						   scanf("%s", userinfo.addr);
						   printf("Please input New Level : ");fflush(stdout);
						   scanf("%d", &userinfo.level);
						   printf("Please input New phone : ");fflush(stdout);
						   scanf("%s", userinfo.phone);
						   strcpy(userinfo.name, user.name);
						   print_info(&userinfo);//
						   send(socket_fd, &user, sizeof(user), 0);
						   send(socket_fd, &userinfo, sizeof(userinfo), 0);
						   break;
					case 2:user.user_commend=2+3;//5 退出登陆
						   send(socket_fd,&user,sizeof(user),0);
					       close(socket_fd);
						   exit(0);
						   break;
					case 3:user.user_commend=3+3;//6 查询指定用户信息
						   printf("Please input Select User Name : ");fflush(stdout);
						   scanf("%s", user.name);
						   send(socket_fd, &user, sizeof(user), 0);
						   bzero(&userinfo, sizeof(userinfo));
						   recv(socket_fd, &userinfo, sizeof(userinfo), 0);
						   if(userinfo.age == -1)
							   printf("User doen't existence...\n");
						   else
						   {
							   system("clear");
						       print_info(&userinfo);
						   }
						   break;
					case 4:user.user_commend=4+3;//7 添加用户  
						   Add_menu(&user);
						   send(socket_fd, &user, sizeof(user), 0);
						   recv(socket_fd, &ret_add, sizeof(ret_add), 0);
						   if(ret_add == OK)
							   printf("User Add Success, Contratulations !!!\n");
						   else
							   printf("User Add Error, Please checkout !!!\n");
						   break;
					case 5:user.user_commend=5+3;//8 删除用户
						   printf("Please input Delete User Name : ");
						   fflush(stdout);
						   scanf("%s", user.name);
						   send(socket_fd, &user, sizeof(user), 0);
						   printf("Deleting Now ... \n");
						   sleep(2);
						   recv(socket_fd, &ret_add, sizeof(ret_add), 0);
						   if(ret_add == OK)
							   printf("User Deleting Success, Contratulations !!!\n");
						   else
							   printf("User Deleting Error, Attention !!!\n");
						   break;
					case 6:
						   bzero(&user, sizeof(user));
						   user.user_commend=6+3;
						   send(socket_fd, &user, sizeof(user), 0);
						   recv(socket_fd, &ret_add, sizeof(ret_add), 0);
						   while(ret_add-- > 0)
						   {
								recv(socket_fd, &userinfo, sizeof(userinfo), 0);
						        print_info(&userinfo);
						   }
						   printf("Press Ane Key to Continue ...\n");
						   getchar();
						   getchar();
						   system("clear");
						   break;
					default:printf("Please input Again\n");break;
				}
			}
		}
		else
		{
			printf("User Not Exist! Please later input again...\n");
			sleep(3);
		}
	}
}
