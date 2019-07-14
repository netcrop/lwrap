/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)

void fourbyteheader()
{
    me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
    me->currdata->byteheader = 40;
    me->wcolcount = me->wbytecount = 0;
    me->currdata->wcolcount = 1;
    me->currdata->wbytecount = 1;
    me->currjustify->wcount++;
    me->hbytecount++;
}

inline void lbfourbyteheader()
{
    me->currjustify->remain = me->currdata->wcolcount;
}
