/*************************************************************************
    > File Name: menu.c
    > Author: Yangyang
    > Mail: 980560264.com 
    > Created Time: Mon 03 Sep 2018 01:33:57 PM CST
 ************************************************************************/

#include "../my.h"
int init_menu()
{
	int choice;
	char buf[20];
	system("clear");
	printf("*************************************************\n");
	printf("*****  Welcome Enter XX_information System  *****\n");
	printf("   1                                 2  \n");
	printf(" Login                              Exit \n");
	printf("*************************************************\n");
	while(1)//prevent the unregular input
	{
		printf("Your Choice : ");
		gets(buf);
		if(buf[0] == '1' || buf[0] == '2')
			break;
		printf("Please input '1' or '2', Thanks !!!\n");	
	}
	choice = atoi(&buf[0]);
	return choice;
}
void Login_menu(USER *user)
{
	printf("Please input Name : ");
	scanf("%s",user->name);
	printf("Please input Passwd : ");
	scanf("%s",user->password);
	printf("%s-%s   is Logining ...\n",user->name,user->password);
	sleep(1);
}
void Add_menu(USER *user)//zhu yi shi zhi zhen,zhe di fang cuo l
{
	printf("Please input NEW Name : ");
	scanf("%s",user->name);
	printf("Please input NEW Passwd : ");
	scanf("%s",user->password);
	printf("Please input NEW Type : ");
	scanf("%s",user->type);
	printf("%s-%s-%s\n",user->name,user->password,user->type);
	printf("Adding .......\n");
	sleep(2);
}
int guest_login_menu(USER user)
{
	int choice;
	printf("*************************************************\n");
	printf("       1             2              3  \n");
	printf(" Modify Passwd      Exit        Select Info \n");
	printf("*************************************************\n");
	printf("Please input Your Choice : ");
	fflush(stdout);
	scanf("%d",&choice);
	return choice;	
}
int root_login_menu(USER user)
{
	int choice;
	printf("********************************************************\n");
	printf("       1        2       3         4      5      6  \n");
	printf(" Modify_info  Exit  Select_Info  Add  Delete   List\n");
	printf("********************************************************\n");
	printf("Please input Your Choice : ");
	fflush(stdout);
	scanf("%d",&choice);
	return choice;	
}
void print_info(INFO *info)
{
	printf("\n\n################################################\n");
	printf("Name : %s\tAddr : %s\t  Age : %d\t\n",info->name,info->addr,info->age-'0');
	printf("Level: %d\tPhone: %s\tSalary: %d\t\n\n",info->level-'0',info->phone,info->salary-'0');
}
