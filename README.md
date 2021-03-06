# CShell :ocean: :shell:
#### CrystalSimonhell
Making a shell in C with [cwcrystal8](github.com/cwcrystal8) and [SimonBerens](github.com/SimonBerens)

## Table of Contents
1. [How to Run](#how-to-run)
2. [Working Features](#working-features)
3. [To Be Added](#to-be-added)
4. [Limits](#limits)
5. [Function Descriptions](#function-descriptions)
6. [Known Bugs](#known-bugs)


## How to Run
1. In a bash shell, run:
~~~
$ make
~~~
2. Then run:
~~~
$ make run
~~~
3. Input any commands, then press enter to run the commands.


## Working Features
Feature | Notes
--- | ---
`cd` | If no directory specified, current working directory does not change
`exit`| Will exit regardless of any arguments
All bash commands | e.g. `ls`, `ps`, etc.
Semicolon parsing | Supports multiple commands; Filters empty commands
Shows current working directory | Color-coded
Supports arguments for commands | e.g. `ls -l`
Catches CTRL+C (^C) | Will send a SIGINT to the current process running
Arbitrary whitespace support | Will ignore multiple spaces
Catches invalid commands | Prints error
Redirecting | Supports `>`, `>>`, `2>`, `2>>`, `<`
Background processes | Supports `&`
Chain piping | e.g. `ls -l \| grep .c \| wc`


## Function Descriptions
Header | Arguments | Purpose | Return Value
---|---|---|---
void new_shell_line() | No arguments | Prints the current working directory | void
static void active_sig_handler(int n) | `n`: signal number | Handles signals| void
static void passive_sig_handler(int n) | `n`: signal number | Prints newline to flush stdout | void
void redirect(int direction, int flag, char * file_name, int * fd_location) | `direction`: indicates the buffer that is being redirected <br> `flag`: indicates the flags to open the file with <br> `file_name`: the name of the file that the buffer is redirected to <br> `fd_location`: a pointer to the file descriptor of the opened `file_name` | void
int main() | No arguments | Generates shell, parses input, and runs commands | Returns 0 on success, and value of errno otherwise

## Limits
* 1000 character input max
* 10 arguments per command max
* `cd` does not support any flags

## Known Bugs
* Pressing tab will allow the user to delete the shell's displayed current working directory
