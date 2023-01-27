SHELL	=	/bin/bash

# Variables

NAME		= philo
INC			= includes
HEADER		= -I $(INC) -lpthread
SRC_DIR		= sources/
OBJ_DIR		= obj/
CC			= gcc
FLAGS		= -Wall -Werror -Wextra
RM			= rm -f
ECHO		= echo -e

# Colors

DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

# Sources

SRC_FILES	=	error ft_philo init main utils

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

start:
			@$(ECHO) -n "$(YELLOW)[Philosophers]:\t$(DEF_COLOR)"
			@$(ECHO) -n "$(RED)[$(DEF_COLOR)"
			@make all
			@$(ECHO) -n "$(RED)]$(DEF_COLOR)"

all:		$(NAME)

$(NAME):	$(OBJ) $(OBJF)
			@$(CC) $(FLAGS) $(OBJ) $(HEADER) -o $(NAME)
		
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJF)
			@$(ECHO) -n "$(ORANGE)=$(DEF_COLOR)"
			@$(CC) $(FLAGS) $(HEADER) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@touch $(OBJF)

clean:
			@$(RM) -r $(OBJ_DIR)
			@$(RM) $(OBJF)
			@$(ECHO) -n "$(BLUE)[Philosophers]:\tobject files$(DEF_COLOR)$(GREEN)  => Cleaned!$(DEF_COLOR)\n"

fclean:		clean
			@$(RM) $(NAME)
			@$(ECHO) -n "$(CYAN)[Philosophers]:\texec. files$(DEF_COLOR)$(GREEN)  => Cleaned!$(DEF_COLOR)\n"

re:			fclean start
			@$(ECHO) -n "\n$(GREEN)Cleaned and rebuilt everything for [Philosophers]!$(DEF_COLOR)\n"

norm:
			@clear
			@norminette $(SRC) $(INC) | grep Error

.PHONY:		start all clean fclean re norm
