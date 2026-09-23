#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <string.h>
//#define COLOR "\033[48;2;R;G;B"
#define BK "\x1B[38;02;02;02;010;48;2;039;039;049m"
#define RD "\x1B[31m"
#define GN "\x1B[32m"
#define YL "\x1B[33m"
#define BL "\x1B[34m"
#define MG "\x1B[35m"
#define CY "\x1B[36m"
#define WH "\x1B[40;37m"
#define NO "\x1B[0m" 
#define DGR "\033[48;2;39;39;49;38;2;90;90;100m"
#define GR "\033[48;2;39;39;49;38;2;119;119;169m"
#define FLAME "\033[48;2;89;89;209;38;2;22;21;103m"
#define ERR "\033[48;2;90;1;1;38;2;11;11;13m"
//# Flatfetch (shell and system info)
//# Most of terminals interpreter custom colors as blue or another colors
//#
int main() {
//# structs
    struct utsname buffer;
    struct sysinfo sysi;
//# cpu
    long cores = sysconf(_SC_NPROCESSORS_ONLN); 
    FILE *fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");
    unsigned int max_freq_khz;
    fscanf(fp, "%u", &max_freq_khz);
//# ram
    sysinfo(&sysi);
    long long total_ram_mb = (long long)sysi.totalram * sysi.mem_unit / (1024 * 1024);
    uname(&buffer);
//# misc
    char *ver = "1.0" ;
    char *user = getenv("USER");
    char x = 'x';
    int num = strlen(user) + 2 ;
    char* str = (char*)malloc(num + 3);
    memset(str, x, num); 
    str[num] = '\0'; 
    char path[40], shell[8];
    sprintf(path, "/proc/%d/comm", getppid());
    FILE *f = fopen(path, "r");
    fgets(shell, sizeof(shell), f);
//# show info
    printf("%s....._=XYYYX=_.....%s X %s\n",GR,NO, user);
    printf("%s._X&$$$$$$$$$$$&X_.%s X%s \n",GR,NO, str);
    printf("%s&############%s--%s###&%s X Kernel - %s\n",DGR,FLAME,DGR,NO, buffer.sysname);
    printf("%s@#@#@#%s=++%s##%s++-%s#@#@#%s X Release - %s\n",DGR,FLAME,DGR,FLAME,DGR,NO, buffer.release);
    printf("%s@@#@%sEX=%s@#@@%s+++%s#@@#@%s X Machine - %s\n",BK,FLAME,BK,FLAME,BK,NO, buffer.machine);
    printf("%s@@@@%s@@EEEXx==+%s@@@@@%s X Nodename - %s\n",BK,FLAME,BK,NO, buffer.nodename);
    printf("%sX@@@@%s@@@@EEX%s@@@@@@X%s X Version - %s\n",BK,FLAME,BK,NO, buffer.version);
    printf("%s=xX&@@@@@@@@@@@&Xx=%s X Shell - %s",BK,NO,shell);
    printf("%s...-=xX&@@@&Xx=-...%s X Total freq * cores - %.2f MHZ * %ld CORES\n",BK,NO,max_freq_khz / 1000.0, cores);
    printf("                    X Total Ram Vol - %lld MB\n", total_ram_mb);
    printf("%sX%sX%sX%sX%sX%sX%sX%sX%sX%sX%sX%sX\n",BK,DGR,GR,WH,RD,YL,GN,CY,BL,MG,FLAME,ERR,NO);
    fclose(f);free(str);
}
