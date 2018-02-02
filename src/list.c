/*************************************************************************
	> File Name: list.c
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月01日 星期四 22时00分46秒
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include"client_info.h"
#include"list.h"

PListType pHead = NULL;

int  init_list( ) 
{
    pHead = (PListType)malloc((sizeof(ListType)));
    if( pHead == NULL )
    {
        perror("malloc err\n");
        return -1;
    }

    (pHead)->ptr = NULL;
    (pHead)->next = NULL;

}

int  insert_list(user_info_t * data)
{
    PListType temp = pHead;
    PListType pNew = (PListType)malloc(sizeof(ListType));
    if( pNew == NULL )
    {
        perror("malloc err\n");
        return -1;
    }
    pNew->ptr = data;

    pNew->next = pHead->next;
    pHead->next = pNew;
    return 0;
}

/*int  del_list(int epfd)
{
    int i = 0;
    PListType p = pHead->next;
    PListType q = pHead;
    while( p != NULL )
    {
        
        
        if(time(NULL) - p->ptr->conn_time > 6 )
        {
            q->next = p->next;
            free(p->ptr);
            free(p);
            printf("client:%s outline! \n",p->ptr->user_ip);
            return 0;
        }
        q = q->next;
        p = p->next;
    }
    perror("having no node\n");
    return -1;
}
*/

int  foreach_list()
{
    int i = 0;
    PListType p = pHead->next;
    while( p != NULL )
    {
        printf("%s\n",p->ptr->user_ip);
        printf("%d\n",i++);
        p = p->next;
    }
    return 0;
}
