/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (*me)
int main(int argc, char *argv[])
{
    me = (self *) NULL;
    avariable(&me);
    me->argc = argc;
    me->argv = argv;
   # me->option(&me);
   # me->alocate(&me);
   # me->freadfile(&me);
    me->delocate(&me);
    return 0;
}
