PIPEX		=	pipex

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
INCLUDES	=	-I./includes

HEADER		=	./includes/pipex.h

SRCS_DIR	=	srcs/
SRCS_LIST	=	pipex.c \
				parsing_data.c \
				utils.c \
				ft_split.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strdup.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS		=	$(patsubst %.c, %.o, $(SRCS_LIST))

all : $(PIPEX)

$(PIPEX) : Makefile $(HEADER) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(INCLUDES)
	@printf "'$(PIPEX)' was compiled\n"

%.o : $(addprefix $(SRCS_DIR), %.c) $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean :
	@rm -rf $(OBJS)
	@printf "command 'clean' was done\n"

fclean : clean
	@rm -rf $(PIPEX)
	@printf "command 'fclean' was done\n"

re : fclean all
	@printf "command 're' was done\n"

.PHONY: all clean fclean re bonus
