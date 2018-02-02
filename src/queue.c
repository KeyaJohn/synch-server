/*************************************************************************
	> File Name: quene.c
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月02日 星期五 19时28分23秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include"queue.h"
#include<stdbool.h>

/*int init_queue(pqueue  qu,char (*que_arr)[])
{
    char *mem =(char *)malloc( sizeof (char ) * MEMSIZE * MEMLEN);
    if( mem == NULL )
    {
        perror("malloc err\n");
        return -1;
    }

    int i = 0;
    for(; i<MEMLEN; i++)
    {
        que_arr[i] = mem;
        mem = mem + MEMSIZE;
    }
    
    qu->front = 0;
    qu->behind = 0;
}
*/


int init_queue(Queue *qu)
{
    qu->top = 0;
    qu->bottom = 0;
}


int push(Queue *queue, char *filename)
{
    if ((queue->top + 1) % MAXSIZE == queue->bottom)
    {
        printf("queue Full\n");
        return -1;
    }
        queue->elem[queue->top] = filename;
        queue->top = (queue->top +1)% MAXSIZE;
    return 0;
}

int pop(Queue * queue, char **date)
{
    if (queue->top == queue->bottom)
    {
        printf("queue empty\n");
        return -1;
            
    }
    *date = queue->elem[queue->bottom];
    queue->bottom = (queue->bottom + 1) % MAXSIZE;
}

int is_full(Queue *queue)
{
    if ((queue->top + 1) % MAXSIZE == queue->bottom)
    {
        printf("queue Full\n");
        return -1;
    }
    return 0;
}
   
int is_empty(Queue *queue)
{
    if (queue->top == queue->bottom)
    {
        printf("queue empty\n");
        return -1;
    }
    return 0;
}

void show(Queue * queue)
{
  // if( (queue->top + 1) != queue->bottom )
    if ((queue->top + 1) % MAXSIZE == queue->bottom)
    {
        printf("%s\n",queue->elem[queue->top]);
        queue->top += 1;
    }

}

/*void main()
{
    
    char *p[] = {"aaa","bbb","ccc","ddd"};

    Queue queue ;
    init_queue(&queue);
    push(&queue,p[0]);
    push(&queue,p[3]);
    push(&queue,p[2]);
    push(&queue,p[1]);
   
    char*q = NULL;
    pop(&queue,&q);
    printf("%s\n",q);
    
    pop(&queue,&q);
    printf("%s\n",q);
    
    pop(&queue,&q);
    printf("%s\n",q);
   
    pop(&queue,&q);
    printf("%s\n",q);

    pop(&queue,&q);
    printf("%s\n",q);
}
*/
