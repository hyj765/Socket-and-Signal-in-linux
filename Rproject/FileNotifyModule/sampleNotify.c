#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024* (EVENT_SIZE + 16))

int main(){

	int fd,wd;

	fd = inotify_init();
	if(0 > fd){
		return 0;
	}

	wd = inotify_add_watch(fd,"/home/ori",IN_MODIFY | IN_CREATE | IN_DELETE);
	if(0 > wd){
		printf("wd error");
		return 0;
	}
	char buffer[EVENT_BUF_LEN];

	printf("watch is running now...\n");
        while(1){

                int len = read(fd,buffer,EVENT_BUF_LEN);
                if(0 > len){
                 return 0;
                }

                int i =0;

                while(i < len){
                        struct inotify_event *event = (struct inotify_event *)&buffer[i];
                       if(event->len)
                       {
			if(event->mask & IN_CREATE){
				printf("File %s was Created.\n",event->name);
			}else if(event->mask & IN_MODIFY){
				printf("File %s was Modified.\n",event->name);
			}else if(event->mask & IN_DELETE){
				printf("File %s was Deleted.\n",event->name);
			}
		       }
			
			i += EVENT_SIZE + event->len;
		}
		
	}


        inotify_rm_watch(fd,wd);
	close(fd);	

	return 0;
}
