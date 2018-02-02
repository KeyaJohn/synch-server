/*************************************************************************
	> File Name: accept.c
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月01日 星期四 20时39分22秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include"check_login.h"
#include"listen_guest.h"
#include"list.h"
#include"client_info.h"

extern PListType pHead;

int join_connect(user_info_t * pClient)
{

    int ret = insert_list(pClient);
    if( ret == -1 )
    {
        printf("insert list err\n");
        return -1;
    }
    return 0;
}

int setnonblock(int fd)
{
        int flag;
        flag = fcntl(fd, F_GETFL, 0);
        fcntl(fd, F_SETFL, flag|O_NONBLOCK);
        return 0;

}

int  del_list(int epfd)
{
    struct epoll_event ev;
    int i = 0;
    PListType p = pHead->next;
    PListType q = pHead;
    while( p != NULL )
    {
        if(time(NULL) - p->ptr->conn_time > 6 )
        {
            printf("client:%s outline! \n",p->ptr->user_ip);
            ev.events = EPOLLIN;
            ev.data.fd = p->ptr->sockfd;
            epoll_ctl(epfd,EPOLL_CTL_DEL,p->ptr->sockfd,&ev);
            close(p->ptr->sockfd);
            
            q->next = p->next;
            free(p->ptr);
            p->ptr = NULL;
            free(p);
            return 0;
        }
        q = q->next;
        p = p->next;
    }
    return -1;
}

int  del_fd_list(int fd)
{
    int i = 0;
    PListType p = pHead->next;
    PListType q = pHead;
    while( p != NULL )
    {
        if( p->ptr->sockfd == fd)
        {
            q->next = p->next;
            free(p->ptr);
            p->ptr = NULL;
            free(p);
            return 0;
        }
        q = q->next;
        p = p->next;
    }
    return -1;
}
user_info_t*  find_fd_list(int fd)
{
    int i = 0;
    PListType p = pHead->next;
    PListType q = pHead;
    while( p != NULL )
    {
        if( p->ptr->sockfd == fd)
        {
            return p->ptr;
        }
        q = q->next;
        p = p->next;
    }
    return NULL;
}

int listen_guest()
{
    int sockfd,newfd;
    int len;
    struct sockaddr_in ser_addr,cli_addr;
    
    user_info_t* pclient =  NULL;

    int  ret = init_list();
    if( ret == -1 )
    {
        printf("init list err\n");
        return -1;
    }
    
    if( (sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1 )
    {
        perror("scoket err\n");
        return -1;
    }
    
    int on = 1;
    if( (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(int))) == -1)
    {
        perror("setsockopt err\n");
        return -1;
    }

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(SER_PORT);
    ser_addr.sin_addr.s_addr = inet_addr(SER_IP);
    
    len = sizeof(struct sockaddr_in) ;
    ret = bind(sockfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in));
    if( ret == -1 )
    {
        perror("bind err\n");
        return -1;
    }
    
    listen(sockfd,MAX_LINK);
    setnonblock(sockfd);
    struct epoll_event evs[MAX_LINK],ev;
    ev.data.fd = sockfd;
    ev.events = EPOLLIN;

    signal(SIGPIPE,SIG_IGN);
    int epfd = epoll_create(MAX_LINK);
    if( epfd < 0 )
    {
        perror("epoll create err\n");
        return -1;
    }

    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);
    
    while( 1 )
    {
        int nfds = epoll_wait(epfd,evs,MAX_LINK,3000);
        //del_list(epfd);
        if( nfds < 0 )
        {
            perror("epoll wait err\n");
            return -1;
        }
        else if( nfds == 0 )
        {
            printf("time out\n");
            continue;
        }
         

        int i;
        for(i=0; i<nfds; i++)
        {
            if( evs[i].data.fd == sockfd )
            {

                newfd = accept(sockfd,(struct sockaddr*)&cli_addr,&len);
                if( newfd < 0 )
                {
                    perror("accept err\n");
                    return -1;
                }

                setnonblock(newfd);
                ev.data.fd = newfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_ADD,newfd,&ev);
               
               
                pclient = (user_info_t *) malloc (sizeof(user_info_t));
                if( pclient == NULL)
                {
                    perror("malloc err\n");
                }
                strcpy(pclient->user_ip,inet_ntoa(cli_addr.sin_addr));
                pclient->conn_time = time(NULL);
                pclient->sockfd = newfd; 
                pclient->is_start = 0; 
                
                join_connect(pclient);
                foreach_list();
            }
            else if( (evs[i].events) & EPOLLIN) 
            {

                user_info_t * pTemp = find_fd_list(evs[i].data.fd);
                pTemp->conn_time = time(NULL);
                int ret = check_login(evs[i].data.fd);
                if( ret == -1 )
                {
                    epoll_ctl(epfd,EPOLL_CTL_DEL,evs[i].data.fd,&ev);
                    close(evs[i].data.fd);
                    del_fd_list(evs[i].data.fd);
                }
                else 
                {
                     
                }     
               
                epoll_ctl(epfd,EPOLL_CTL_DEL,evs[i].data.fd,&ev);
                close(evs[i].data.fd);
            }
            else 
            {
                epoll_ctl(epfd,EPOLL_CTL_DEL,evs[i].data.fd,&ev);
                close(evs[i].data.fd);
            }
        
        }
    }
}



