SRC = main.cpp BitcoinExchange.cpp
OBJ = $(SRC:.cpp=.o)
CXX = c++ -Wall -Wextra -Werror -std=c++98
NAME = btc

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
