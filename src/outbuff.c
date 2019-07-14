/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
inline void foutput()
{
    if (me->curroutindex->val < me->writesize)
        return;
    fwrite(me->writebuff, 1, me->curroutindex->val, stdout);
    me->curroutindex = &me->outindex[0];
}

void finitwritebuff()
{
    if (me->currdata->dataindex < me->writebuffrelay)
        return;
    me->initwritebuff = FOUTBUFF;
    fwritebuff(me);
}

inline void fwritebuff()
{
    if (me->outdata->val == EOS) {
        me->outdata->annotation = EOS;
        me->outdata = me->outdata->after;
        return;
    }
    if (me->outdata->annotation == NEWLINE) {
        me->writebuff[me->curroutindex->val] = me->outdata->val;
        me->curroutindex = me->curroutindex->incre;
        me->writebuff[me->curroutindex->val] = NEWLINE;
        me->curroutindex = me->curroutindex->incre;
        me->outjustify->wcount = 0;
        me->outjustify = me->outjustify->after;
        me->outdata->val = EOS;
        me->outdata->annotation = EOS;
        me->outdata = me->outdata->after;
        return;
    }
    if (me->outdata->val == SPACE) {
        me->fjustify(me);
        me->outdata->val = EOS;
        me->outdata->annotation = EOS;
        me->outdata = me->outdata->after;
        return;
    }
    if (me->outdata->val == NEWLINE) {
        me->writebuff[me->curroutindex->val] = NEWLINE;
        me->curroutindex = me->curroutindex->incre;
        me->outjustify->wcount = 0;
        me->outjustify = me->outjustify->after;
        me->outdata->val = EOS;
        me->outdata->annotation = EOS;
        me->outdata = me->outdata->after;
        return;
    }

    me->writebuff[me->curroutindex->val] = me->outdata->val;
    me->curroutindex = me->curroutindex->incre;
    me->outdata->val = EOS;
    me->outdata->annotation = EOS;
    me->outdata = me->outdata->after;
}
