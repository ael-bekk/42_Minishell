<h1 align="center">Minishell 💻</h1>
<h4 align="center">As beautiful as a shell </h4>



## About

- Minishell is a project at school 42.

- The objective of this project is to create a simple shell to learn a lot about processes and file descriptors.

- The existence of shells is linked to the very existence of IT. At the time, all coders agreed that communicating with a computer using aligned 1/0 switches was seriously irritating. It was only logical that they came up with the idea to communicate with
a computer using interactive lines of commands in a language somewhat close to english.
With Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.


## Functions
Only the following functions are allowed to be used in this project:<br>
| Function | Description | Function | Description |
|----------|-------------|----------|-------------|
|readline | read a line from the terminal |lstat | get file status | 
|rl_clear_history | clear the history list by deleting all of the entries | fstat | get file status by fd |
|rl_on_new_line | tell the update routines that we have moved onto a new line | unlink | remove a specified file |
|rl_replace_line | replace the contents of rl_line_buffer with text | execve | execute program |
|rl_redisplay | change what's displayed on the screen | dup | duplicate a file descriptor |
|add_history | save the line in a history list of lines | dup2 | duplicate a file descriptor |
|printf | format and print data | pipe | create pipe |
|malloc | allocate dynamic memory | opendir | open a directory |
|free | free dynamic memory | readdir | read a directory |
|write | write to a file descriptor | closedir | close a directory |
|access | check user's permissions for a file | strerror | return string describing error number |
|open | open and can create a file | perror | print a system error message |
|read | read from a file descriptor | isatty | test whether a file descriptor refers to a terminal |
|close | close a file descriptor | ttyname | return name of a terminal |
|fork | create a child process | ttyslot | find the slot of the current user's terminal in some file |
|wait | wait for process to change state | ioctl | control device |
|waitpid | wait for process to change state | getenv | get an environment variable |
|wait3 | wait for process to change state | tcsetattr | control asynchronous communications ports |
|wait4 | wait for process to change state | tcgetattr | control asynchronous communications ports |
|signal | ANSI C signal handling | tgetent | termcap database emulation |
|sigaction | examine and change a signal action | tgetflag |  termcap database emulation |
|kill | send signal to a process | tgetnum |  termcap database emulation |
|exit | cause normal process termination | tgetstr | termcap database emulation |
|getcwd | get current working directory | tgoto | termcap database emulation |
|chdir | change working directory | tputs | curses interfaces to terminfo database |
|stat | get file status by pathname |

## Starting ##

```bash
# Clone this project
$ git clone https://github.com/Mounadi05/42_Minishell

# Access
$ cd 42_Minishell

# Compile the project
$ make

# Compile the project in linux 
$ make linux 

# Run the project
$ ./minishell

```
