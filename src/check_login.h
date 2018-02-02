/*************************************************************************
	> File Name: check_login.h
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月02日 星期五 16时02分58秒
 ************************************************************************/

#ifndef _CHECK_LOGIN_H
#define _CHECK_LOGIN_H
typedef struct name_pass
{
    char user_name[20];
   char user_pass[20];
}Login_Info;

int check_mysql(char name[],char pass[]);
int check_login(int fd);
#endif
