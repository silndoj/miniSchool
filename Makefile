NAME				= 	minishell

CC					=	cc
FLAGS				=   -Wextra -Wall -Werror 

SRCS_MAIN			= 	src/main.c				\
						src/utils.c				\
						src/parsing_stuff.c 	\
						src/builtin.c 			\
						src/history_stuff.c 	\
						src/var_stuff.c 		\
						src/export_builtin.c 	\
						src/execute.c			\
						src/exec_utils.c 		\
						src/utils2.c 			\
						src/free.c				\
						src/builtin2.c			\
						src/handle_infile.c		\
						src/handle_outfile.c	\
						src/execute_pipes.c		\
						src/signal.c			\
						src/garbage_collector.c \
						src/parse_pipe.c		\
						src/allocation_stuff.c

LIBFT 				=	tools/libft/libft.a

OBJ 				=	tools/obj
OBJ_MAIN			=	$(SRCS_MAIN:src/%.c=$(OBJ)/%.o)

all:						$(NAME)

$(LIBFT):
				@cd tools/libft && make -s && make bonus -s

$(NAME):$(LIBFT) $(OBJ_MAIN)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_MAIN) -L./tools/libft -lft -lreadline

$(OBJ)/%.o:	src/%.c
			@cd tools
			@mkdir -p $(OBJ)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -rf $(OBJ)/*
			@cd tools/libft && make clean -s


fclean: 			clean
			@rm -rf $(NAME)
			@rm -rf $(OBJ)
			@cd tools/libft && make fclean -s

re:			fclean all

.PHONY:		all clean fclean re
