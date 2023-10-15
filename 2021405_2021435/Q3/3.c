#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include<linux/sched/signal.h>


int simple_init(void){
    int count=0;
    struct task_struct *task;

    for_each_process(task){
        if (task->state==TASK_RUNNING){
            count++;
        }
    }

    printk(KERN_INFO "Number of running processes: %d\n",count);
    return 0;
}

void simple_exit(void){
    printk(KERN_INFO "Exiting process count module\n");
}

module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Vipul");