##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

CXXFLAGS += -std=c++20 -shared -fPIC -I../../includes/

OBJ	=	$(SRC:.cpp=.o)

SRC_SPHERE = ./Sphere.cpp

SRC_PLANE = ./Plane.cpp

SRC_CONES = ./Cones.cpp

SRC_TRIANGLE = ./Triangle.cpp

SRC_CYLINDER = ./Cylinder.cpp

SRC_TORUS = ./Torus.cpp

SRC_CUBE = ./Cube.cpp

NAME = arcade

all:
	g++ $(CXXFLAGS) $(SRC_SPHERE) -o ../plugins/Sphere.so
	g++ $(CXXFLAGS) $(SRC_PLANE) -o ../plugins/Plane.so
	g++ $(CXXFLAGS) $(SRC_CONES) -o ../plugins/Cones.so
	g++ $(CXXFLAGS) $(SRC_TRIANGLE) -o ../plugins/Triangle.so
	g++ $(CXXFLAGS) $(SRC_CYLINDER) -o ../plugins/Cylinder.so
	g++ $(CXXFLAGS) $(SRC_TORUS) -o ../plugins/Torus.so
	g++ $(CXXFLAGS) $(SRC_CUBE) $(SRC_PLANE) -o ../plugins/Cube.so
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