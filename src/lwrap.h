/*
 * Yang Li
 * GPLv2
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
typedef void (*fun) ();
typedef struct data_t data_t;
typedef struct index_t index_t;
typedef struct justify_t justify_t;
typedef struct fun_t fun_t;
struct data_t {
  int dataindex;
  int byteheader;
  int wbytecount;
  int wcolcount;
  int annotation;
  int glyph;
  unsigned char val;
  data_t *before;
  data_t *after;
};
struct fun_t {
  fun filter;
  fun linebreak;
};
struct index_t {
  int val;
  index_t *incre;
  index_t *decre;
};
enum enumeration {
  CALLMAIN = 0,
  TERMINATOR = 0,
  EOS = 0,
  ALNUM = 0,
  SPACE = 32,
  NEWLINE = 10,
  FORMFEED = 12,
  PUNCT = 46,
  TAB = 9,
  ONEBYTEMAX = 11,
  TWOBYTEMAX = 22,
  THREEBYTEMAX = 33,
  FOURBYTEMAX = 44,
  NONEBYTEHEADER = 50,
  BYTEHEADER = 50,
  ONEBYTEHEADER = 128,
  ASCIISIZE = ONEBYTEHEADER,
  TWOBYTEHEADER = 224,
  THREEBYTEHEADER = 240,
  FOURBYTEHEADER = 244,
  UNICODESIZE = 256,
  FINITOUTBUFF = 0,
  FOUTBUFF = 1,
  NONEALNUMMIN = 0,
  NONEALNUMMAX = 32,
  ALNUMMIN = 33,
  ALNUMMAX = 126,
  MIDDLEBYTEMIN = 128,
  MIDDLEBYTEMAX = 191,
  ASCII = 0,
  ASCIIMIN = 0,
  ASCIIMAX = 127,
  LATIN = 1,
  LATINMIN = 194,
  LATINMAX = 200,
  IPA = 2,
  IPAMIN = 201,
  IPAMAX = 203,
  ACCENTS = 3,
  ACCENTSMIN = 204,
  ACCENTSMAX = 205,
  CYRIL = 4,
  CYRILMIN = 208,
  CYRILMAX = 212,
  ARMENI = 5,
  ARMENIMIN = 213,
  HEBREW = 6,
  HEBREWMIN = 214,
  HEBREWMAX = 215,
  ARABIC = 7,
  ARABICMIN = 216,
  ARABICMAX = 221,
  SYRIAC = 8,
  SYRIACMIN = 220,
  THAANA = 9,
  THAANAMIN = 222,
  NKO = 10,
  NKOMIN = 223,
  INDIC = 11,
  INDICMIN = 224,
  MISC = 12,
  MISCMIN = 225,
  SYMBOL = 13,
  SYMBOLMIN = 226,
  CJK = 14,
  CJKMIN = 227,
  CJKMAX = 233,
  ASIAN = 15,
  ASIANMIN = 234,
  HANGUL = 16,
  HANGULMIN = 235,
  HANGULMAX = 237,
  PUA = 17,
  PUAMIN = 238,
  FORMS = 18,
  FORMSMIN = 239,
} constant;
struct justify_t {
  int remain;
  int wcount;
  int index;
  justify_t *before;
  justify_t *after;
};
typedef struct self {
  int argc;
  int hcolsize;
  int hcolcount;
  int hbytecount;
  int wbytecount;
  int optchr;
  int debug;
  int wcolcount;
  int delimeter;
  int justifying;
  int endingspace;
  int justifyboundry;
  int justifysize;
  int getchar;
  int filesize;
  int maxwordsize;
  int linebreak;
  int handoffzone;
  int buffmultiple;
  int justifymultiple;
  int datasize;
  int readbuffsize;
  int writebuffboundry;
  int writebuffsize;
  int databoundry;
  int buffboundry;
  int stringsize;
  int readsize;
  int rindex;
  int oindex;
  int callsize;
  int flinebreaksize;
  int fmiddlebytesize;
  int initwritebuff;
  int initoutput;
  int readbuffrelay;
  int writebuffrelay;
  int displaymax;
  int fringboundry;
  int fringsize;
  int writesize;
  char **argv;
  char *string;
  char *currstring;
  char *progname;
  char *debugfile;
  char *printarg;
  char *strtolend;
  char *readbuff;
  char *writebuff;
  FILE *filep;
  FILE *filedebug;
  data_t *data;
  data_t *outdata;
  data_t *currdata;
  data_t *prevdata;
  data_t *nextdata;
  data_t *readdata;
  data_t *lbdata;
  index_t *outindex;
  index_t *curroutindex;
  index_t *readindex;
  index_t *currreadindex;
  fun_t **funicode;
  fun_t *fring;
  justify_t *justify;
  justify_t *currjustify;
  justify_t *outjustify;
  fun *call;
  fun version;
  fun foutput;
  fun freadfile;
  fun option;
  fun usage;
  fun delocate;
  fun reinitdata;
  fun justify_space;
  fun alocate;
  fun fjustify;
  fun flinebreak;
} self;
void usage(self ** me);
void version(self ** me);
void foutput(self ** me);
void alocate(self ** me);
void afring(self ** me);
void delocate(self ** me);
void freadfile(self ** me);
void option(self ** me);
void alnum(self ** me);
void nonealnum(self ** me);
void reinitdata(self ** me);
void justify_space(self ** me);
void fbuff(self ** me);
void newline(self ** me);
void space(self ** me);
void formfeed(self ** me);
void middlebyte(self ** me);
void invalidbyte(self ** me);
void twobyteheader(self ** me);
void fourbyteheader(self ** me);
void emit_justify(self ** me);
void fwritebuff(self ** me);
void finitfilter(self ** me);
void ffilter(self ** me);
void finitwritebuff(self ** me);
void output_remain(self ** me);
void frelay(self ** me);
void finitoutput(self ** me);
void fasciilinebreak(self ** me);
void strappend(char *str, char **strp, self ** me);
void cjkheader(self ** me);
void hangulheader(self ** me);
void indicheader(self ** me);
void mischeader(self ** me);
void symbolheader(self ** me);
void asianheader(self ** me);
void puaheader(self ** me);
void formsheader(self ** me);
void fhangullinebreak(self ** me);
void fhangulmiddlebyte(self ** me);
void flatinmiddlebyte(self ** me);
void aunicode(self ** me);
void avariable(self ** me);
void abuff(self ** me);
void acall(self ** me);
void fjustify(self ** me);
void lbnonealnum(self ** me);
void lbalnum(self ** me);
void lbspace(self ** me);
void lbnewline(self ** me);
void lbformfeed(self ** me);
void lbmiddlebyte(self ** me);
void lbinvalidbyte(self ** me);
void lbtwobyteheader(self ** me);
void lbfourbyteheader(self ** me);
void lbindicheader(self ** me);
void lbcjkheader(self ** me);
void lbmischeader(self ** me);
void lbsymbolheader(self ** me);
void lbasianheader(self ** me);
void lbpuaheader(self ** me);
void lbformsheader(self ** me);
void lbhangulheader(self ** me);
void flinebreak(self ** me);
