#ifndef HTML_PARSER
#define HTML_PARSER

#define BOM_SIZE    3

#define UTF_8_BOM   0xEFBBBF
#define UTF_16_L_BOM    0xFFFE
#define UTF_16_B_BOM    0xFEFF

#define CODE_UTF_8  1
#define CODE_UTF_16_L   2
#define CODE_UTF_16_B   3


#define EQUEL 0x3D
#define TAG_END 0x3E
#define TAG_SLANT 0x2F

#define isspace(a) (((a) == "\t") or \
    ((a) == " ") or ((a) == "\f") or \
    ((a) == "\n") or ((a) == "\r"))

#define is_value(a, b) (((a) ^ (b)) == 0)

#include <string.h>

int html_parser(char* page);

#endif
