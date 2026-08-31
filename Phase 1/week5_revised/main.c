#include <stdio.h>
#include <string.h>
#include <ctype.h>

int parse_command(const char* line, char*verb_out, char *arg_out);
int is_NotEmpty(const char* input);

int main(void)
{
    char cmd_line[64];
    char cmd_verb[32];
    char cmd_noun[32];
    int tokens = 0;

    while(1)
    {
        do
        {
            printf("Enter command for battle: \n");
            char* input_p = fgets(cmd_line, sizeof(cmd_line), stdin);
            if(input_p != NULL)
            {
                if(strchr(cmd_line, '\n') == NULL)
                {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {};
                    printf("Your cmd was too long, try something shorter.\n");
                }
            }
            else
            {
                printf("Input Ended.\n");
                return 0;
            }
            
        } while (strchr(cmd_line, '\n') == NULL);
        
        cmd_line[strcspn(cmd_line, "\n")] = '\0';

        tokens = parse_command(cmd_line, cmd_verb, cmd_noun);

        printf("Parsed Line: %s %s\n", cmd_verb, cmd_noun);

        if(tokens == 0)
        {
            printf("No words detected\n");
        }
        else if(tokens == 1)
        {
            if(strcmp("quit", cmd_verb) == 0)
            {
                printf("Quitting program...\n");
                break;
            }
            printf("One word detected\n");
        }
        else if (tokens == 2)
        {
            printf("Two Words detected\n");
        }
    }
}

//breaks string into verb_out and arg_out, returns amount of tokens found (0, 1, 2)
int parse_command(const char* line, char* verb_out, char* arg_out)
{
    *verb_out = '\0';
    *arg_out = '\0';

    char *verb_p        = verb_out;
    char *noun_p        = arg_out;
    int verb_len_flag   = 0;
    int noun_len_flag   = 0;
    int word_flag       = 0;
    int tokens          = 0;

    printf("||DEBUG|| line: %s\n", line);

    if(!is_NotEmpty(line)) return tokens;

    while(*line != '\0')
    {
        if(!isspace(*line))
        {
            if(word_flag == 0)
            {
                word_flag = 1;
            } 
            
            if(word_flag == 1 && verb_len_flag < 31)
            {
                word_flag = 1;
                verb_len_flag++;
                *verb_p = *line;
                verb_p++;
                
            }
            else if(word_flag == 2 && noun_len_flag < 31)
            {
                noun_len_flag++;
                *noun_p = *line;
                noun_p++;
            }
        }
        else if(isspace(*line) && word_flag == 1)
        {
            word_flag = 2;
        }
        line++;
    }

    printf("||DEBUG|| PARSE COMPLETE\n");
    *verb_p = '\0';
    *noun_p = '\0';

    if(*verb_out != '\0') tokens++;
    if(*arg_out != '\0') tokens++;

    printf("||DEBUG|| FUNCTION COMPLETE\n");

    return tokens;
}

//returns 0 if empty and 1 if not empty
int is_NotEmpty(const char* input) 
{
    if(input == NULL) return 0;

    while(*input != '\0')
    {
        if(!isspace((unsigned char)*input))
        {
            break;
        }

        input++;
    }

    if(*input == '\0')
    {
        return 0;
    }
  
    return 1;
}