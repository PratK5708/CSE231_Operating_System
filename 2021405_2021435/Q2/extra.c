#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sched.h>

int main(){
    struct timeval start_time, end_time;
    pid_t childpid;

    //Creating child process
    childpid = fork();

    if (childpid==-1){
        perror("Fork failed");
        return 1;
    }

    gettimeofday(&start_time,NULL);

    if (childpid==0){

        //Setting FIFO for child process..
        struct sched_param param;
        param.sched_priority=50;


        if(sched_setscheduler(getpid(),SCHED_RR,&param)==-1){
            perror("Error in settign up FIFO scheduler");
            exit(1);
        }

        //Executing Counter.exe using execvp
        char *const args[]={"./Counter",NULL};
        execvp("./Counter",args);






        
        //execvp fails, it report an error
        perror("Execvp failed");
        exit(1);
    }





    else{
        wait(NULL); //Waiting for child process complete



        //Current time
        gettimeofday(&end_time,NULL);

        //Execution time in secs
        double exectime=((end_time.tv_sec)-(start_time.tv_sec))+((end_time.tv_usec)-(start_time.tv_usec))/(1e6);

        printf("Time of Execution for RR is %.6f secs\n",exectime);
    }
















    return 0;
}
