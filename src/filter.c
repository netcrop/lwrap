/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"

inline void ffilter()
{
    my.funicode[(unsigned char)my.readbuff[my.currreadindex->val]]->filter();
    if (my.currdata->val == EOS)
        return;
    my.flinebreak();
    my.call[my.initwritebuff] ();
    my.foutput();
    my.prevdata = my.currdata;
    my.currdata = my.currdata->after;
    my.nextdata = my.currdata->after;
}

inline void frelay()
{
    my.currreadindex = &my.readindex[0];
    for (my.rindex = 0; my.rindex < my.readsize; my.rindex++) {
        ffilter();
        my.currreadindex = my.currreadindex->incre;
    }
}

void freadfile()
{
    do {
        my.readsize = fread(my.readbuff, 1, my.readbuffsize, my.filep);
        frelay();
    } while (my.readsize == my.readbuffsize);
    for (int i = 0; i < my.writebuffrelay; i++) {
        fwritebuff();
        my.foutput();
    }
    fwrite(my.writebuff, 1, my.curroutindex->val, stdout);
}
