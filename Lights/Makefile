##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

CXXFLAGS += -std=c++20 -shared -fPIC -I../../includes/

OBJ	=	$(SRC:.cpp=.o)

SRC_POINT_LIGHT = ./PointLight.cpp

SRC_FRONT_LIGHT = ./FrontLight.cpp

NAME = arcade

all:
	g++ $(CXXFLAGS) $(SRC_POINT_LIGHT) -o ../plugins/PointLight.so
	g++ $(CXXFLAGS) $(SRC_FRONT_LIGHT) -o ../plugins/FrontLight.so

clean :
	rm -rf $(OBJ)

lib:
	make -f Makefile.lib

fclean : clean
	rm -f $(NAME)
	rm -f vgcore*
	rm -f coding-style*
	rm -rf *.o

re : fclean all
