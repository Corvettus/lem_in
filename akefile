NAME = lem_in

COMP = gcc

FLS =

LIB_NAME = libft

LIB_DIR = ./libft

SRCS = 

SRCS_PS = push_swap.c $(SRCS)

SRCS_CH = checker.c get_next_line.c $(SRCS)

OBJS_PS = $(SRCS_PS:.c=.o)
OBJS_CH = $(SRCS_CH:.c=.o)

all: $(LIB_NAME) $(NAME)

$(LIB_NAME):
	@make -C $(LIB_NAME)

$(NAME):
	@$(COMP) $(FLS) -c $(SRCS_PS)
	@$(COMP) $(FLS) -o $(PUSH_SWAP) $(OBJS_PS) -L $(LIB_DIR) -lft

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS_PS)
	@/bin/rm -f $(OBJS_CH)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(PUSH_SWAP)
	@/bin/rm -f $(CHECKER)

re: fclean all

.PHONY: all clean fclean re $(LIB_NAME) $(NAME)