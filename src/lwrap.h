/*
 * Yang Li
 * GPLv2
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "config.h"
typedef void (*fun)();
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
    GREEK = 4,
    GREEKMIN = 206,
    GREEKMAX = 207,
    CYRIL = 5,
    CYRILMIN = 208,
    CYRILMAX = 212,
    ARMENI = 6,
    ARMENIMIN = 213,
    HEBREW = 7,
    HEBREWMIN = 214,
    HEBREWMAX = 215,
    ARABIC = 8,
    ARABICMIN = 216,
    ARABICMAX = 221,
    SYRIAC = 9,
    SYRIACMIN = 220,
    THAANA = 10,
    THAANAMIN = 222,
    NKO = 11,
    NKOMIN = 223,
    INDIC = 12,
    INDICMIN = 224,
    MISC = 13,
    MISCMIN = 225,
    SYMBOL = 14,
    SYMBOLMIN = 226,
    CJK = 15,
    CJKMIN = 227,
    CJKMAX = 233,
    ASIAN = 16,
    ASIANMIN = 234,
    HANGUL = 17,
    HANGULMIN = 235,
    HANGULMAX = 237,
    PUA = 18,
    PUAMIN = 238,
    FORMS = 19,
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
void usage(void);
void version(void);
void foutput(void);
void alocate(void);
void afring(void);
void delocate(void);
void freadfile(void);
void option(void);
void alnum(void);
void nonealnum(void);
void reinitdata(void);
void justify_space(void);
void fbuff(void);
void newline(void);
void space(void);
void formfeed(void);
void middlebyte(void);
void invalidbyte(void);
void fourbyteheader(void);
void emit_justify(void);
void fwritebuff(void);
void finitfilter(void);
void ffilter(void);
void finitwritebuff(void);
void output_remain(void);
void frelay(void);
void finitoutput(void);
void fasciilinebreak(void);
void strappend(char *str, char **strp);
void cjkheader(void);
void hangulheader(void);
void indicheader(void);
void mischeader(void);
void symbolheader(void);
void asianheader(void);
void puaheader(void);
void formsheader(void);
void fhangullinebreak(void);
void fhangulmiddlebyte(void);
void flatinmiddlebyte(void);
void aunicode(void);
void avariable();
void abuff(void);
void acall(void);
void fjustify(void);
void lbnonealnum(void);
void lbalnum(void);
void lbspace(void);
void lbnewline(void);
void lbformfeed(void);
void lbmiddlebyte(void);
void lbinvalidbyte(void);
void lbfourbyteheader(void);
void lbindicheader(void);
void lbcjkheader(void);
void lbmischeader(void);
void lbsymbolheader(void);
void lbasianheader(void);
void lbpuaheader(void);
void lbformsheader(void);
void lbhangulheader(void);
void flinebreak(void);
void latinheader(void);
void accentsheader(void);
void arabicheader(void);
void armeniheader(void);
void cyrilheader(void);
void greekheader(void);
void hebrewheader(void);
void ipaheader(void);
void nkoheader(void);
void syriacheader(void);
void thaanaheader(void);
void lblatinheader(void);
void lbaccentsheader(void);
void lbarabicheader(void);
void lbarmeniheader(void);
void lbcyrilheader(void);
void lbgreekheader(void);
void lbhebrewheader(void);
void lbipaheader(void);
void lbnkoheader(void);
void lbsyriacheader(void);
void lbthaanaheader(void);
void sighandler(int);
#define my (*me)
extern self *me;
