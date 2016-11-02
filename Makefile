CC = gcc
CFLAGS = -Wall -Wc99-extensions -O2

SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.c)
HDR = $(wildcard $(SRCDIR)/*.h)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

test.x: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ) test.x

_temp: 
	gcc -c src/cpdb.c src/utils.c
	ar rcs ~/Dropbox/tmp/brewer/macOS/libcpdb.a cpdb.o utils.o
	cp src/cpdb.h ~/Dropbox/tmp/brewer/macOS/

