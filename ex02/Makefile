SRC = ./src/
INCLUDE = ./include

file = $(addprefix $(SRC), main.cpp PmergeMe.cpp)

NAME =  PmergeMe

cc = c++
flag = -Wall -Wextra -Werror -std=c++98 -g
fileobj = $(file:.cpp=.o)
all : $(NAME)

.cpp.o:
	$(cc) $(flag) -I$(INCLUDE) -c $< -o $@
$(NAME) : $(fileobj)
			$(cc) $(flag) -I$(INCLUDE) $(fileobj) -o $(NAME)

clean:
			rm -f $(fileobj)
fclean: clean
			rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re