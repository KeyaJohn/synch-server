/*************************************************************************
	> File Name: listen_file.h
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年02月02日 星期五 22时07分04秒
 ************************************************************************/

#ifndef _LISTEN_FILE_H
#define _LISTEN_FILE_H
//IN_ACCESS : 即文件被访问
//IN_MODIFY : 文件被 write
//IN_ATTRIB : 文件属性被修改，如 chmod、chown、touch 等
//IN_CLOSE_WRITE : 可写文件被 close
//IN_CLOSE_NOWRITE : 不可写文件被 close
//IN_OPEN : 文件被open
//IN_MOVED_FROM : 文件被移走,如 mv
//IN_MOVED_TO : 文件被移来，如 mv、cp
//IN_CREATE : 创建新文件
//IN_DELETE : 文件被删除，如 rm
//IN_DELETE_SELF : 自删除，即一个可执行文件在执行时删除自己
//IN_MOVE_SELF : 自移动，即一个可执行文件在执行时移动自己
//IN_UNMOUNT : 宿主文件系统被 umount
//IN_CLOSE : 文件被关闭，等同于(IN_CLOSE_WRITE | IN_CLOSE_NOWRITE)
//IN_MOVE : 文件被移动，等同于(IN_MOVED_FROM | IN_MOVED_TO)
//注：上面所说的文件也包括目录



#define EVENT_SIZE (sizeof(struct inotify_event))
#define  EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))



int in_move_to(struct inotify_event * event);
int in_move_from(struct inotify_event * event);
int delete(struct inotify_event * event);
int create(struct inotify_event * event);

int modify(struct inotify_event * event);
int listen_file(char *path);

#endif
