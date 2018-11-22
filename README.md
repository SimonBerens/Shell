# CShell :ocean: :shell:
#### CrystalSimonhell
Making a shell in C with [cwcrystal8](github.com/cwcrystal8) and [SimonBerens](github.com/SimonBerens)

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

## To Be Added
- [ ] Tab autocomplete (maybe)
- [ ] Piping
- [ ] Stdin/Stdout redirection
- [ ] Quote support 
- [ ] History (up arrow)
- [ ] Catch enter after spaces

## Limits
* 1000 character input max
* 10 arguments per command max

## Function Descriptions
Header | Arguments | Purpose | Return Value
---|---|---|---
void new_shell_line() | No arguments | Prints the current working directory | void
static void sig_handler(int n) | n: signal number | Handles signals| void
int main() | No arguments | Generates shell, parses input, and runs commands | Returns 0 on success, and value of errno otherwise


## Known Bugs
* No support for quotes
