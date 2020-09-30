# Archit's Shell (A-Hell)

## How to run
    run following commands in terminal
        ->  make
        -> ./A-Hell

    to remove objectfiles 
        -> make clean

## Features
+ pwd 
+ echo 
+ cd
+ ls
+ pinfo
+ exit/quit
+ foreground commands
+ background commands with exit status
+ redirection only
+ piping only
+ piping + redirection 
+ setenv
+ unsetenv
+ jobs
+ kjob
+ fg
+ bg
+ overkill

- Signal Detection
    * Ctrl+Z  : stopped foreground and send it in background  `pending`
    * Ctrl+C  : kill any foreground process
    * Ctrl+D  : exit shell (EOF)  `faulty`

- BONUS COMMANDS
    + history
    + nightswatch
        + interrupt
        + nerborn
    + last dir : assuming that in starting of shell lastdir = executable address (till directory changes)
    + exit status 
    + chaining commands 

- EXTRA COMMANDS
    + to clear the terminal screen by system("cls")
        * syntax -> clear


## Modular Explaination
+ C files
    + archit.c    : main + exiting shell(quit | exit | EOF(Ctrl+D)) + signals ( Ctrl+C , Ctrl+Z )
    + prompt.c    : codes for printing prompt
    + cd.c        : codes for cd command
    + echo.c      : codes for echo command
    + pwd.c : codes for pwd command
    + ls.c : codes for ls command
    + pinfo.c : codes for pinfo command
    + cmd.c       : codes for back/foreground command 
    + history.c   : codes for history command 
    + nightwatch.c    :codes for nightswatch command
    + redi.c : code for redirection commands only(SP1)
    + piponly.c : code for pipeonly commands only(SP2)
    + env.c     : new cmds (setenv,unsetenv)
    + jobs.c : new cmds (jobs,kjob,fg,bg,overkill)


+ Header file
    + header.h
    + prompt.h
    + cd.h
    + echo.h
    + pwd.h
    + ls.h
    + pinfo.h
    + cmd.h
    + history.h
    + nightswatch.h
    + redi.h
    + piponly.h
    + added.h

+ makefile   

+ README.md  : itself 
* Except all are useless in hell 

## ASSUMPTIONS
+ Outputs of all internal processes can redirected to a file but inputs cannot 
+ In piping, pipine+redirection and chaining we use don't use internal commands
+ WARNING status in yellow colour if cmd has extra arguments, then the ouput will be for minimal( default with no flags ) cmd
+ ERROR status in red colour if cmd is facing error with corresponding error 
+ added colours in prompt to deffrentiate it by other
+ added extra msg at starting and exit position

## POSSIBLE ERRORS
+ printing of prompt twice when q+enter is pressed in nightswatch (one for q+enter and other for next command ig!code)



