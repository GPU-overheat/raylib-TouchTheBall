CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lraylib -lm

SRC = main.c util.c
OBJ = $(SRC:.c=.o)

EXEC = run

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
