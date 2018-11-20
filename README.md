# CShell
#### CrystalSimonhell
Making a shell in C

## How to Run
1. In a bash shell, run:
  `$ make`
  `$ make run`
  
## Working Features
* cd
  * Needs a '/' at the end of the path to work
* exit
* Basic bash commands
  * e.g. ls, ps, etc.
* Semicolon parsing
  * Supports multiple commands
* Shows current working directory
* Supports arguments for commands

## To Be Added
* Tab autocomplete
* Piping
* Stdin/Stdout redirection
* Errors
* Catch ctrl-c

## Limits
* 1000 character input max
* 10 arguments per command max

## Function Descriptions


## Known Bugs
* Shows error for trailing semicolon