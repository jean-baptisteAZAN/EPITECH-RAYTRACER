##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

SRC = main.cpp \
	Engine/Engine.cpp

SFML_PATH = /opt/homebrew/opt/sfml/include

LIB_CONFIG = /opt/homebrew/opt/libconfig/include

CPPFLAGS	= -g -std=c++20 -W -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -I include/ -lconfig++ -pthread

CC			=	g++

OBJ			=	$(SRC:.cpp=.o)

NAME		=	raytracer

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJ)
	$(MAKE)	-C Shapes
	$(MAKE)	-C Lights

clean:
	rm -f $(OBJ)


fclean:	clean
	rm -f $(NAME)
	$(MAKE) fclean -C Shapes
	$(MAKE)	fclean -C Lights
	rm -rf plugins/*.so
	rm -rf vgcore*


re:	fclean all

macos: SFML_PATH = /opt/homebrew/opt/sfml@2.5.1/include

macos: LIB_CONFIG = /opt/homebrew/opt/libconfig/include

macos: CPPFLAGS = -std=c++20 -g -W -Wall -Wextra -I include/ -I $(LIB_CONFIG) -I $(SFML_PATH) -L /opt/homebrew/opt/libconfig/lib -L /opt/homebrew/opt/sfml@2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lconfig++

macos: $(NAME)

