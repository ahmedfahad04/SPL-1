#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

//ANSI COLOR CODES
#define FONT_RED  "\x1B[1;31m"
#define FONT_NRM  "\x1B[0m"
#define FONT_GRN  "\x1B[1;32m"
#define FONT_YEL  "\x1B[1;33m"
#define FONT_BLU  "\x1B[1;34m"
#define FONT_MAG  "\x1B[1;35m"
#define FONT_CYN  "\x1B[1;36m"
#define FONT_WHT  "\x1B[1;37m"

#define FONT_DEEP_NRM  "\x1B[0m"
#define FONT_DEEP_RED  "\x1B[0;31m"
#define FONT_DEEP_GRN  "\x1B[0;32m"
#define FONT_DEEP_YEL  "\x1B[0;33m"
#define FONT_DEEP_BLU  "\x1B[0;34m"
#define FONT_DEEP_MAG  "\x1B[0;35m"
#define FONT_DEEP_CYN  "\x1B[0;36m"
#define FONT_DEEP_WHT  "\x1B[0;37m"

#define BACKGROUND_NRM "\x1B[40m"
#define BACKGROUND_RED " \x1B[41m"
#define BACKGROUND_GRN "\x1B[42m"
#define BACKGROUND_YEL "\x1B[43m"
#define BACKGROUND_BLU "\x1B[44m"
#define BACKGROUND_MAG "\x1B[45m"
#define BACKGROUND_CYN "\x1B[46m"
#define BACKGROUND_WHT "\x1B[47m"


// Command Prompt
void prompt();
char *take_user_input();
char **str_tokenize(char *ch, char sep);
void sig_handler(int signum);

// string opearation
size_t strlen(const char *str);
bool strcmp(const char *a, const char *b);
char *strcpy(const char *b);
char *strchr(const char *a, const char ch);
char *strcatt(const char *with, const char *str);
char *strreplace(const char *info, const char *with, const char *str);
bool strcontain(const char *data, const char *substr);
char **removeWhiteSpace(char **raw_data);
void PieTable(char *neddle, int neddle_len, int *LPS);
int strsubstr(char *neddle, char *heystack);
char **strsplit(char *find, char *text);
char *strip(char *word);

// Command Execution
void cmd_execute(char **args);
void change_directory(char *path);
char *current_directory();
char *hostName();
char *userName();
void execute(char **args);
bool isBuiltInCmd(char *cmd);
char *getCurrentDirectory();
void cmdSuggestion(char *cmd);
void findExeFileName(char *cmd);
void saveInfo();