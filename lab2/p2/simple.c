#include <linux/list.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

static LIST_HEAD(birthday_list);

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

int simple_init(void) {
	struct birthday *person;

	//Person 1
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 17;
	person->month = 11;
	person->year = 1998;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	//Person 2
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 28;
	person->month = 12;
	person->year = 2000;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	//Person 3
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 31;
	person->month = 03;
	person->year = 2003;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	//Person 4
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 05;
	person->month = 10;
	person->year = 1997;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	//Person 5
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 12;
	person->month = 11;
	person->year = 1999;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	printk(KERN_INFO "Loading Module!\n");
	printk(KERN_INFO "Constructing List!\n");
	
	list_for_each_entry(person, &birthday_list, list) {
		printk(KERN_INFO "Day: %d\nMonth: %d\nYear: %d\n", person->day, person->month, person->year);
	}
	return 0;
}	

void simple_exit(void){
	struct birthday *person, *next;
	list_for_each_entry_safe(person, next, &birthday_list, list) {
		printk(KERN_INFO "Returning free memory back to kernel!");
		list_del(&person->list);
		kfree(person);
	}
	printk(KERN_INFO "Removing Module!\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Amit Srivastava");
MODULE_DESCRIPTION("Simple Module");