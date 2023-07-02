#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))

int main() {
    int length, i = 0;
    int fd;
    int wd;
    int buffsize = 1024 * (EVENT_SIZE + 16);
    char buffer[BUF_LEN];

    fd = inotify_init();
    if (fd < 0) {
        return -1;
    }

    wd = inotify_add_watch(fd, ".", IN_CREATE | IN_DELETE);
    if (wd < 0) {
        return -1;
    }

    while (1) {
        i = 0;
        length = read(fd, buffer, BUF_LEN);
        if (length < 0) {
            return -1;
        }

/*
struct inotify_event
{
int wd;  inotify descriptor
uint32_t mask; watch mask 
uint32_t cookie; 
uint32_t len; 
char name __flexarr; 
};
*/
//	inotify 구조 

       
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->mask & IN_CREATE) {
                if (event->mask & IN_ISDIR)
                    printf("directory create: %s\n", event->name);
                else
                    printf("file create: %s\n", event->name);
            } else if (event->mask & IN_DELETE) {
                if (event->mask & IN_ISDIR)
                    printf("directory delete: %s\n", event->name);
                else
                    printf("file delete: %s\n", event->name);
            }
            i += EVENT_SIZE + event->len;
        }
    }
		
    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}
