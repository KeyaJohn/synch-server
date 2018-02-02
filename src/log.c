/*************************************************************************
	> File Name: log.c
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月01日 星期四 19时22分28秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"log.h"

zlog_category_t * log_handle = NULL;

int open_log(char *conf_file,char *mode)
{
    if( !conf_file )
    {
        perror("配置文件不存在\n");
        return -1;
    }

    int ret = zlog_init(conf_file);
    if( ret == -1 )
    {
        perror("zlog init err\n");
        return -1;
    }
        
    log_handle = zlog_get_category(mode);
    if( log_handle == NULL )
    {
        perror("zlog_get_category err\n");
        return -1;
    }  
    return 0;
}

void del_log()
{
    zlog_fini();
}
