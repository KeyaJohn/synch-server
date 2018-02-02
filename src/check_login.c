/*************************************************************************
	> File Name: check_log.c
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月02日 星期五 16时01分37秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include<string.h>
#include "check_login.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int check_login(int fd)
{
    Login_Info str_info;
    memset(&str_info,'\0',sizeof(Login_Info));
    int len = recv(fd,&str_info,sizeof(Login_Info),0);
    if( len < 0 )
    {
        perror("recv login info err\n");
        return -1;
    }
    
   // printf("%s   %s\n",str_info.user_name,str_info.user_pass);
    if( check_mysql(str_info.user_name,str_info.user_pass) == 0)
    {
        printf("login in successfully!\n") ;
        return 0;
    }
    
    printf("login in faile!\n") ;

    return -1; 
}

int check_mysql(char name[],char pass[])
{
    MYSQL* p_mysql;
    p_mysql = mysql_init(NULL);
    if( p_mysql == NULL )
    {
        printf("init mysql error\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(p_mysql,"127.0.0.1","root","jingtikai","cli_info_db",0,NULL,0) == NULL ) 
    {
        printf("connect mysql server errno :%d\n",mysql_errno(p_mysql));
        exit(EXIT_FAILURE);
    }
    
    if( mysql_select_db(p_mysql,"cli_info_tb") == 0)
    {
        printf("select db err\n");
        exit(EXIT_FAILURE);
    }
    char buff[1024] ;
    memset(buff,'\0',1024);
/*    sprintf(buff,"%s","insert into stu_tb values (null,'jingti',12,1,'jjjjj',null) ;");
    if (mysql_query(p_mysql,buff) != 0)
    {
        printf("insert data err\n");
        exit(EXIT_FAILURE);
    }
*/
    memset(buff,'\0',1024);
    sprintf(buff,"select * from  cli_info_tb");
    if( mysql_query(p_mysql,buff) != 0 )
    {
        perror("query err\n");
        exit(EXIT_FAILURE);
    }

    
    MYSQL_RES * p_res = mysql_store_result(p_mysql);
    if( p_res == NULL )
    {
        printf("store err\n");
        exit(EXIT_FAILURE);
    }

    MYSQL_ROW p_row;
    while( (p_row = mysql_fetch_row(p_res)) != NULL )
    {
    //    printf("%s\t%s\n",p_row[0],p_row[1]);
        if( ((strcmp(name,p_row[0]))==0) && (strcmp(pass,p_row[1])==0) )
        {
            return 0;
        }
    }
    
    mysql_free_result(p_res);

    mysql_close(p_mysql);
    return -1;
}


