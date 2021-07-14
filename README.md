# simple-cli
Simple CLI module

## Intro
This CLI module is simple - no dynamic memory allocation, only one type of delimiter character. 

There is a maximum number of commands to be added to the parser. Also a maximum number of parameters 
to be tokenized (if more, then they are passed as the last one not delimited). Check the `cli.h` for more
details.

## Project structure
The platform-specyfic software is in the `src/platform/` directory. The core code is in the `src/` directory.

## Operation
The CLI needs to be initialized with a function printing string to a desired output.
This is required for the help command and (if set) the invalid command note.

CLI will try to parse the input in it's buffer and execute one of matching command added earlier.

## Compile
Just run `make clean && make` to prepare and compile the solution.

## Run
The example is compiled to the `build/` directory. Run the executable for an example.
