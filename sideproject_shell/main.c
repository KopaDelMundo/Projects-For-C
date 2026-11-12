#include <stdio.h>
#include <stdlib.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char *line);

//functions for commands
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

int (*builtin_func[]) (char ** ) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int main(int argc, char **argv)
{
    //run command loop
    lsh_loop();

    //performe any shutdown/cleanup
    return EXIT_SUCCESS;
}

void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    }while(status);
}

char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if(!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        //read a character
        c = getchar();

        //if we hit EOF, replace it will a null character and return.
        if (c == EOF || c == '\n') 
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        //if we have exceeded the buffer, reallocate
        if (position >= bufsize) 
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if(!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize *sizeof(char*));
    char *token;

    if(!tokens) 
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if(position >= bufsize)
        {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_BUFSIZE);
    }
    tokens[position] = NULL;
    return tokens;
}

int_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    int i;
    printf("Aaron's mock LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for(i = 0; i < lsh_num_builtins(); i++)
    {
        printf(". %s\n", builtin_str[i]);
    }

    printf("Use the command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}