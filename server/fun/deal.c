/*************************************************************************
    > File Name: deal.c
    > Author: Yangyang
    > Mail: 980560264.com 
    > Created Time: Mon 03 Sep 2018 02:08:29 PM CST
 ************************************************************************/
#include "../my.h"
void Create_database()
{

	sqlite3 *db;
	char *errmsg;
	int ret = sqlite3_open("user.db",&db);
	if(ret != SQLITE_OK)
	{

		printf("%s\n",sqlite3_errmsg(db));	
		exit(-1);
	}
	ret = sqlite3_exec(db,"create table if not exists user (type char,name char,passwd char)",NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{

		printf("%s\n",errmsg);	
		exit(-1);
	}
	ret = sqlite3_exec(db,"create table if not exists info (name char,addr char,age integer,level integer, no integer primary key autoincrement,phone char,salary integer)",NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("%s\n",errmsg);	
		exit(-1);
	}
	sqlite3_close(db);
}
int Login_deal(USER *user)
{
	sqlite3 *db;
	char *errmsg,**resultp;
	int nrow,ncolumn,i;
	char buf1[300] = "\0";
	int ret = sqlite3_open("user.db",&db);
	if(ret != SQLITE_OK)	{
		printf("%s\n",sqlite3_errmsg(db));	
		exit(-1);
	}
	if(sqlite3_get_table(db,"select * from user",&resultp,&nrow,&ncolumn,&errmsg)!=SQLITE_OK)
	{
		printf("error:%s\n",errmsg);
		exit(-1);
	}
	for(i=1;i<nrow+1;i++)
	{
		if(strcmp(user->name,resultp[i*3+1])==0 && strcmp(resultp[i*3+2],user->password)==0)
		{
			printf("User exist!Login success\n");
			user->login_success_flag=1;
			strcpy(user->type,resultp[i*3]);//获取用户类型权限
			printf("user type is %s\n",user->type);
			return User_exist;	//一旦找到，就直接退出搜索
		}
	}
	printf("User not exist! %s====%d\n",__FILE__,__LINE__);
	user->login_success_flag=0;	
	return User_gone;
}
void guest_modify_info(USER *user)
{
	sqlite3 *db;
	char *errmsg,**resultp;
	int nrow,ncolumn,i,j,index;
	char buf1[300] = "\0";
	int ret = sqlite3_open("user.db",&db);
	sprintf(buf1,"update user set passwd = '%s' where name = '%s'",user->password,user->name);
	printf("%s\n",buf1);
	if(sqlite3_exec(db,buf1,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);	
		exit(-1);
	}
}
void root_modify_info(INFO *info)
{
	sqlite3 *db;
	char *errmsg,**resultp;
	int nrow,ncolumn,i,j,index;
	char buf1[300] = "\0";
	int ret = sqlite3_open("user.db",&db);
	sprintf(buf1,"update info set addr = '%s',level = %d ,phone = '%s' where name = '%s'",info->addr,info->level,info->phone,info->name);
	printf("%s\n",buf1);
	if(sqlite3_exec(db,buf1,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);	
		exit(-1);
	}
}
int select_info(USER *user,INFO *userinfo)
{
	sqlite3 *db;
	char *errmsg,**resultp;
	int nrow,ncolumn,i,j,index;
	char buf1[300] = "\0";
	int ret = sqlite3_open("user.db",&db);
	if(ret != SQLITE_OK)	{
		printf("%s\n",sqlite3_errmsg(db));	
		return error;
	}
	sprintf(buf1,"select * from info where name = '%s'",user->name);
	ret = sqlite3_get_table(db,buf1,&resultp,&nrow,&ncolumn,&errmsg);
	if(ret != SQLITE_OK)	{
		printf("%s\n",sqlite3_errmsg(db));	
		return error;
	}
	printf("%d====%d--%d\n",__LINE__,nrow,ncolumn);
	index=ncolumn;//
	if(nrow != 0)
	{
		strcpy(userinfo->name,resultp[index++]);
		strcpy(userinfo->addr,resultp[index++]);
		userinfo->age = *resultp[index++];
		userinfo->level = *resultp[index++];
		strcpy(userinfo->phone,resultp[index++]);
		userinfo->salary = *resultp[index++];
	}
	//如果用户不存在，设置年龄为-1，客户端通过检查这个变量来知道是否成员不存在
	else
		userinfo->age = -1;
	sqlite3_close(db);
}
int Add_deal(USER user)
{
	sqlite3 *db;
	char *errmsg;
	char buf1[300] = "\0";
	int ret = sqlite3_open("user.db",&db);
	if(ret != SQLITE_OK)	{
		printf("%s\n",sqlite3_errmsg(db));	
		return error;
		exit(-1);
	}
	sprintf(buf1,"insert into user values('%s','%s','%s')",user.type,user.name,user.password);
	ret = sqlite3_exec(db,buf1,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
		printf("%s\n",errmsg);	
	sprintf(buf1,"insert into info values('%s','anhui',0,0,'00000',0.0)",user.name);
	ret = sqlite3_exec(db,buf1,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)	{
		printf("%d====%s\n",__LINE__,sqlite3_errmsg(db));	
		return error;
		exit(-1);
	}
	sqlite3_close(db);
	return OK;
}
int Delete_deal(USER user)
{
	sqlite3 *db;
	char *errmsg;
	char buf1[300] = "\0";
	int ret = sqlite3_open("user.db",&db);
	if(ret != SQLITE_OK)	{
		printf("%s\n",sqlite3_errmsg(db));	
		return error;
		exit(-1);
	}
	sprintf(buf1,"delete from info where name = '%s'",user.name);
	ret = sqlite3_exec(db,buf1,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)	{
		printf("%d====%s\n",__LINE__,sqlite3_errmsg(db));	
		return error;
		exit(-1);
	}
	sprintf(buf1,"delete from user where name = '%s'",user.name);
	ret = sqlite3_exec(db,buf1,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)	{
		printf("%d====%s\n",__LINE__,sqlite3_errmsg(db));	
		return error;
		exit(-1);
	}
	sqlite3_close(db);
	return OK;
}
int List_deal(INFO *userinfo, int connect_fd)
{
	sqlite3 *db;
	char *errmsg,**resultp;
	int nrow,ncolumn,i,j,index;
	char buf1[300] = "\0";
	int ret = sqlite3_open("user.db",&db);
	if(ret != SQLITE_OK)	{
		printf("%s\n",sqlite3_errmsg(db));	
		return error;
	}
	ret = sqlite3_get_table(db,"select * from info",&resultp,&nrow,&ncolumn,&errmsg);
	if(ret != SQLITE_OK)	{
		printf("%s\n",sqlite3_errmsg(db));	
		return error;
	}
	printf("%d====%d--%d\n",__LINE__,nrow,ncolumn);
	index=ncolumn;
	send(connect_fd,&nrow,sizeof(nrow),0);
	for(i=0;i<nrow;i++)
	{
		bzero(userinfo, sizeof(INFO));
		strcpy(userinfo->name,resultp[index++]);
		strcpy(userinfo->addr,resultp[index++]);
		userinfo->age = *resultp[index++];
		userinfo->level = *resultp[index++];
		strcpy(userinfo->phone,resultp[index++]);
		userinfo->salary = *resultp[index++];
		send(connect_fd,userinfo,sizeof(INFO),0);
	}
	sqlite3_close(db);
	return OK;
}
int callback(void *para,int num,char **value,char **name)
{
	int i;
	for(i=0;i<num;i++)
		printf("%s : %s\n",name[i],value[i]);
	return 0;
}
void print_userinfo()
{
	sqlite3 *db;
	char *errmsg;
	char buf1[300] = "\0";
	int ret = sqlite3_open("user.db",&db);
	if(ret != SQLITE_OK)	{
		printf("%s\n",sqlite3_errmsg(db));	
		exit(-1);
	}
	if(sqlite3_exec(db,"select *from user",callback,NULL,&errmsg)!=SQLITE_OK)
	{
		printf("error:%s\n",errmsg);
		exit(-1);
	}
	sqlite3_close(db);
}
