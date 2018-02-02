/*************************************************************************
> File Name: listen_file.c
> Author: kayejohn
> Mail: 1572831416@qq.com
> Created Time: 2018年02月02日 星期五 20时57分35秒
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/inotify.h>
#include"listen_file.h"




int in_move_to(struct inotify_event * event)
{
    if(event->mask&IN_ISDIR)
    {
        printf("Directory %s move to\n",event->name);
    }
    else
    {
        printf("FIle %s move to\n",event->name);
    }
}

int in_move_from(struct inotify_event * event)
{
    if(event->mask&IN_ISDIR)
    {
        printf("Directory %s move from.\n",event->name);
    }
    else
    {
        printf("FIle %s move from\n",event->name);
    }

}

int delete(struct inotify_event * event)
{
    if(event->mask&IN_ISDIR)
    {
        printf("Directory %s deleted.\n",event->name);
    }
    else
    {
        printf("FIle %s deleted.\n",event->name);
    }
}
int create(struct inotify_event * event)
{
    if( event->mask & IN_ISDIR )
    {
        printf("New directpry %s create.\n",event->name);
    }
    else
    {
        printf("New file %s create.\n",event->name);
    }
}

int modify(struct inotify_event * event)
{
    if( event->mask & IN_ISDIR )
    {
        printf("New directpry %s create.\n",event->name);
    }
    else
    {
        printf("New file %s create.\n",event->name);
    }
}
int listen_file(char *path)
{
    int length,i = 0;
    int fd;
    int wd;

    char buffer[EVENT_BUF_LEN];

    fd = inotify_init();
    if( fd < 0 )
    {
        perror("inotify_init err\n");
        return -1;
    }

    wd = inotify_add_watch(fd,"/tmp",IN_CREATE|IN_DELETE);

    while( 1 )
    {
        int i = 0;
        length = read(fd,buffer,EVENT_BUF_LEN);
        if( length < 0 )
        {
            perror("inotify read err\n");
            return -1;
        }

        while( i<length )
        {
            struct inotify_event * event = (struct inotify_event *)&buffer[i];
            if( event->len )
            {
                if( event->mask & IN_CREATE  )
                {
                }
                else if( event->mask & IN_DELETE  )
                {
                }
                else if( event->mask & IN_MODIFY  )
                {
                }
                else if( event->mask & IN_MOVED_FROM )
                {
                }
                else if ( event->mask &  IN_MOVED_TO )
                {
                    
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }
    inotify_rm_watch(fd,wd);
    close(fd);
    return 0;
}
