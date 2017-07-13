/*
 * Yang Li
 * GPLv2
 */

#include "lwrap.h"
#define my (**me)

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
