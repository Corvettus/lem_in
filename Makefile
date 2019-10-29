NAME = lem_in

COMP = gcc

FLS =

LIB_NAME = libft

LIB_DIR = ./libft

SRCS = main.c \
       lem_in.c \
	   ft_input.c \
	   ft_make.c \
	   get_next_line.c

OBJS_CH = $(SRCS:.c=.o)

all: $(LIB_NAME) $(NAME)

$(LIB_NAME):
	@make -C $(LIB_NAME)

$(NAME):
	@$(COMP) $(FLS) -c $(SRCS)
	@$(COMP) $(FLS) -o $(NAME) $(OBJS) -L $(LIB_DIR) -lft -I get_next_line.h

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIB_NAME) $(NAME)