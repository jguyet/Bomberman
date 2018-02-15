# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 12:48:21 by frmarinh          #+#    #+#              #
#    Updated: 2017/09/14 19:08:39 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = network.a

SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/

SRCS_BASE			=	Packet.cpp							\
						messages/ServerListMessage.cpp		\

SRCS	=	$(addprefix $(SRCDIR), $(SRCS_BASE))
OBJS	=	$(addprefix $(OBJDIR), $(SRCS_BASE:.cpp=.o))
CC		=	g++ -std=c++1z

FLAGS =

all: $(NAME)

$(NAME):
	@echo "Builiding the network library..."
	@make BUILD

BUILD: $(OBJDIR) $(OBJS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(dir $(OBJS))

$(OBJDIR)%.o : $(SRCDIR)%.cpp | $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@											\
		-I $(INCDIR)													\

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re:		fclean all
