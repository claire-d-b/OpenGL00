.SUFFIXES:

NAME	=	executable
LIST	=	Graphics \
			Errors \
			Window \
			Render \
			# Scene \
			# Shaders \
			Errors \
			Window \

# LIST	=	Example2 \

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address -MMD -std=c++98
CC		=	clang++
GL_LIB	=	-I./includes/vendors/GLFW -framework Cocoa -framework OpenGL -framework IOKit -L./includes/vendors/GLFW/lib -lglfw3 -lGLEW

S_DIR	=	srcs/
I_DIR	=	includes/
O_DIR	=	objs/
D_DIR	=	deps/

C_SUFF	=	.cpp
O_SUFF	=	.o
D_SUFF	=	.d

DIR_O	=	@mkdir -p objs/
DIR_D	=	@mkdir -p deps/

RM_FILE	= rm -f
RM_DIR	= rm -rf

LIST_C	= $(addprefix $(S_DIR), $(LIST))
LIST_O	= $(addprefix $(O_DIR), $(LIST))
LIST_D	= $(addprefix $(D_DIR), $(LIST))

SRCS	= $(addsuffix $(C_SUFF), $(LIST_C))
OBJS	= $(addsuffix $(O_SUFF), $(LIST_O))
DEPS	= $(OBJS:.o=.d)

$(O_DIR)%.o	:	$(S_DIR)%.cpp
				$(DIR_O)
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(GL_LIB)

all	:			$(NAME)

clean	:		
				$(RM_DIR) $(O_DIR) $(D_DIR)

fclean	:		clean
				$(RM_FILE) $(NAME)

re	:			fclean all

.PHONY	:		all clean fclean re

-include	$(DEPS)