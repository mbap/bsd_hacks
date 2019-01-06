#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include <sys/syscall.h>
#include <sys/param.h>
#include <sys/module.h>

int eprintf(const char * restrict format, ...);

int
main(int argc, char *argv[]) {
    int syscall_num = 0;
    struct module_stat stat = {0};

    if (argc != 3) {
        eprintf("Usage: %s <syscall name> <string>\n", argv[0]);
        return 1;
    }

    stat.version = sizeof(struct module_stat);
    if (modstat(modfind(argv[1]), &stat) == -1) {
        /* Note: kldstat -v is your friend. */
        eprintf("Failed to stat '%s' syscall mod: %s.\n",
            argv[1], strerror(errno));
        return 1;
    }

    if (syscall(stat.data.intval, argv[2])) {
        eprintf("Error occured during syscall %d.\n", argv[1]);
        return 1;
    }
    return 0;
}

int
eprintf(const char * restrict format, ...)
{
    int ret = 0;
    va_list arg_list;

    va_start(arg_list, format);
    ret = vfprintf(stderr, format, arg_list);
    va_end(arg_list);
    return ret;
}
