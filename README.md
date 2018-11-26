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
`$ cd` | Needs a '/' at the end of the path to work
`$ exit`| All bash commands (e.g., `ls`, `ps`, etc.)
Semicolon parsing | Supports multiple commands; Filters empty commands
Shows current working directory | Color-coded
Supports arguments for commands | e.g. `ls -l`
Catches CTRL+C (^C) | Will send a SIGINT to the current process running
Arbitrary whitespace support | Will ignore multiple spaces
Catches invalid commands | Prints error set in errno
Redirecting | Suports `>`,`>>`,`2>`,`2>>`,`<`

## Function Descriptions
Header | Arguments | Purpose | Return Value
---|---|---|---
void new_shell_line() | No arguments | Prints the current working directory | void
static void sig_handler(int n) | `n`: signal number | Handles signals| void
int main() | No arguments | Generates shell, parses input, and runs commands | Returns 0 on success, and value of errno otherwise
int redirect(int direction, int flag, char * file_name, int * fd_location) | `direction`: indicates the buffer that is being redirected <br> `flag`: indicates the flags to open the file with <br> `file_name`: the name of the file that the buffer is redirected to <br> `fd_location`: a pointer to the file descriptor of the opened `file_name` | Returns the file descriptor of the opened `file_name`

## To Be Added
- [ ] Piping
- [ ] Catch enter after spaces

## Limits
* 1000 character input max
* 10 arguments per command max

## Known Bugs
* Semicolon parsing does not work if there is a space before the semicolon
