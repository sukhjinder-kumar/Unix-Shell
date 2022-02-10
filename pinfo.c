#include "headers.h"

void pinfo_pid(pid_t pid) {
    char filename[1000];
    sprintf(filename, "/proc/%d/stat", pid);
    FILE *f = fopen(filename, "r");
    char state;
    long unsigned int v_size;
    char comm[1000];
    int pgrp, group_id;
    // fscanf(f,"%*d %s %c %*d %d %*d %*d %d %*u %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %*ld %*ld %*llu %lu", comm, &state, &v_size);
    fscanf(f,"%*d %s %c %*d %d %*d %*d %d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu", comm, &state,&pgrp, &group_id, &v_size);

    // 1. print pid
    printf("pid -- %d\n", pid);

    // 2. process status
    printf("Process status -- %c", state);
    if(pgrp == group_id) printf("+");
    printf("\n");
    // 3. memory
    printf("memory -- %lu\n", v_size);

    // 4. executable path
    printf("executabale path -- %s\n", comm);

}

void pinfo_hub(struct tokens t) {
    pid_t shell_pid = getpid();
    if(t.size == 1) pinfo_pid(shell_pid);
    if(t.size > 1) {
        pid_t some_pid;
        sscanf(t.string[1],"%d",&some_pid);
        pinfo_pid(some_pid);
    }
}