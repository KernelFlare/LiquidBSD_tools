#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <string.h>
#ifndef __linux__
#include <sys/sysctl.h> // Открываем sysctl-магию для BSD систем
#endif
//#define COLOR "\033[48;2;R;G;B"
#define BK "\x1B[38;02;02;02;02;48;2;22;22;22m"
#define RD "\x1B[31m"
#define GN "\x1B[32m"
#define YL "\x1B[33m"
#define BL "\x1B[34m"
#define MG "\x1B[35m"
#define CY "\x1B[36m"
#define WH "\x1B[40;37m"
#define NO "\x1B[0m" 
#define DGR "\033[48;2;22;22;22;38;2;36;36;36m"
#define GR "\033[48;2;22;22;22;38;2;63;63;63m"
#define FLAME "\033[48;2;133;0;0;38;2;43;0;0m"
#define CLEAR "\033[2J\033[1;1H"

int main(void);
int pages_size_valid(long p, long s);

int
pages_size_valid(long p, long s) {
    return (p > 0 && s > 0);
}

int
main(void) {
    //# structs
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        perror("bname: uname failed");
        return 1;
    }
    //# cpu
    long cores = sysconf(_SC_NPROCESSORS_ONLN); 
    if (cores < 1) cores = 1;
    FILE *fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");
    unsigned int max_freq_khz;
    fscanf(fp, "%u", &max_freq_khz);
    //# ram n swap
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    long long total_ram_mb = 0;
    if (pages_size_valid(pages, page_size)) {
        total_ram_mb = ((long long)pages * page_size) / (1024 * 1024);
    }
    long long total_swap_mb = 0;
    #if defined(__linux__)
    long swap_pages = sysconf(_SC_AVPHYS_PAGES);
    if (swap_pages > 0 && page_size > 0) {
        total_swap_mb = ((long long)swap_pages * page_size) / (1024 * 1024);
    }
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
    int mib[3];
    size_t len;
    mib[0] = CTL_VM;
    mib[1] = VM_SWAPUSAGE;
    struct {
        int64_t total;
        int64_t reserved;
        int64_t allocated;
    } swap_info;
    len = sizeof(swap_info);
    if (sysctl(mib, 2, &swap_info, &len, NULL, 0) == 0) {
        total_swap_mb = swap_info.total / (1024 * 1024);
    }
#else
    total_swap_mb = 0; 
#endif
    //# misc
    char *ver = "26.09.23" ;
    //# Get username
    char *user = "anon";
    user = getenv("USER");
    user = getenv("LOGNAME");
    //# Get shell and tty
    char *tty_dev = ttyname(0);
    if (!tty_dev) tty_dev = "/dev/console";
    char *shell = "unkn";
    char *env_shell = getenv("SHELL");
    if (env_shell) shell = env_shell;
    if (env_shell) strncpy(shell, env_shell, sizeof(shell) - 1);
    size_t num = strlen(user) + 2;
    char *str = (char *)malloc(num + 1);
    if (str != NULL) {
        memset(str, 'x', num); 
        str[num] = '\0';
    } else str = "xx";
    //# show info
    printf("%s...@@@............%s X [%s]\n",FLAME,NO, user);
    printf("%s..@..@@##.........%s X%s \n",FLAME,NO, str);
    printf("%s..@.##@###........%s X Kernel - [%s]\n",FLAME,NO, buffer.sysname);
    printf("%s....##...0#8......%s X Release - [%s]\n",FLAME,NO, buffer.release);
    printf("%s....3#..00.#8.....%s X Machine - [%s]\n",FLAME,NO, buffer.machine);
    printf("%s.....3#00.00#8....%s X Nodename - [%s]\n",FLAME,NO, buffer.nodename);
    printf("%s......3#..0.00#...%s X Version - [%s]\n",FLAME,NO, buffer.version);
    printf("%s.......##00.00##..%s X Shell at Input - [%s] at [%s]\n",FLAME,NO,shell,tty_dev);
    printf("%s........##.00.#...%s X Total freq * cores - [%.2f] MHZ * [%ld] CORES\n",FLAME,NO,max_freq_khz / 1000.0, cores);
    printf("%s.........####.....%s X Total Ram + Swap Vol - [%lld] + [%lld] MB\n",FLAME,NO, total_ram_mb, total_swap_mb);
    printf("%sX%sX%sX%sX%sX%sX%sX%sX%sX%sX%sX%sX       X PXpG ver - [%s]\n",BK,DGR,GR,WH,RD,YL,GN,CY,BL,MG,FLAME,NO,ver);
    if (strcmp(buffer.sysname, "LiquidBSD") == 0) {
        printf("bname: I'm home, lol\n");
    }
    if (str != NULL && strcmp(str, "xx") != 0) free(str);
    return 0;
}
