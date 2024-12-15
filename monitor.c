#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>

void get_cpu_usage() {
    FILE *fp;
    char buffer[128];
    long user, nice, system, idle, iowait, irq, softirq, total, total_idle;

    // 获取CPU的使用信息
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Unable to open /proc/stat");
        return;
    }

    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(fp);

    total = user + nice + system + idle + iowait + irq + softirq;
    total_idle = idle + iowait;
    float cpu_usage = (float)(total - total_idle) / total * 100.0;
    printf("CPU使用率: %.2f%%\n", cpu_usage);
    printf("Debug: CPU usage function ran successfully.\n");
}

void get_memory_usage() {
    FILE *fp;
    char buffer[256];
    long total_memory, free_memory, buffers, cached;

    // 获取内存的总量和剩余量
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Unable to open /proc/meminfo");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, "MemTotal:")) {
            sscanf(buffer, "MemTotal: %ld kB", &total_memory);
        } else if (strstr(buffer, "MemFree:")) {
            sscanf(buffer, "MemFree: %ld kB", &free_memory);
        } else if (strstr(buffer, "Buffers:")) {
            sscanf(buffer, "Buffers: %ld kB", &buffers);
        } else if (strstr(buffer, "Cached:")) {
            sscanf(buffer, "Cached: %ld kB", &cached);
        }
    }
    fclose(fp);

    // 计算实际使用的内存
    long used_memory = total_memory - free_memory - buffers - cached;
    float memory_usage = (float)used_memory / total_memory * 100.0;
    printf("内存使用率: %.2f%%\n", memory_usage);
    printf("Debug: Memory usage function ran successfully.\n");
}

// 获取Disk使用信息
void get_disk_usage() {
    struct statvfs buf;
    if (statvfs("/", &buf) != 0) {
        perror("statvfs error");
        return;
    }

    unsigned long total_space = buf.f_blocks * buf.f_frsize;
    unsigned long free_space = buf.f_bfree * buf.f_frsize;
    unsigned long used_space = total_space - free_space;
    float disk_usage = (float)used_space / total_space * 100.0;
    
    printf("磁盘使用率: %.2f%%\n", disk_usage);
    printf("Debug: Disk usage function ran successfully.\n");
}

int main() {
    while (1) {
        printf("\n系统监视器：\n");
        get_cpu_usage();
        get_memory_usage();
        get_disk_usage();
        sleep(2);  // 每2秒刷新一次
    }
    return 0;
}
