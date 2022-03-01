NAME	=	pipex

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

INCLUDES	=	includes
HEADER		=	pipex.h
B_HEADER	=	pipex_bonus.h
FUNC_HEADER	=	functions.h

SRCS_DIR		=	srcs
B_SRCS_DIR		=	srcs_bonus
SRCS_DIR_FUNC	=	functions

SRCS_LIST	=	pipex.c \
				parsing_data.c \
				utils.c
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS_LIST))

SRCS_LIST_FUNC	=	ft_strlen.c \
					ft_strdup.c \
					ft_strjoin.c \
					ft_split.c \
					ft_strncmp.c
SRCS_FUNC		=	$(addprefix $(SRCS_DIR_FUNC)/,$(SRCS_LIST_FUNC))

B_SRCS_LIST	=	pipex_bonus.c \
				parsing_data_bonus.c \
				parsing_paths_bonus.c \
				here_doc_bonus.c \
				open_files_bonus.c \
				child_process_bonus.c \
				free_pipex.c \
				utils_bonus.c
B_SRCS		=	$(addprefix $(B_SRCS_DIR)/,$(B_SRCS_LIST))

B_SRCS_LIST_FUNC	=	$(SRCS_LIST_FUNC) \
						ft_strcmp.c \
						ft_memmove.c \
						get_next_line.c \
						get_next_line_utils.c
B_SRCS_FUNC			=	$(addprefix $(SRCS_DIR_FUNC)/,$(B_SRCS_LIST_FUNC))

OBJS_DIR	=	objs

OBJS		=	$(addprefix $(OBJS_DIR)/,$(SRCS_LIST:.c=.o))
OBJS_FUNC	=	$(addprefix $(OBJS_DIR)/,$(SRCS_LIST_FUNC:.c=.o))

B_OBJS		=	$(addprefix $(OBJS_DIR)/,$(B_SRCS_LIST:.c=.o))
B_OBJS_FUNC	=	$(addprefix $(OBJS_DIR)/,$(B_SRCS_LIST_FUNC:.c=.o))

NORMAL		=	\033[0m
BOLD		=	\033[1m
UNDERLINE	=	\033[4m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
VIOLET		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

all : $(OBJS_DIR) $(NAME)

$(NAME) : $(OBJS) $(OBJS_FUNC)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)Project succesfully compiled"

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(INCLUDES)/$(HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating object file$(WHITE) --> $(notdir $@) --> $(GREEN)[Done]$(NORMAL)"

$(OBJS_DIR)/%.o : $(SRCS_DIR_FUNC)/%.c $(INCLUDES)/$(HEADER) $(INCLUDES)/$(FUNC_HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating object file$(WHITE) --> $(notdir $@) --> $(GREEN)[Done]$(NORMAL)"

$(OBJS_DIR) :
	@mkdir -p objs
	@echo "$(CYAN)Creating directory for objects file$(WHITE) --> $@ --> $(GREEN)[Done]$(NORMAL)"

bonus : $(OBJS_DIR) $(B_OBJS) $(B_OBJS_FUNC)
	@$(CC) $(CFLAGS) -o $(NAME) $(B_OBJS) $(B_OBJS_FUNC)
	@echo "$(GREEN)Project update for bonus"

$(OBJS_DIR)/%.o : $(B_SRCS_DIR)/%.c $(INCLUDES)/$(B_HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating object file$(WHITE) --> $(notdir $@) --> $(GREEN)[Done]$(NORMAL)"

$(OBJS_DIR)/%.o : $(SRCS_DIR_FUNC)/%.c $(INCLUDES)/$(B_HEADER) $(INCLUDES)/$(FUNC_HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating object file$(WHITE) --> $(notdir $@) --> $(GREEN)[Done]$(NORMAL)"

clean :
	@rm -rf $(OBJS_DIR)
	@echo "$(VIOLET)Removing objects files$(WHITE) --> *.o --> $(GREEN)[Done]$(NORMAL)"

fclean : clean
	@rm -rf $(NAME)
	@echo "$(VIOLET)Removing perfoming file$(WHITE) --> $(NAME) --> $(GREEN)[Done]$(NORMAL)"

re : fclean all

.PHONY : all, clean, fclean, bonus