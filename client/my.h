#ifndef _MY_H_
#define _MY_H_

#define User_exist 1
#define User_gone 2
#define OK 1
#define error 0

#include<stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <strings.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<grp.h>//group ID
#include<pwd.h>//user ID
#include<string.h>
#include<dirent.h>//directory
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include <sqlite3.h>
//#include "fun/menu.h"

typedef struct 
{
	int user_commend;
	int login_success_flag;
	int login_regi_flag;//biao zhi Login or Register
	char  type[10]; //权限标志位
	char  name[20];  // 姓名
	char  password[10]; // 密码
}USER;

typedef struct 
{
	char name[20];	//姓名
	char addr[20]; // 地址
	int age; // 年龄
	int level; // 等级
	char phone[64]; // 电话
	int salary ; // 工资
}INFO;


#endif
