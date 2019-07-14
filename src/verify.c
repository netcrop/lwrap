/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
self *me = (self *) NULL;
int main(int argc, char *argv[])
{
    avariable();
    me->argc = argc;
    me->argv = argv;
    option();
    alocate();
    freadfile();
    delocate();
    return 0;
}
