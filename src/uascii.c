/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)
inline void flinebreak(self ** me)
{
  if (my.hcolcount <= my.hcolsize)
    return;
  if (my.currdata->val == EOS)
    return;
  if ((my.linebreak = my.currdata->dataindex - my.currdata->wbytecount) < 0)
    my.linebreak += my.databoundry;
  my.lbdata = &my.data[my.linebreak];
  my.hcolcount = my.currdata->wcolcount;
  my.hbytecount = my.currdata->wbytecount;
  my.funicode[my.lbdata->val]->linebreak(me);
  if (my.currjustify->remain != 0 && my.currjustify->wcount == 0) ;
  else
    my.currjustify = my.currjustify->after;
}

inline void lbspace(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  if (my.endingspace == 1) {
    my.lbdata->annotation = NEWLINE;
    return;
  }
  my.lbdata->val = NEWLINE;
}

inline void lbnewline(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbnonealnum(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbalnum(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  my.lbdata->annotation = NEWLINE;
}

inline void lbformfeed(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  my.lbdata->annotation = NEWLINE;
}

inline void lbmiddlebyte(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
  my.lbdata->annotation = NEWLINE;
}

inline void lbinvalidbyte(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbtwobyteheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbfourbyteheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbindicheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbcjkheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbmischeader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbsymbolheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbasianheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbpuaheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}

inline void lbformsheader(self ** me)
{
  my.currjustify->remain = my.currdata->wcolcount;
}
