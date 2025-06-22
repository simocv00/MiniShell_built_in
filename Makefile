NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

SRC = create_env_node.c ft_cd.c ft_env.c ft_putstr_fd.c ft_strcmp.c helper_func.c export_map.c ft_echo.c ft_exit.c ft_pwd.c get_env_str.c main.c ft_unset.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re