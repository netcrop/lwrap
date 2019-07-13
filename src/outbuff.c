/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
inline void foutput(self ** me)
{
    if (my.curroutindex->val < my.writesize)
        return;
    fwrite(my.writebuff, 1, my.curroutindex->val, stdout);
    my.curroutindex = &my.outindex[0];
}

void finitwritebuff(self ** me)
{
    if (my.currdata->dataindex < my.writebuffrelay)
        return;
    my.initwritebuff = FOUTBUFF;
    fwritebuff(me);
}

inline void fwritebuff(self ** me)
{
    if (my.outdata->val == EOS) {
        my.outdata->annotation = EOS;
        my.outdata = my.outdata->after;
        return;
    }
    if (my.outdata->annotation == NEWLINE) {
        my.writebuff[my.curroutindex->val] = my.outdata->val;
        my.curroutindex = my.curroutindex->incre;
        my.writebuff[my.curroutindex->val] = NEWLINE;
        my.curroutindex = my.curroutindex->incre;
        my.outjustify->wcount = 0;
        my.outjustify = my.outjustify->after;
        my.outdata->val = EOS;
        my.outdata->annotation = EOS;
        my.outdata = my.outdata->after;
        return;
    }
    if (my.outdata->val == SPACE) {
        my.fjustify(me);
        my.outdata->val = EOS;
        my.outdata->annotation = EOS;
        my.outdata = my.outdata->after;
        return;
    }
    if (my.outdata->val == NEWLINE) {
        my.writebuff[my.curroutindex->val] = NEWLINE;
        my.curroutindex = my.curroutindex->incre;
        my.outjustify->wcount = 0;
        my.outjustify = my.outjustify->after;
        my.outdata->val = EOS;
        my.outdata->annotation = EOS;
        my.outdata = my.outdata->after;
        return;
    }

    my.writebuff[my.curroutindex->val] = my.outdata->val;
    my.curroutindex = my.curroutindex->incre;
    my.outdata->val = EOS;
    my.outdata->annotation = EOS;
    my.outdata = my.outdata->after;
}
