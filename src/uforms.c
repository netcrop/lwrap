#include "lwrap.h"
#define my (**me)
void formsheader()
{
    me->currdata->val = (unsigned char)me->readbuff[me->currreadindex->val];
    me->currdata->byteheader = 30;
    me->wcolcount = me->wbytecount = 0;
    me->currdata->wcolcount = 2;
    me->currdata->wbytecount = 1;
    me->currjustify->wcount++;
    me->hcolcount += 2;
    me->hbytecount++;
}

inline void lbformsheader()
{
    me->currjustify->remain = me->currdata->wcolcount;
}
