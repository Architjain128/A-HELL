CC = gcc
CFLAGS = -Wall
DFLAGS = -lm
OBJFILES = archit.o  jobs.o env.o prompt.o pwd.o cd.o echo.o ls.o cmd.o pinfo.o history.o nightwatch.o redi.o pipe.o 
TARGET = A-Hell
TEXT = history.txt

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) $(DFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) $(TEXT)*~
