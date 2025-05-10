CYAN = \033[94m
RESET = \033[0m

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11 -O2

SRCS = *.c
OUT = out.out

DEFAULT = matrices4

all:
	@$(CC) $(CFLAGS) $(SRCS) -o $(OUT)

run-bruteforce-%: all
	@echo "$(CYAN)Multiplying using brute force with n = $*...$(RESET)"
	@./$(OUT) 0 $*

run-divideconquer-%: all
	@echo "$(CYAN)Multiplying using native divide and conquer with n = $*...$(RESET)"
	@./$(OUT) 1 $*

run-strassens-%: all
	@echo "$(CYAN)Multiplying using Strassen's algorithm with n = $*...$(RESET)"
	@./$(OUT) 2 $*

clean:
	@echo "$(CYAN) Cleaning up$(RESET)"
	@rm $(OUT)


