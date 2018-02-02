/*************************************************************************
	> File Name: list.h
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月01日 星期四 22时08分07秒
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H
#define MAXSIZE 56
#include <stdint.h>
#include"list.h"
#include "client_info.h"

typedef struct list
{
    user_info_t   * ptr;
    struct list *next;
}ListType,*PListType;

extern  PListType pHead;

int  init_list( );
int  insert_list(user_info_t *);
int  del_list();
int  foreach_list();
#endif
