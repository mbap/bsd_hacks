#include <stdio.h>

/**
 * test is the type of a function.
 *     the declaration of abc could use test instead of int abc(int) -> test abc;
 *     later it could be defined in the same way.
 *
 * test2 is the type of function pointer.
 *    test * is the type of function pointer.
 *    There is no difference between (test2) and (test *)
 *
 * This is a good stack overflow post with additional information:
 *     https://stackoverflow.com/questions/44148406/typedef-function-vs-function-pointer
 *     https://stackoverflow.com/questions/4574985/can-a-function-prototype-typedef-be-used-in-function-definitions?lq=1
 *
 */

typedef int test(int x);
typedef int (*test2)(int x);

int abc(int);
test *xyz();
test2 lmn();

int
main(void)
{
    test *ptr = &abc;
    (*ptr)(4);

    test2 ptr2 = &abc;
    (*ptr)(5);

    test2 ptr3 = xyz();
    (*ptr3)(6);

    test2 ptr4 = lmn();
    (*ptr4)(7);

    return 0;

}

int abc(int y) {
    printf("Testing %d\n", y);
    return y;
}

test *xyz() {
    return &abc;
}

test2 lmn() {
    return &abc;
}
