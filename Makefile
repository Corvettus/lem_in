NAME = lem_in

COMP = gcc

FLS =

LIB_NAME = libft

LIB_DIR = ./libft

SRCS = main.c \
       dijkstra_1.c dijkstra_2.c \
	   rooms_n_links.c \
	   read_check.c checker.c is_room.c \
	   set.c init.c get.c get2.c \
	   compl.c \
       writing.c \
	   link.c mat.c path.c \
	   ways.c rooms.c \
	   del.c

OBJS = $(SRCS:.c=.o)

all: $(LIB_NAME) $(NAME)

$(LIB_NAME):
	@make -C $(LIB_NAME)

$(NAME):
	@$(COMP) $(FLS) -c $(SRCS)
	@$(COMP) $(FLS) -o $(NAME) $(OBJS) -L $(LIB_DIR) -lft

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIB_NAME) $(NAME)