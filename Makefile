CC = gcc
CFLAGS = -Wall -Wextra -g

# List of source files
SRCS = lexer.c main.c parser.c pile.c

# List of object files
OBJS = $(SRCS:.c=.o)

# Name of the executable
TARGET = calc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)
