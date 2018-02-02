/*************************************************************************
	> File Name: log.h
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月01日 星期四 19时30分09秒
 ************************************************************************/

#ifndef _LOG_H
#define _LOG_H
#include<zlog.h>

extern zlog_category_t *log_handle;

#define ALL(...) zlog_fatal(log_handle, __VA_ARGS__)
#define INF(...) zlog_info(log_handle, __VA_ARGS__)
#define WAR(...) zlog_warn(log_handle, __VA_ARGS__)
#define DBG(...) zlog_debug(log_handle, __VA_ARGS__)
#define ERR(...) zlog_error(log_handle, __VA_ARGS__)

void del_log();
int open_log(char *conf_file,char *mode);
#endif
