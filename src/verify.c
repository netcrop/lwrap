#include "lwrap.h"
#define my (*me)
int main(int argc, char *argv[])
{
  self *me=(self*)NULL;
  avariable(&me);
  my.argc=argc;
  my.argv=argv;
  my.option(&me);
  my.alocate(&me);
  my.freadfile(&me);
  my.delocate(&me);
  return 0;
}
