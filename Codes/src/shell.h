#include <cstdio>
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

// BK TREE NODE
struct node
{
    int data;
    char *word;
    struct node *left;
    struct node *right;
};

// COMMAND STRUCT
struct ShellCommands
{
    char *simpleCommand[100];
    char *infile;
    char *outfile;
    char size = 0;
};

// COMMAND AUTOCOMPLETION
struct cmdFreq
{
    char *cmd;
    int freq;
    int prev;
};
void frequencyCalculator(char *command, FILE *save);
void assembleFreqOutput();
int generateAutoCommand(char *cmd);
void showValue(char *value);
void updateCmdFrequency();
int count(char *data[], char *info, int size);
void commandSuggestion(int flag, char **args);
char *AutoCommandCompletion(int flag, char *args);

// HISTORY
struct history
{
    char *cmd;
    int order;
};
int historySerialLocator();
void writeHistory(int size, struct history ht[]);
char *readHistory(int serial = -1);
char *showParticularHistory(char *cmd);
void clearHistory();

// MAIN LOOP
void eventLoop(char *code = "", char *type = "");
void eventLoopWithColors(char *ch = "", char *type = "");

// COMMAND PROMPT
void prompt();
void promptWithColors(char *code, char *colorType);
char *takeUserInput(char *code = "", char *colorType = "", int fsl = 0, FILE *fp = NULL);
char **strTokenize(char *ch, char sep);

// BASIC STRING OPERATIONS
size_t strlen(const char *str);
bool strcmp(const char *a, const char *b);
int strlen2(char **str);
char *strcpy(const char *b);
char *strchr(const char *a, const char ch);
char *strcatt(const char *with, const char *str);
char *strreplace(const char *info, const char *with, const char *str);
bool strcontain(const char *data, const char *substr);
char **removeWhiteSpace(char **raw_data);
void prefixTable(char *neddle, int neddle_len, int *LPS);
int strsubstr(char *neddle, char *heystack);
char **strsplit(char *find, char *text);
char *strip(char *word);
char *selectBGColor(char *args);
char *selectFGColor(char *args);
char *numToStr(int num);
void userManual();
bool wildcardmatching(char *str, char *pat, int slen, int plen);
void intro();

// COMMAND EXECUTION
void cmdExecute(char **args);
void change_directory(char *path);
char *current_directory();
char *hostName();
char *userName();
void execute(char **args);
char *getCurrentDirectory();
void BKTreeGeneration(char *cmd);
void findExeFileName(char *cmd);
void saveInfo();
void executePipelinedCommands(int size, char *simpleCMD[], struct ShellCommands command);
char **checkForWildCards(char **data);
void setAlias(char *cmd, char *alias);
void aliasCommands(char **words);
char **checkForAliasing(char **cmd);
char *getAlias(char *data);
struct ShellCommands parse(char *data);
int processPipelinedCommand(char *command);
int porcessSingleCommand(char *command);
