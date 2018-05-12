#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unistd.h>
#include <utime.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "cmd.hpp"

#define BUFSIZE 4096

using namespace std;

void run_cmd(string &cmd, int argc, queue<string> &argv) {
    errno = 0;
    if(cmd == "cat") {
        if(argc != 1) {
            cout << HELP[H_CAT] << endl;
            return;
        }
        cat(argv.front());
    } else if(cmd == "cd") {
        if(argc != 1) {
            cout << HELP[H_CD] << endl;
            return;
        }
        cd(argv.front());
    } else if(cmd == "chmod") {
        if(argc != 2) {
            cout << HELP[H_CHMOD] << endl;
            return;
        }

        string mode = argv.front();
        argv.pop();
        string path = argv.front();

        if(!is_octal(mode)) {
            cout << mode << ": not an octal number." << endl;
            return;
        }

        ch_mod(strtol(mode.c_str(), NULL, 8), path);
    } else if(cmd == "echo") {
        if(argc != 1 && argc != 2) {
            cout << HELP[H_ECHO] << endl;
            return;
        }
        string s = argv.front();
        argv.pop();
        cout << s << endl;

        if(argc == 2) {
            string f = argv.front();
            echo(s, f);
        }
    } else if(cmd == "exit") {
        exit(0);
    } else if(cmd == "find") {
        if(argc > 1) {
            cout << HELP[H_FIND] << endl;
            return;
        }
        string path = "./";

        if(argc == 1) path = argv.front();
        if(path[path.length() - 1] != '/') path += "/";
        find(path);
    } else if(cmd == "help") {
        for(int i = H_CAT; i <= H_UMASK; i++) {
            cout << HELP[i] << endl;
        }
    } else if(cmd == "id") {
        if(argc != 0) {
            cout << cmd << ": too many arguments.\n" << HELP[H_ID] << endl;
            return;
        }
        cout << "uid: " << geteuid() << " gid: " << getegid() << endl;
    } else if(cmd == "mkdir") {
        if(argc != 1) {
            cout << HELP[H_MKDIR] << endl;
            return;
        }
        mk_dir(argv.front());
    } else if(cmd == "pwd") {
        if(argc != 0) {
            cout << cmd << ": too many arguments.\n" << HELP[H_PWD] << endl;
            return;
        }
        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd))) {
            cout << cwd << endl;
        } else {
            perror("pwd");
        }
    } else if(cmd == "rm") {
        if(argc != 1) {
            cout << HELP[H_RM] << endl;
            return;
        }
        rm(argv.front());
    } else if(cmd == "rmdir") {
        if(argc != 1) {
            cout << HELP[H_RMDIR] << endl;
            return;
        }
        rm_dir(argv.front());
    } else if(cmd == "stat") {
        if(argc != 1) {
            cout << HELP[H_STAT] << endl;
            return;
        }
        print_stat(argv.front());
    } else if(cmd == "touch") {
        if(argc != 1) {
            cout << HELP[H_TOUCH] << endl;
            return;
        }
        touch(argv.front());
    } else if(cmd == "umask") {
        if(argc != 1) {
            cout << HELP[H_UMASK] << endl;
            return;
        }
        if(!is_octal(argv.front())) {
            cout << argv.front() << ": not an octal number." << endl;
            return;
        }
        umask(strtol(argv.front().c_str(), NULL, 8));
    } else {
        cout << "Command not found. Type `help` to see supported commands." << endl; 
    }
}

void cat(string& file) {
    FILE *f = fopen(file.c_str(), "r");
    if(f) {
        int n;
        char buf[BUFSIZE];
        while((n = fread(buf, 1, sizeof(buf), f)) > 0) {
            write(STDOUT_FILENO, buf, n);
        }
        fclose(f);
    } else {
        perror(file.c_str());
    }
}

void cd(string& dir) {
    if(chdir(dir.c_str()) == -1) {
        perror(dir.c_str());
    }
}

void ch_mod(int mode, string& path) {
    if(chmod(path.c_str(), mode) == -1) {
        perror(path.c_str());
    }
}

void echo(string& s, string& file) {
    FILE *f = fopen(file.c_str(), "a");
    if(f) {
        fprintf(f, "%s\n", s.c_str());
        fclose(f);
    } else {
        perror(file.c_str());
    }
}

void find(string& path) {
    DIR *d = opendir(path.c_str());
    if(d) {
        struct dirent *dent;
        while(dent = readdir(d)) {
            struct stat file_stat;
            if(stat(dent->d_name, &file_stat) == -1) continue;
            cout << f_type(file_stat.st_mode) <<
                ((file_stat.st_mode & S_IRUSR) ? "r" : "-") <<
                ((file_stat.st_mode & S_IWUSR) ? "w" : "-") <<
                ((file_stat.st_mode & S_IXUSR) ? "x" : "-") <<
                ((file_stat.st_mode & S_IRGRP) ? "r" : "-") <<
                ((file_stat.st_mode & S_IWGRP) ? "w" : "-") <<
                ((file_stat.st_mode & S_IXGRP) ? "x" : "-") <<
                ((file_stat.st_mode & S_IROTH) ? "r" : "-") <<
                ((file_stat.st_mode & S_IWOTH) ? "w" : "-") <<
                ((file_stat.st_mode & S_IXOTH) ? "x" : "-") <<
                " " << file_stat.st_size << "\t" << dent->d_name << endl;

        }
    } else {
        perror(path.c_str());
    }
}

void mk_dir(string& dir) {
    if(mkdir(dir.c_str(), 0755) == -1) {
        perror(dir.c_str());
    }
}

void rm(string& file) {
    if(unlink(file.c_str()) == -1) {
        perror(file.c_str());
    }
}

void rm_dir(string& dir) {
    if(rmdir(dir.c_str()) == -1) {
        perror(dir.c_str());
    }
}

void print_stat(string& path) {
    struct stat file_stat;
    if(stat(path.c_str(), &file_stat) != -1) {
        cout << f_type(file_stat.st_mode) <<
            ((file_stat.st_mode & S_IRUSR) ? "r" : "-") <<
            ((file_stat.st_mode & S_IWUSR) ? "w" : "-") <<
            ((file_stat.st_mode & S_IXUSR) ? "x" : "-") <<
            ((file_stat.st_mode & S_IRGRP) ? "r" : "-") <<
            ((file_stat.st_mode & S_IWGRP) ? "w" : "-") <<
            ((file_stat.st_mode & S_IXGRP) ? "x" : "-") <<
            ((file_stat.st_mode & S_IROTH) ? "r" : "-") <<
            ((file_stat.st_mode & S_IWOTH) ? "w" : "-") <<
            ((file_stat.st_mode & S_IXOTH) ? "x" : "-") <<
            " " << file_stat.st_nlink << " " << file_stat.st_uid <<
            " " << file_stat.st_gid << " " << file_stat.st_size <<
            " " << path << " " << file_stat.st_atime << 
            " " << file_stat.st_mtime << endl;

    } else {
        perror(path.c_str());
    }
}

void touch(string& file) {
    FILE *f = fopen(file.c_str(), "ab+");
    if(f) {
        utime(file.c_str(), NULL);
        fclose(f);
    } else {
        perror(file.c_str());
    }
}

char f_type(mode_t mode) {
    char c;
    switch (mode & S_IFMT) {
        case S_IFBLK:
            c = 'b';
            break;
        case S_IFCHR:
            c = 'c';
            break;
        case S_IFDIR:
            c = 'd';
            break;
        case S_IFIFO:
            c = 'p';
            break;
        case S_IFLNK:
            c = 'l';
            break;
        case S_IFREG:
            c = '-';
            break;
        case S_IFSOCK:
            c = 's';
            break;
        default:
            c = '?';
            break;
    }
    return (c);
}

bool is_octal(string& num) {
    bool octal = true;
    for(int i = 0; i < num.length(); i++) {
        if(num[i] < '0' || num[i] >= '8') {
            octal = false;
            break;
        }
    }
    return octal;
}
