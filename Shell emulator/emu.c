#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

// Restrictions: Command is 4096 symbols maximum, each argument is 256 maximum, the number of arguments is 256 maximum

int is_in_set(char c)
{
    return (c == '>' || c == '|' || c == '<' || c == '('
        || c == ')' || c == ';' || c == '&' || c == '\0'); //parentheses aren't really necessary here because of the conditions of the task
}

int get_next_first_sym(const char *cmd, int *offset) //returns the first symbol of the next word; 
// optionally returns the offset of the first sym of the word
{
    int counter = 0;
    while (cmd[counter] != ' ' && cmd[counter] != '\0')
        ++counter;
    while (cmd[counter] == ' ')
        ++counter;
    if (offset)
        *offset += counter;
    return cmd[counter];
}

int gather_args(const char *cmd, char *argvect[]) //returns the offset of the last symbol of the arguments, makes a vector of args
{
    int counter = 0, pos = 0; // pos will be the first sym of the first word AFTER the last arg, i.e. a special symbol
    do
    {
        argvect[counter] = malloc(257);
        sscanf(cmd + pos, "%s", argvect[counter++]);
    }
    while (!is_in_set(get_next_first_sym(cmd + pos, &pos)));
    argvect[counter] = NULL;
    return pos;
}

typedef struct fileinfo
{
    char *path;
    int flags;
} fil;

void collect_files(const char *cmd, fil *ifilp, fil *ofilp, int *offs)
{
    int pos = 0;
    int tmpc;
    while ((tmpc = get_next_first_sym(cmd + pos, &pos)) == '<' || tmpc == '>' || !is_in_set(tmpc))
        if (cmd[pos] == '<')
        {
            if (!ifilp->path)
                ifilp->path = malloc(257);
            sscanf(cmd + pos + 1, "%s", ifilp->path);
            ifilp->flags = O_RDONLY;
        }
        else if (cmd[pos] == '>')
            if (cmd[pos + 1] == '>')
            {
                if (!ofilp->path)
                    ofilp->path = malloc(257);
                sscanf(cmd + pos + 2, "%s", ofilp->path);
                ofilp->flags = O_WRONLY | O_CREAT | O_APPEND;
            }
            else
            {
                if (!ofilp->path)
                    ofilp->path = malloc(257);
                sscanf(cmd + pos + 1, "%s", ofilp->path);
                ofilp->flags = O_WRONLY | O_CREAT | O_TRUNC;
            }
    if (offs)
        *offs += pos;
    return;
}

int wt;

int executev(const fil *ifil, const fil *ofil, char *const argvect[], int dowait)
{
    int oldin, oldout, oifl = 0, oofl = 0;
    if (ifil->path)
    {
        int ifd = open(ifil->path, ifil->flags);
        oldin = dup(0);
        oifl = 1;
        dup2(ifd, 0);
        close(ifd);
    }
    if (ofil->path)
    {
        int ofd = open(ofil->path, ofil->flags, 0666);
        oldout = dup(1);
        oofl = 1;
        dup2(ofd, 1);
        close(ofd);
    }
    int sonpid;
    if (!(sonpid = fork()))
    {
        if (oifl)
            close(oldin);
        if (oofl)
            close(oldout);
        execvp(argvect[0], argvect);
        exit(1);
    }
    if (oifl)
    {
        dup2(oldin, 0);
        close(oldin);
    }
    if (oofl)
    {
        dup2(oldout, 1);
        close(oldout);
    }
    if (dowait && !wt)
        waitpid(sonpid, NULL, 0); //
    return 0;
}

void process_cmd_refined(const char *cmd, int dowait, int *offs) // process and execute 1 command
{
    fil ifil, ofil;
    ifil.path = NULL;
    ofil.path = NULL;
    int pos = 0;
    collect_files(cmd, &ifil, &ofil, &pos);
    if (offs)
        *offs += pos;
    char **argvect = malloc(257);
    gather_args(cmd, argvect);

    executev(&ifil, &ofil, argvect, dowait); //execute

    int counter = 0;
    do
    {
        free(argvect[counter]);
    }
    while (argvect[++counter] != NULL);
    free(argvect);
    if (ifil.path)
        free(ifil.path);
    if (ofil.path)
        free(ofil.path);
    if (wt)
        exit(0);
    return;
}

int pipfl, fd0;

void process_cmd_conv(const char *cmd)
{
    int pos = 0;
    char tmpc;
    while (!is_in_set(tmpc = get_next_first_sym(cmd + pos, &pos)) || tmpc == '<' || tmpc == '>');
    if (tmpc == '|')
    {
        int fd[2];
        pipe(fd);
        if (!fork())
        {
            close(fd[0]);
            if (pipfl)
            {
                dup2(fd0, 0);
                close(fd0);
            }
            dup2(fd[1], 1);
            close(fd[1]);
            process_cmd_refined(cmd, 0, NULL);
            exit(0);
        }

        close(fd[1]);
        if (pipfl)
            close(fd0);
        pipfl = 1;
        fd0 = fd[0];
        ++pos;
        while (cmd[pos] == ' ')
            ++pos;
        process_cmd_conv(cmd + pos); //recursive
    }
    else
    {
        if (pipfl)
        {
            int sonpid;
            pipfl = 0;
            if (!(sonpid = fork()))
            {
                dup2(fd0, 0);
                close(fd0);
                process_cmd_refined(cmd, 1, NULL);
                exit(0);
            }
            close(fd0);
            waitpid(sonpid, NULL, 0);
        }
        else
            process_cmd_refined(cmd, 1, NULL);
    }
    return;
}

void process_cmd(char *cmd)
{
    int pos = 0;
    while (cmd[pos] == ' ')
        ++pos;
    if (cmd[strlen(cmd) - 1] == '&')
    {
        cmd[strlen(cmd) - 1] = '\0';
        if (!fork())
        {
            wt = 1;
            process_cmd_conv(cmd + pos);
            exit(0);
        }
    }
    else
        process_cmd_conv(cmd + pos);
    return;
}

// Note: This handler will always be called on receiving SIGCHLD
// However, if this process (parent) is on standby by wait() then actually the other wait(),
// the wait() outside the handler will reap the child and the wait() inside this handler will
// receive -1 as the return value of wait()
void hand_child(int sig)
{
    waitpid(0, NULL, WNOHANG); //reap only if the parent process is not on standby by another wait(). Otherwise will wait 2x times, which is an error
    return;
}

void try_again(const char *cmd)
{
    printf("> ");
    fflush(stdout);
    return;
}

int main(int argc, char *argv[])
{
    struct sigaction chld;  //Ensuring there are no zombies
    chld.sa_handler = hand_child;
    chld.sa_flags = SA_RESTART;
    sigemptyset(&chld.sa_mask);
    sigfillset(&chld.sa_mask);
    sigaction(SIGCHLD, &chld, NULL);

    char *cmd = malloc(4097);
    printf("> ");
    fflush(stdout);
    cmd[read(0, cmd, 4096)] = '\0';

    while (1)
    {
        char c;
        if (sscanf(cmd, "%c", &c) <= 0 || c == '\n')
        {
            if (strlen(cmd) == 0)
            {
                printf("\n");
                break;
            }
            try_again(cmd);
            cmd[read(0, cmd, 4096)] = '\0';
            continue;
        }
        if (!strcmp(cmd, "exit") || !strcmp(cmd, "exit\n"))
            break;
        if (cmd[strlen(cmd) - 1] != '\n')
        {
            printf("\n");
            break;
        }
        else
            cmd[strlen(cmd) - 1] = '\0';

        process_cmd(cmd); //entry
        try_again(cmd);
        cmd[read(0, cmd, 4096)] = '\0';
    }

    free(cmd);
    return 0;
}

