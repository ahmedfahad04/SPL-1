#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// ANSI COLOR CODES
#define FONT_BLK "\u001b[30m"
#define FONT_RED "\u001b[31m"
#define FONT_GRN "\u001b[32m"
#define FONT_YEL "\u001b[33m"
#define FONT_BLU "\u001b[34m"
#define FONT_MAG "\u001b[35m"
#define FONT_CYN "\u001b[36m"
#define FONT_WHT "\u001b[37m"
#define RESET "\u001b[0m" 

#define FONT_DARK_BLK "\u001b[30m;1m"
#define FONT_DARK_RED "\u001b[31m;1m"
#define FONT_DARK_GRN "\u001b[32m;1m"
#define FONT_DARK_YEL "\u001b[33m;1m"
#define FONT_DARK_BLU "\u001b[34m;1m"
#define FONT_DARK_MAG "\u001b[35m;1m"
#define FONT_DARK_CYN "\u001b[36m;1m"
#define FONT_DARK_WHT "\u001b[37m;1m"

#define BG_BLK "\u001b[40m"
#define BG_RED "\u001b[41m"
#define BG_GRN "\u001b[42m"
#define BG_YEL "\u001b[43m"
#define BG_BLU "\u001b[44m"
#define BG_MAG "\u001b[45m"
#define BG_CYN "\u001b[46m"
#define BG_WHT "\u001b[47m"

#define BG_DARK_BLK "\u001b[40m;1m"
#define BG_DARK_RED "\u001b[41m;1m"
#define BG_DARK_GRN "\u001b[42m;1m"
#define BG_DARK_YEL "\u001b[43m;1m"
#define BG_DARK_BLU "\u001b[44m;1m"
#define BG_DARK_MAG "\u001b[45m;1m"
#define BG_DARK_CYN "\u001b[46m;1m"
#define BG_DARK_WHT "\u001b[47m;1m"


// COMMAND PROMPT
void prompt();
char *take_user_input();
char **str_tokenize(char *ch, char sep);
void sig_handler(int signum);

// BASIC STRING OPERATIONS
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
void colorManager();
char * numToStr(int num);

// COMMAND EXECUTION
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