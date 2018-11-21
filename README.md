# CShell
#### CrystalSimonhell
Making a shell in C

## How to Run
1. In a bash shell, run:
Test
~~~
$ make
~~~
2. Then run:
~~~
$ make run
~~~


## Working Features
* `$ cd`
  * Needs a '/' at the end of the path to work
* `$ exit`
* Basic bash commands
  * e.g. `ls`, `ps`, etc.
* Semicolon parsing
  * Supports multiple commands
  * Filters empty commands
* Shows current working directory
* Supports arguments for commands
* Catches ctrl-c
* Arbitrary whitespace support
* Catches invalid commands

## To Be Added
* Tab autocomplete (maybe)
* Piping
* Stdin/Stdout redirection
* Quote support
* History
* Catch enter after spaces

## Limits
* 1000 character input max
* 10 arguments per command max

## Function Descriptions


## Known Bugs
* No support for quotes
