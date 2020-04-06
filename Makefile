##
##
##

CPPFLAGS	= -g -Wall -Wextra -W -Iinclude -lcaca -std=c++17 -ldl \
			-lsfml-window -lsfml-system -lsfml-audio -lsfml-network \
			-lsfml-graphics

GPP		= g++

RM		= rm -f

## ========== CORE ==========

NAME		= arcade

SRCS_CORE		=   src/main.cpp         	\
				src/Core.cpp				\
				src/Error.cpp				\
				src/Menu.cpp				\
				src/SoLoader.cpp


OBJS_CORE		= $(SRCS_CORE:.cpp=.o)

FLAGSCORE = -g -Wall -Wextra -W -Iinclude -lcaca -std=c++17 -ldl \
			-lsfml-window -lsfml-system -lsfml-audio -lsfml-network \
			-lsfml-graphics

## ========== GRAPHICS ==========

## SFML

NAME_SFML = 	lib/lib_arcade_sfml.so

SRCS_SFML = 	lib/Sfml.cpp

FLAGS_SFML = 	-fPIC -shared

## LIBCACA

NAME_LIBCACA = 	lib/lib_arcade_libcaca.so

SRCS_LIBCACA = 	lib/libcaca.cpp

FLAGS_LIBCACA = -shared -fPIC

## NCURSES

NAME_NCURSES = 	lib/lib_arcade_ncurses.so

SRCS_NCURSES = 	lib/ncurses.cpp

FLAGS_NCURSES =	-shared -fPIC

## ========== GAME ==========

## SOLARFOX

NAME_SOLARFOX = 	games/game_arcade_solarfox.so

SRCS_SOLARFOX = 	games/solarfox.cpp

FLAGS_SOLARFOX = 	-shared -fPIC

## SNAKE

NAME_SNAKE = 	games/game_arcade_nibbler.so

SRCS_SNAKE = 	games/snake.cpp

FLAGS_SNAKE = 	-shared -fPIC




## ========== INSTRUCTIONS ==========

all:			core games graphicals

core: 			$(NAME)

graphicals: 	$(NAME_SFML) $(NAME_NCURSES) $(NAME_LIBCACA)

games: 			$(NAME_SOLARFOX) $(NAME_SNAKE)




## ========== COMPILATION ==========

## CORE

$(NAME):	$(OBJS_CORE)
	$(GPP) $(OBJS_CORE) -o $(NAME) $(CPPFLAGS) -L.

## GRAPHICALS

$(NAME_SFML):
	$(GPP) $(FLAGS_SFML) $(SRCS_SFML) -o $(NAME_SFML)

$(NAME_LIBCACA):
	$(GPP) $(FLAGS_LIBCACA) $(SRCS_LIBCACA) -o $(NAME_LIBCACA)

$(NAME_NCURSES):
	$(GPP) $(FLAGS_NCURSES) $(SRCS_NCURSES) -o $(NAME_NCURSES)


## GAMES

$(NAME_SOLARFOX):
	$(GPP) $(FLAGS_SOLARFOX) $(SRCS_SOLARFOX) -o $(NAME_SOLARFOX)

$(NAME_SNAKE):
	$(GPP) $(FLAGS_SNAKE) $(SRCS_SNAKE) -o $(NAME_SNAKE)




## ========== OTHERS INSTRUCTIONS ==========

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME) $(OBJS_CORE) $(NAME_SFML) $(NAME_LIBCACA) $(NAME_NCURSES) $(NAME_SOLARFOX) $(NAME_SNAKE)

re:		fclean all

.PHONY:		all clean fclean re
