NAME     = phonebook

CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes

SRCS = 		main.cpp \
			src/Contact.cpp \
			src/PhoneBook.cpp

OBJS     = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
