#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <unistd.h>

#include "cmd.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    string input;

    setegid(atoi(argv[2]));
    seteuid(atoi(argv[1]));

    while((cout << "shell> " && getline(cin, input))) {
        if(input.length()) {
            int arg_count = 0;
            string cmd, tmp;
            stringstream pipe_to;
            queue<string> arg_queue;

            pipe_to << input;
            pipe_to >> cmd;

            while(pipe_to >> tmp) arg_queue.push(tmp);

            arg_count = arg_queue.size();

            run_cmd(cmd, arg_count, arg_queue);
        }
    }
    return 0;
}
