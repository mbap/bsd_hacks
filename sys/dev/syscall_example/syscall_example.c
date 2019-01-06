#include <sys/param.h>

#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>

#include <sys/systm.h>
#include <sys/types.h>

struct sc_example_args {
    char *str;
};

static int
sc_example(struct thread *td, void *syscall_args)
{
    struct sc_example_args *args;
    args = (struct sc_example_args *)syscall_args;
    printf("XXX: %s\n", args->str);
    return 0;
}

static struct sysent sc_example_sysent = {
    .sy_narg = 1,
    .sy_call = sc_example
};

static int offset = NO_SYSCALL;

static int
load(module_t mod, int mod_type, void *arg)
{
    int error = 0;

    switch (mod_type) {
	case MOD_LOAD:
        uprintf("Syscall loaded offset %d.\n", offset);
        break;
	case MOD_UNLOAD:
        uprintf("Syscall unloaded offset %d.\n", offset);
        break;
	case MOD_SHUTDOWN:
	case MOD_QUIESCE:
    default:
        error = EOPNOTSUPP;
        break;
    }
    return error;
}

SYSCALL_MODULE(sc_example, &offset, &sc_example_sysent, load, NULL);

