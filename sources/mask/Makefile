NAME	=	bin

CC	=	g++

SRC	=	Engine.cpp \
		main.cpp \
		Module.cpp \
		RPack.cpp \
		Screen.cpp \
		AButton.cpp \
		Field.cpp \
		Intersection.cpp \
		Arbitrator.cpp \
		Game.cpp \
		Player.cpp \
		Humain.cpp \
		Artificial.cpp \
		Patern.cpp \
		MainMenu.cpp

RM	=	rm -rf

CPPFLAGS	=	-W -Wall -Werror

LIB	=	-L/usr/local/lib

LL	=	-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

OBJ	=	$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):		$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB) $(LL) $(CFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
