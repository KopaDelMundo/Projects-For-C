#include <stdio.h>


void log_hit(const char* attacker, const char* defender, int dmg);
int parse_command(const char* line, char*verb_out, char *arg_out);
void note_trunc(int a, int b);

int main(void)
{
    log_hit("Aaron", "Slime", 200);
    log_hit("Slime", "Aaron", 0);
}

void log_hit(const char* attacker, const char* defender, int dmg)
{
    char buf[128];
    int buf_size = (int)sizeof(buf);
    int n;

    if(dmg == 0) //0 dmg assumes a miss for now
    {
        n = snprintf(buf, sizeof(buf), "%s's attack missed!", attacker);
        note_trunc(n, buf_size);
    }
    else
    {
        n = snprintf(buf, sizeof(buf), "%s attacks %s! %d damage!", attacker, defender, dmg);
        note_trunc(n, buf_size);
    }

    printf("%s\n", buf);
}

void note_trunc(int a, int b)
{
    if(a >= b) fprintf(stderr, "warning: log message truncated\n");
}