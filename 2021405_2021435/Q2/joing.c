#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/time.h>

#define NUMBER_OF_POLICIES 3

struct PolicyData{
    const char* name;
    int pol;
    int prior;
    const char* f;
};

struct PolicyData policies[NUMBER_OF_POLICIES]={{"FIFO",SCHED_FIFO,99,"FIFO.txt"},{"RR",SCHED_RR,1,"RR.txt"},{"OTHER",SCHED_OTHER,0,"OTHER.txt"}};

void ExecPolicy(const struct PolicyData* pol){
    struct timeval start_time, etime;
    pid_t cpid;

    gettimeofday(&start_time, NULL);
    cpid = fork();

    if (cpid==-1){
        perror("Fork failed");
    }

    if (cpid==0){
        struct sched_param parameter;
        parameter.sched_priority=pol->prior;
        if (sched_setscheduler(0,pol->pol,&parameter)==-1){
            perror("Error setting up scheduler");
            exit(1);
        }

        char *const args[]={"./Counter", NULL};
        execvp("./Counter",args);
        perror("Execvp failed");
        exit(1);
    } 
    
    else{
        wait(NULL);
        gettimeofday(&etime, NULL);
        double exectime=((etime.tv_sec)-(start_time.tv_sec))+((etime.tv_usec)-(start_time.tv_usec))/(1e6);
        printf("Exec time for %s: %.6f secs\n",pol->name,exectime);
        FILE *filepoint=fopen(pol->f,"w");
        fprintf(filepoint, "%.6f \n",exectime);
        fclose(filepoint);
    }
}

int main() {
    for (int i=0;i<NUMBER_OF_POLICIES;i++){
        pid_t cpid=fork();
        if (cpid==0){
            ExecPolicy(&policies[i]);
            exit(0);
        }
    }

    for (int i=0;i<NUMBER_OF_POLICIES;i++){
        wait(NULL);
    }
    
    return 0;
}