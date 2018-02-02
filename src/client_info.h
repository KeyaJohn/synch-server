/*************************************************************************
	> File Name: client_info.h
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月02日 星期五 09时16分54秒
 ************************************************************************/

#ifndef _CLIENT_INFO_H
#define _CLIENT_INFO_H

#include<stdint.h>
#include <time.h>
typedef struct 
{
        char lst_dir[256];
        char user_name[32];
        char user_pass[32];
        char user_ip[64];
        char send_file[256];
        int login_flag;
        long int conn_time;
        int sockfd;
        int is_start;
        int send_flag;
        int file_fd;
        //que_t *que_free;
        //que_t *que_busy;

}user_info_t;

#endif
