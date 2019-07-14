/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
inline void ffilter()
{
    me->funicode[(unsigned char)me->readbuff[me->currreadindex->val]]->filter(me);
    if (me->currdata->val == EOS)
        return;
    me->flinebreak(me);
    me->call[me->initwritebuff] (me);
    me->foutput(me);
    me->prevdata = me->currdata;
    me->currdata = me->currdata->after;
    me->nextdata = me->currdata->after;
}

inline void frelay()
{
    me->currreadindex = &me->readindex[0];
    for (me->rindex = 0; me->rindex < me->readsize; me->rindex++) {
        ffilter(me);
        me->currreadindex = me->currreadindex->incre;
    }
}

void freadfile()
{
    do {
        me->readsize = fread(me->readbuff, 1, me->readbuffsize, me->filep);
        frelay(me);
    } while (me->readsize == me->readbuffsize);
    for (int i = 0; i < me->writebuffrelay; i++) {
        fwritebuff(me);
        me->foutput(me);
    }
    fwrite(me->writebuff, 1, me->curroutindex->val, stdout);
}
