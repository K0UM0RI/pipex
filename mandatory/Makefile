NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = pipex.c \
	../utils/ft_split.c \
	../utils/getcmd.c \
	../utils/pipexutils.c \
	../utils/utils_utils.c \
	../utils/utils.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) ../pipex.h

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

.SECONDARY: $(NAME) $(OBJ)