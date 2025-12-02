typedef struct instr{
    char **arg;
    int MAX_ARGS;
    int MAX_CHARS;
}in_str;

in_str initArg(int args, int chars);
void escanf(in_str *cur);
void freeArgs(in_str *cur);
void destroyArgs(in_str *cur);
