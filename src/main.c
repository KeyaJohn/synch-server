/*************************************************************************
	> File Name: main.c
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月01日 星期四 18时16分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include"listen_guest.h"
#include<unistd.h>
#include"log.h"
#include"list.h"



/*int main()
{
    PListType pHead = NULL;
    ListType p;
    if( init_list(&pHead) == -1)
    {
        return 0;
    }
    
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int i ;
    for(i=0; i<10; i++)
    {
        p.ptr = &a[i];
        insert_list(pHead,&a[i]);
    }
    
    foreach_list(pHead);
    del_list(pHead,&a[3]);
    foreach_list(pHead);
    return 0;
}
*/

int main(int argc,char *argv[])
{

    char log_file[] = "my.conf";
    
    if( argc == 1 )
    {
        printf("------------进入非守护进程模式-----------\n");
        open_log(log_file,"nodemo_cat");
    }
    else if( strncmp(argv[1],"-d",2) == 0)
    {
        printf("------------进入守护进程模式-----------\n");
        daemon(1,0);
        open_log(log_file,"demo_cat");
    }
    else 
    {
        printf("usage: %s  or  %s  -d",argv[0],argv[0]);
        return 0;
    }

    
    listen_guest();
    sleep(22) ;
    return 0;
}
