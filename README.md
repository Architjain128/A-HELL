# Archit's Shell (A-Hell)

## How to run
    run following commands in terminal
        ->  make
        -> ./A-Hell

    to remove object and text files 
        -> make clean

## Features
+ pwd 
+ echo 
+ cd
+ ls
+ pinfo
+ exit/quit  ( also by pressing Ctrl+d )
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
    * Ctrl+Z  : stopped foreground and send it in background 
    * Ctrl+C  : kill any foreground process
    * Ctrl+D  : exit shell (EOF) 

- BONUS COMMANDS
    + history
    + nightswatch
        + interrupt
        + newborn
    + last dir by `cd -` : assuming that in starting of shell lastdir = executable address (till directory changes)
    + exit status along with prompt
    + chaining commands with `@` as AND, and `$` as OR

- EXTRA COMMANDS
    + to clear the terminal screen by system("clear")
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
    + pipe.c : code to execute piping with redirection (SP3)
    + ppp.c : helper code for pipe.c
    + setenv.c     : code for setenv command
    + unsetenv.c     : code for unsetenv command
    + jobs.c : code for jobs command
    + kjob.c : code for kjob command
    + overkill.c : code for overkill command
    + fg.c : code for fg command
    + bg.c : code for bg command
    + boom.c : code for chained commands


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
    + pipe.h
    + ppp.h
    + setenv.h
    + unsetenv.h
    + jobs.h
    + kjob.h
    + fg.h
    + bg.h
    + overkill.h
    + boom.h

+ makefile   

+ README.md  : itself 

* All other files are useless in hell

## ASSUMPTIONS
+ Outputs of all internal processes can redirected to a file but inputs cannot 
+ In piping, pipine+redirection and chaining we use don't use internal commands
+ exit status is set neutral for chainned commands and exit staus `SUCESS` for complete execution or WARNING in a command else if any ytype of error detected it will be set as `FAILURE` 
+ `WARNING` status in yellow colour if cmd has extra arguments, then the ouput will be for minimal( default with no flags ) cmd
+ `ERROR` status in red colour if cmd is facing error with corresponding error 
+ added colours in prompt to deffrentiate it by other
+ added extra msg at starting and exit position

## POSSIBLE ERRORS
+ printing of prompt twice when `q+enter` is pressed in nightswatch (one for q+enter and other for next command ig!code)




