#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <string.h>
//# Flatfetch (shell and system info)
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
    printf("....._=XYYYX=_..... X %s\n", user);
    printf("._X&$$$$$$$$$$$&X_. X%s \n", str);
    printf("&############--###& X Kernel - %s \n", buffer.sysname);
    printf("@#@#@#=++##++-#@#@# X Release - %s \n", buffer.release);
    printf("@@#@x==@#@@+++#@@#@ X Machine - %s \n", buffer.machine);
    printf("@@@@FFxxx====+@@@@@ X Nodename - %s \n", buffer.nodename);
    printf("X@@@@FFFFxx=@@@@@@X X Version - %s \n", buffer.version);
    printf("=xX&@@@@@@@@@@@&Xx= X Shell - %s", shell);
    printf("...-=xX&@@@&Xx=-... X Total freq * cores - %.2f MHZ * %ld CORES \n", max_freq_khz / 1000.0, cores);
    printf("                    X Total Ram Vol - %lld MB  \n", total_ram_mb);
    fclose(f);free(str);return 0;
}
