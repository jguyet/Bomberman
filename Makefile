# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/25 15:18:38 by jguyet            #+#    #+#              #
#    Updated: 2017/03/19 04:47:40 by jguyet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STUDENT			=	jguyet

AUTHOR			=	auteur

PROG1			=	Bomberman

BUILD_DIR		=	build

CMAKE_BUILDER	=	$(BUILD_DIR)/build.sh

.SILENT:

all:	$(BUILD_DIR)
	if test -f $(PROG1) ; then																\
		echo "make: Nothing to be done for \`all\`.";										\
	else																					\
		$(MAKE) -j $(PROG1);																\
	fi

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	echo "cd build\nmkdir external_libraries\ncmake .." > $(CMAKE_BUILDER)


$(PROG1):
	echo "\033[38;5;115mBUILD CMAKE  :\033[00m"
	sh $(CMAKE_BUILDER)
	echo "\033[38;5;115mBUILD MAKEFILE  :\033[00m"
	make -C $(BUILD_DIR)
	cp $(BUILD_DIR)/$(PROG1) .
	echo "\033[38;5;227mAUTHOR  :\033[0m"
	cat -e $(AUTHOR)

clean:
	echo "\033[38;5;124mCLEAN\033[00m $(PROG1)"
	rm -rf $(BUILD_DIR)/$(PROG1)
	rm -rf $(PROG1)

fclean:	clean
	echo "\033[38;5;124mFCLEAN\033[00m $(PROG1)"
	rm -rf $(BUILD_DIR)

re:		fclean all

compile:	clean
	echo "\033[38;5;124mCOMPILE\033[00m $(PROG1)"
	make -C $(BUILD_DIR)
	cp $(BUILD_DIR)/$(PROG1) .
	echo "\033[38;5;227mAUTHOR  :\033[0m"
	cat -e $(AUTHOR)


.PHONY: all clean fclean re
