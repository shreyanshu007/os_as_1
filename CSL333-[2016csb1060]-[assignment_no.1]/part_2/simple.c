#include <linux/module.h>
#include <linux/kernel.h>   
#include <linux/init.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>


#define BIRTHDAY_COUNT      5

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lakshmanan");
MODULE_DESCRIPTION("A Simple Hello World module");


typedef struct _birthday 
{
    
    int day;
    int month;
    int year;
    struct list_head list;

}birthday;


LIST_HEAD(birthday_list);

int birthdayList_init(void) {

    printk(KERN_INFO "Loading the Module\n");


    birthday *person;
    int i = 0;
    for(i = 0; i < BIRTHDAY_COUNT; i++) 
    {

        person = kmalloc(sizeof(*person), GFP_KERNEL);

        person->day = 2 + i;
        person->month = 7 + i;
        person->year = 1995 + i;

        INIT_LIST_HEAD(&person->list);

        list_add_tail(&person->list, &birthday_list);

    }


    birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) 
    {

        printk(KERN_INFO "Birthday: Month %d Day %d Year %d\n",
                ptr->month,
                ptr->day,
                ptr->year);
    }

           return 0;
}


void birthdayList_exit(void) {

    printk(KERN_INFO "Removing the Module\n");


    birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) 
    {

        printk(KERN_INFO "Removing Birthday: Month %d Day %d Year %d\n",
                ptr->month,
                ptr->day,
                ptr->year);

        list_del(&ptr->list);

        kfree(ptr);
    
    }

    printk(KERN_INFO "Memory freed\n");

}


module_init(birthdayList_init);
module_exit(birthdayList_exit);


