#include <stdio.h>
#include <string.h>
#include <ctype.h>

void log_hit(const char* attacker, const char* defender, int dmg, int is_crit, int is_miss);
int parse_command(const char* line, char*verb_out, char *arg_out);
void note_trunc(int written, int buffer_size);
int is_NotEmpty(char* input);


int main(void)
{
    //log_hit("Hubert Blaine Wolfeschlegelsteinhausenbergerdorff", "Slime", 200, 1, 0);
    log_hit("Aaron", "Slime", 200, 1, 0);
    log_hit("Slime", "Aaron", 100, 1, 1);
}

int parse_command(const char* line, char*verb_out, char *arg_out)
{
    int tokens = 0;//spaces indicate # of tokens
    char* verbs[] = {"attack", "use", "look", "quit"}; //valid commands
    char* enemy_nouns[] = {"goblin, slime"};
    char* item_nouns[] = {"potion", "elixir"};
    char verb_buf[32];
    char noun_buf[32];

    if(!is_NotEmpty(line)) return 0;
    
    //find cmd
    while(*line != '\0')
    {
        
    }




}

int is_NotEmpty(char* input)
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
    char buf[30];
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