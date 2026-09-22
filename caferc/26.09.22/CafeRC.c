#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>

void makeRC(void);
void spinner(void);
void run(void);
void setup(void);
int main();

char *RCpath = "/etc/RC";
char *initpath = "init";
char *ver = "26.09.22";
struct utsname buffer;

void
makeRC(void){
    if (access(RCpath, F_OK) != 0) {
        FILE *default_cfg = fopen(RCpath, "w");
        if (default_cfg != NULL) {
            fprintf(default_cfg, "#!/bin/env sh\n");
            fprintf(default_cfg, "export PATH=/bin:/usr/bin\n");
            fprintf(default_cfg, "exec /bin/login");
            fclose(default_cfg);
            printf("CafeRC: Created [RC] file at [%s]\n", RCpath);
        }
    }
        if (access(initpath, F_OK) != 0) {
        FILE *default_cfg = fopen(initpath, "w");
        if (default_cfg != NULL) {
            fprintf(default_cfg, "#!/bin/env sh\n");
            fprintf(default_cfg, "/bin/CafeRC\n");
            fclose(default_cfg);
            printf("CafeRC: Created [INIT] file at [%s]\n", initpath);
        }
    }
}

void
spinner(void){
    printf("\b/");
    fflush(stdout);
    usleep(300000);
    printf("\b-");
    fflush(stdout);
    usleep(300000);
    printf("\b\\");
    fflush(stdout);
    usleep(300000);
    printf("\b|");
    fflush(stdout);
    usleep(300000);
}

void
run(void){
    system("/etc/RC");
}

void
setup(void){
    if (uname(&buffer) != 0) {
        perror("uname");
        printf("CafeRC: Couldn\'t use [UNAME]\n");
    }
    if (rand() % 10 == 7) {
        printf("CafeRC: HEY EVERY !! IT'S ME!!!\n");
        usleep(3000000);
        printf("CafeRC: EV3RY BUDDY 'S FAVORITE [[Old-style RCinit 2026]]\n");
        usleep(3000000);
        printf("CafeRC: CA");
        usleep(300000);
        printf("\b\bCAFERC %s ON %s \n",ver,buffer.sysname);
    }
    else printf("CafeRC %s on %s, Checking for [RC] at [%s]\n",ver, buffer.sysname,RCpath);
    if (buffer.sysname == "LikuidBSD") {
        printf("CafeRC:I\'M HOME??? ALREADY??? IN BIG")
        system("/bin/date");
        printf("????\n");
    }
}

int
main(){
    makeRC();
    usleep(3000000);
    setup();
    usleep(3000000);
    printf("CafeRC: Starting the [RC] file\n");
    printf("Loading:  ");
    for(int i = 0; i < 3; i++) spinner(); 
    printf("\n");
    run();
}
