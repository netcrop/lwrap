/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
void cyrilheader()
{
    me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
    me->currdata->byteheader = 20;
    me->currdata->wcolcount = ++me->wcolcount;
    me->currdata->wbytecount = ++me->wbytecount;
    me->hbytecount++;
}

inline void fcyrilmiddlebyte()
{
    me->hbytecount++;
    me->hcolcount++;
    me->currdata->wbytecount = ++me->wbytecount;
    me->currdata->wcolcount = me->wcolcount;
}

inline void lbcyrilheader()
{
    me->currjustify->remain = me->currdata->wcolcount;
}
