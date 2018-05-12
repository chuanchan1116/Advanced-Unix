# Homework #1

Advanced Programming in the UNIX Environment

## Due: April 3, 2018

Due to requests, we will extend the submission deadline to April 7, 2018.

## Secure Interactive Shell

It is common to have a customized shell for embedded devices, e.g., switches, routers, cameras, and many IoT devices. In this homework, you have to implement a secure interactive shell running in a chroot'ed environment. No system binaries nor libraries are available in the chroot'ed environment. Your implemented program is the only binary that is available in the runtime environment. Therefore, you have to implement several required functions by yourself. The requirements for your secure interactive shell is as follows

1. You have to compile your program statically so that your program does not depend on any external libraries in the system.
2. You program will be launched as a service using xinetd. The sample configuration for running your service will be similar to this one.
3. We will launch your program with root (euid = 0) permission, and you have to set euid and egid to the first two values passed to your program (via argc/argv), respectively
4. A breif summary of supported commands and their minimum requirements are listed here (ordered alphabetically):

    ```
    cat {file}:              Display content of {file}.
    cd {dir}:                Switch current working directory to {dir}.
    chmod {mode} {file/dir}: Change the mode (permission) of a file or directory.
                             {mode} is an octal number. Please do not follow symbolc links (not supported on Linux, but works on Mac).
    echo {str} [filename]:   Display {str}. If [filename] is given,
                             open [filename] and append {str} to the file.
    exit:                    Leave the shell.
    find [dir]:              List files/dirs in the current working directory
                             or [dir] if it is given.
                             Minimum outputs contatin file type, size, and name.
    help:                    Display help message.
    id:                      Show current euid and egid number.
    mkdir {dir}:             Create a new directory {dir}.
    pwd:                     Print the current working directory.
    rm {file}:               Remove a file.
    rmdir {dir}:             Remove an empty directory.
    stat {file/dir}:         Display detailed information of the given file/dir.
    touch {file}:            Create {file} if it does not exist,
                             or update its access and modification timestamp.
    umask {mode}:            Change the umask of the current session.
    ```

5. If a command cannot be handled or returns with errors, please display a meaningful error message to the user.

To test your program, you can try to install xinetd in your own virtual machine, edit and use the sample configuration we provided, and test your program in the chroot'ed environment.

## Homework Submission

Plesae submit your homework via the E3 system. You have to pack all the required files (README, Makefile, source codes, and maybe xinetd configuration file) in a single zip archive file. Scores will be given based on the correctness and completeness of your implementation.

## FAQ

We have prepared a list of FAQ by summarizing all the questions from the students. Please have a look! If you cannot find an answer here, please send your questions to the TAs or the instructor. Thanks

* Q0: Which language should we use in HW1? Are both C and C++ available?

  A: Yes, you can implement in both C and/or C++.
* Q1: Should I compile the required commands into binaries separately and run them using fork?

  A: No, our required features are pretty simple. You should implement the minimum requirements by yourself in your homework program. No other binary is available in the runtime environment, so it does not make sense to work with fork.
* Q2: Why system call is not working after chroot?

  A: Actually system call works if you implement the call in assembly. However, dynamically linked libraries (the default behavior) are not available in the chroot'ed environment. Therefore, we asked you to statically compile your program.
* Q3: Should `echo` append a newline character if [filename] is given?

  A: It does not matter if a file name is given or not. You should always have a new line character for an echoed string.
* Q4: Should `id` also show username?

  A: No, `id` command does not need to show username, only euid and egid is required. We are not asking you to implement the full version 'id' command in the system. You don't have to work with functions like getgrgid.
* Q5: How do we chmod without following the symbolic link?

  A: We have removed the requirement on 'not following symbolic links'. It is actually supported on Mac and BSD, but not available on Linux.
* Q6: Is working directory not preserved after the program exit?

  A: Your program will always start with the chroot'ed directory passed to the chroot program. Working directory is not preserved.
* Q7: Shall we need to support executing other binary file by using fork?

  A: No, we will test the commands as stated in the requirement. Also there is no other binary in the chroot'ed environment.
* Q8: Should `echo` deal with the case that `str` come with whitespace?

  A: It is not in the requirement so we will not run that kind of test cases. If your program supports the feature, please make a statement in your README file.
* Q9: Should `find` list the files/directories recursively (not just the first level)?

  A: No, you only need to list the files and directories in first level.
* Q10: What `type` and `size` should `find` show?

  A: `type` can be file, directory, fifo, socket, block/char devices, etc. `size` can be either actual file size or major/minor number depend on the type of the file.
* Q11: What should I put into the README file?

  A: Just tell the TAs how to test your program. For example, what would be the parameters accepted by your implemented commands, what would be the output of your commands, or what additional features are implemented.

