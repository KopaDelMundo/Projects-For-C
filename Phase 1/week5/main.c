#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TESTSTRINGS 8

void log_hit(const char* attacker, const char* defender, int dmg, int is_crit, int is_miss);
int parse_command(const char* line, char*verb_out, char *arg_out);
void note_trunc(int written, int buffer_size);
int is_NotEmpty(const char* input);


int main(void)
{
    //log_hit("Hubert Blaine Wolfeschlegelsteinhausenbergerdorff", "Slime", 200, 1, 0);
    //log_hit("Aaron", "Slime", 200, 1, 0);
    //log_hit("Slime", "Aaron", 100, 1, 1);
    char cmd_verb[32];
    char cmd_noun[32];
    char cmd_raw[64];
    //int tokens;

    while(1)
    {
        printf("Enter command for battle: \n");
        fgets(cmd_raw, sizeof(cmd_raw), stdin);
        if(strchr(cmd_raw, '\n') == NULL)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {};
            printf("Your cmd was too long, try something shorter.\n");
        }
        cmd_raw[strcspn(cmd_raw, "\n")] = '\0';

        parse_command(cmd_raw, cmd_verb, cmd_noun);
        
        if(strcmp(cmd_verb, "quit") == 0) break;
    }



}

int parse_command(const char* line, char*verb_out, char *arg_out)
{
    //0 for first word not valid
    //1 for valid first cmd, but doesnt account for second word (might also mean quit)
    //2 if valid noun (and verb isn't quit)
    
    char* verbs[] = {"attack", "use", "look", "quit"};  //valid commands
    char* enemy_nouns[] = {"goblin", "slime"};          //valid enemies
    char* item_nouns[] = {"potion", "elixir"};          //valid items 
    char verb_buf[32];
    char *verb_p = verb_buf;
    int current_word_flag = 1;
    char noun_buf[32];
    char *noun_p = noun_buf; 
    int is_valid_cmd = 0;
    int is_valid_noun = 0;

    printf("||DEBUG|| line: %s\n", line);

    if(!is_NotEmpty(line)) return 0;
    
    //parse verb and noun
    while(*line != '\0')
    {
        if(!isspace(*line))
        {

            if(current_word_flag == 1)
            {
                *verb_p = *line;
                verb_p++;
            }
            else if(current_word_flag == 2)
            {
                *noun_p = *line;
                noun_p++;
            }
        }
        else if(isspace(*line) && current_word_flag == 1)
        {
            current_word_flag = 2;
        }
        line++;
    }

    *verb_p = '\0';
    *noun_p = '\0';

    printf("||DEBUG|| verb_buf:_%s_\n", verb_buf);
    printf("||DEBUG|| noun_buf:_%s_\n", noun_buf);

    //search for valid verb in verbs[]
    for(int i = 0; i < 4; i++)
    {
        if(strcmp(verbs[i], verb_buf) == 0)
        {
            is_valid_cmd = 1;
            
            strcpy(verb_out, verb_buf);
            break;
        }
    }
    //handle invalid verb
    if(!is_valid_cmd)
    {
        printf("Unknown Command: Please enter valid command.\n");
        return 0;
    } 

    if(strcmp(verbs[3], verb_buf) == 0) return 1;

    if(strcmp(verbs[1], verb_buf) == 0)  //if cmd was "use", look item nouns, else look in enemy nouns
    {
        printf("||DEBUG|| looking for item...\n");
        for(int i = 0; i < 2; i++)
        {
            if(strcmp(item_nouns[i], noun_buf) == 0)
            {
                is_valid_noun = 1;
                printf("||DEBUG||comparing from enemy_nouns: %s\n", item_nouns[i]);
                strcpy(arg_out, noun_buf);
                break;
            }
        }
        
    }
    
    if(strcmp(verbs[0], verb_buf) == 0 || strcmp(verbs[2], verb_buf) == 0)
    {
        printf("||DEBUG|| looking for enemy...\n");
        for(int i = 0; i < 2; i++)
        {
            printf("||DEBUG||comparing from enemy_nouns: %s\n", enemy_nouns[i]);
            if(strcmp(enemy_nouns[i], noun_buf) == 0)
            {
                is_valid_noun = 1;
                
                strcpy(arg_out, noun_buf);
                break;
            }
        }
        
    }

    if(!is_valid_noun)
    {
        printf("Unknown Command: Second word of command not valid.\n");
        return 1;
    }

    return 2;

}

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

void log_hit(const char* attacker, const char* defender, int dmg, int is_crit, int is_miss)
{
    char buf[64];
    int buf_size = (int)sizeof(buf);
    int n = 0;

    if(is_miss) //0 dmg assumes a miss for now
    {
        n = snprintf(buf, sizeof(buf), "%s's attack missed!", attacker);
    }
    else if(is_crit)
    {
        n = snprintf(buf, sizeof(buf), "%s attacks %s! It was critical! %d damage!", attacker, defender, dmg);
    }
    else
    {
        n = snprintf(buf, sizeof(buf), "%s attacks %s! %d damage!", attacker, defender, dmg); 
    }

    note_trunc(n, buf_size);
    printf("%s\n", buf);
}

void note_trunc(int written, int buffer_size)
{
    if(written >= buffer_size) fprintf(stderr, "warning: log message truncated\n");
}