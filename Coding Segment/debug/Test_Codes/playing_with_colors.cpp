#include <stdio.h>

#define SH_NRM  "\x1B[0m"
#define SH_RED  "\x1B[1;31m"
#define SH_GRN  "\x1B[1;32m"
#define SH_YEL  "\x1B[1;33m"
#define SH_BLU  "\x1B[1;34m"
#define SH_MAG  "\x1B[1;35m"
#define SH_CYN  "\x1B[1;36m"
#define SH_WHT  "\x1B[1;37m"

#define SH_B_RED  "\x1B[0;31m"
#define SH_B_GRN  "\x1B[0;32m"
#define SH_B_YEL  "\x1B[0;33m"
#define SH_B_BLU  "\x1B[0;34m"
#define SH_B_MAG  "\x1B[0;35m"
#define SH_B_CYN  "\x1B[0;36m"
#define SH_B_WHT  "\x1B[0;37m"


#define SH_BG_RED " \x1B[41m"
#define SH_BG_GRN "\x1B[42m"
#define SH_BG_YEL "\x1B[43m"
#define SH_BG_BLU "\x1B[44m"
#define SH_BG_MAG "\x1B[45m"
#define SH_BG_CYN "\x1B[46m"
#define SH_BG_WHT "\x1B[47m"


int main(){

    printf("%s%sMyColor\n%s", SH_B_BLU, SH_RED, SH_NRM);
}
