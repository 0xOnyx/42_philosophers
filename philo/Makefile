NAME = philo

SRC_PATH 	= src/
SRC_OBJ		= objs/
SRC_HEADER	= includes/

HEADER	= philo.h
SRC		= main.c init_philo.c routine_philo.c utils.c

CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
OPTIONS	= -I$(SRC_HEADER)
LIBS		= -lpthread

SRCS = $(addprefix $(SRC_PATH),$SRC)
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(SRC_OBJ),$(OBJ))
HEADERS = $(addprefix $(SRC_HEADER),$(HEADER))

CC = gcc
RM = rm -f

$(SRC_OBJ)%.o: $(SRC_PATH)%.c $(HEADERS)
	$(CC) $(CLFAGS) $(OPTIONS) -o $(@) -c $(<)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LIBS) $(CFLAGS) $(OPTIONS) -o $(@) $(^)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re
