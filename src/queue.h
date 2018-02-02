/*************************************************************************
	> File Name: quene.h
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月02日 星期五 19时29分13秒
 ************************************************************************/

#ifndef _QUENE_H
#define _QUENE_H
#define SIZE 32 
#define MAXSIZE  10
typedef struct 
{
    char *elem[MAXSIZE];
    int top;
    int bottom;
}Queue,*pQueue;

#endif
