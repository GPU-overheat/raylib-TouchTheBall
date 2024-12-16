CC = cc
CFLAGS = -Wall -Wextra
LDFLAGS = -lraylib -lm

SRC = main.c util.c startWindow.c
OBJ = $(SRC:.c=.o)

EXEC = run

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

cl:
	rm -f $(OBJ) $(EXEC)
