#include <string>
#include <queue>
#include <unistd.h>

using namespace std;

void run_cmd(string& cmd, int argc, queue<string> &argv);
void cat(string& file);
void cd(string& dir);
void ch_mod(int mode, string& path);
void echo(string& s, string& file);
void find(string& path);
void mk_dir(string& dir);
void rm(string& file);
void rm_dir(string& dir);
void print_stat(string& path);
void touch(string& file);
char f_type(mode_t mode);
bool is_octal(string& num);

enum {
    H_CAT,
    H_CD,
    H_CHMOD,
    H_ECHO,
    H_EXIT,
    H_FIND,
    H_HELP,
    H_ID,
    H_MKDIR,
    H_PWD,
    H_RM,
    H_RMDIR,
    H_STAT,
    H_TOUCH,
    H_UMASK
};

static const char* HELP[] = {
    "cat {file}:              Display content of {file}.",
    "cd {dir}:                Switch current working directory to {dir}.",
    "chmod {mode} {file/dir}: Change the mode (permission) of a file or directory.\n"
        "                         {mode} is an octal number.",
    "echo {str} [filename]:   Display {str}. If [filename] is given,\n"
        "                         open [filename] and append {str} to the file.",
    "exit:                    Leave the shell.",
    "find [dir]:              List files/dirs in the current working directory\n"
        "                         or [dir] if it is given.\n"
        "                         Minimum outputs contatin file type, size, and name.",
    "help:                    Display help message.",
    "id:                      Show current euid and egid number.",
    "mkdir {dir}:             Create a new directory {dir}.",
    "pwd:                     Print the current working directory.",
    "rm {file}:               Remove a file.",
    "rmdir {dir}:             Remove an empty directory.",
    "stat {file/dir}:         Display detailed information of the given file/dir.",
    "touch {file}:            Create {file} if it does not exist,\n"
        "                         or update its access and modification timestamp.",
    "umask {mode}:            Change the umask of the current session."
};
