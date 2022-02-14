PIPEX		=	pipex

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
LIBRARIES	=	-L./libft -lft
INCLUDES	=	-I./includes

LIBFT		=	./libft/libft.a
HEADER		=	./includes/pipex.h

SRCS_DIR	=	srcs/
SRCS_LIST	=	pipex.c \
				parsing_data.c \
				utils.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS		=	$(patsubst %.c, %.o, $(SRCS_LIST))

all : $(PIPEX)

$(PIPEX) : Makefile $(HEADER) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBRARIES) $(INCLUDES)
	@printf "'$(PIPEX)' was compiled\n"

$(LIBFT) : ./libft/Makefile ./libft/libft.h ./libft/*.c
	@make -C ./libft
	@make bonus -C ./libft
	@printf "'libft' was compiled\n"

%.o : $(addprefix $(SRCS_DIR), %.c) $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean :
	@make clean -C ./libft
	@rm -rf $(OBJS)
	@printf "command 'clean' was done\n"

fclean : clean
	@make fclean -C ./libft
	@rm -rf $(PIPEX)
	@printf "command 'fclean' was done\n"

re : fclean all
	@printf "command 're' was done\n"

.PHONY: all clean fclean re bonus
