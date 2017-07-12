/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
inline void ffilter(self ** me)
{
  my.funicode[(unsigned char)my.readbuff[my.currreadindex->val]]->filter(me);
  if (my.currdata->val == EOS)
    return;
  my.flinebreak(me);
  my.call[my.initwritebuff] (me);
  my.foutput(me);
  my.prevdata = my.currdata;
  my.currdata = my.currdata->after;
  my.nextdata = my.currdata->after;
}

inline void frelay(self ** me)
{
  my.currreadindex = &my.readindex[0];
  for (my.rindex = 0; my.rindex < my.readsize; my.rindex++) {
    ffilter(me);
    my.currreadindex = my.currreadindex->incre;
  }
}

void freadfile(self ** me)
{
  do {
    my.readsize = fread(my.readbuff, 1, my.readbuffsize, my.filep);
    frelay(me);
  } while (my.readsize == my.readbuffsize);
  for (int i = 0; i < my.writebuffrelay; i++) {
    fwritebuff(me);
    my.foutput(me);
  }
  fwrite(my.writebuff, 1, my.curroutindex->val, stdout);
}
