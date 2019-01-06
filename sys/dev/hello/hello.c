#include <sys/param.h>

#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/systm.h>

#include <sys/cdefs.h>
#include <sys/types.h>

static int hello_handler(module_t, int , void *);

static moduledata_t hello_mod_data = {
    .name = "hello",
    .evhand = &hello_handler,
    .priv = NULL
};

DECLARE_MODULE(hello, hello_mod_data, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);

static int
hello_handler(module_t mod, int modtype /* modeventtype_t */, void *arg)
{

    int error = 0;

    switch (modtype) {
    case MOD_LOAD:
        uprintf("Hello, world!\n");
        break;
    case MOD_UNLOAD:
        uprintf("Goodbye, world!\n");
        break;
    case MOD_SHUTDOWN:
    case MOD_QUIESCE:
    default:
        error = EOPNOTSUPP;
        break;
    }

    return error;
}


