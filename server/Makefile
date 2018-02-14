# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/15 12:05:50 by frmarinh          #+#    #+#              #
#    										          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BOMBER_SERVER	=	bomber_server

NAME		=   "Bomber Server"
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	g++ -std=c++1z
FLAGS 		=
#FLAGS		=	-Wall -Wextra -Werror
FLAGS_O		=

SRCDIR_BOMBER_SERVER		=	srcs/
OBJDIR_BOMBER_SERVER		=	objs/

INCDIR				=	includes/

SRCBASE_BOMBER_SERVER	=	\
					main.cpp								\

INCS			=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_BOMBER_SERVER			=	$(addprefix $(SRCDIR_BOMBER_SERVER), $(SRCBASE_BOMBER_SERVER))
OBJS_BOMBER_SERVER			=	$(addprefix $(OBJDIR_BOMBER_SERVER), $(SRCBASE_BOMBER_SERVER:.cpp=.o))

.SILENT:

all:		ACTIONS

ACTIONS:
	if test -f $(NAME_BOMBER_SERVER) ; then											\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make BUILD 			&& 														\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&    \
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";			\
	fi

$(OBJDIR_BOMBER_SERVER):
	mkdir -p $(OBJDIR_BOMBER_SERVER)
	mkdir -p $(dir $(OBJS_BOMBER_SERVER))

$(OBJDIR_BOMBER_SERVER)%.o : $(SRCDIR_BOMBER_SERVER)%.cpp | $(OBJDIR_BOMBER_SERVER)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(INCDIR)														\
		-I $(INCDIR)

fcleanlib:	fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

BUILD: $(OBJDIR_BOMBER_SERVER) $(OBJS_BOMBER_SERVER)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_BOMBER_SERVER) $(OBJS_BOMBER_SERVER)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_BOMBER_SERVER)"

clean:
	@rm -rf $(OBJDIR_BOMBER_SERVER)
	echo "\r\033[38;5;124m📕  CLEAN $(OBJDIR_BOMBER_SERVER)\033[0m\033[K";

fclean:		clean
	@rm -rf $(NAME_BOMBER_SERVER)
	echo "\r\033[38;5;124m📕  FCLEAN $(NAME_BOMBER_SERVER)\033[0m\033[K";

-include $(OBJS:.o=.d)
