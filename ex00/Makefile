NAME = btc

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRC = main.cpp BitcoinExchange.cpp

OBJ = $(SRC:.cpp=.o)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

fast: re
	make clean

.PHONY: all clean fclean re fast