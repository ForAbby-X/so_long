# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 09:39:09 by alde-fre          #+#    #+#              #
#    Updated: 2022/11/25 09:39:09 by alde-fre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long.out

# directories
SRCDIR	=	./src
INCDIR	=	-I ./inc
OBJDIR	=	./obj

# src / includes / obj files
SRC		= main.c \
		  utils.c \
		  menu_1.c \
		  menu_2.c \
		  map.c \
		  parsing_1.c \
		  parsing_2.c \
		  init_game.c \
		  map_loader.c \
		  game_render.c \
		  game_render_2.c \
		  particles_1.c \
		  particles_2.c \
		  raycast.c \
		  collisions.c \
		  uuid.c \
		  entities/entities.c \
		  entities/utils.c \
		  entities/tank.c \
		  entities/tank_drawing.c \
		  entities/bullet.c \
		  entities/enn_base.c \
		  entities/enn_action.c \
		  entities/shell.c \
		  entities/coin.c \
		  entities/exit.c \
		  entities/objects.c

INC		= game.h

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= clang
CFLAGS	= -MMD -Wall -Wextra -Werror

# engine library
ENGINE		= ./engine/
ENGINE_LIB	= $(addprefix $(ENGINE),libengine.a)
ENGINE_INC	= -I ./engine/inc
ENGINE_LNK	= -l Xext -l X11 -L ./engine -l engine

all: obj $(ENGINE_LIB) $(NAME)

malloc_test: obj $(ENGINE_LIB) $(NAME)
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ $(OBJ) $(ENGINE_LNK) -L. -lmallocator

raw: CFLAGS += -O0
raw: obj $(ENGINE_LIB) $(NAME)

fast: CFLAGS += -Ofast
fast: obj $(ENGINE_LIB) $(NAME)

debug: CFLAGS += -g3
debug: obj $(ENGINE_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	@echo "\e[1;35mLinking...\e[0m"
	@$(CC) -o $(NAME) $+ $(ENGINE_LNK) -lm
	@echo "\e[1;32m➤" $@ "created succesfully !\e[0m"

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "\e[1;36m[\e[0;36mC\e[1;36m]\e[0;36m → " $<"\e[0m"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCDIR) $(ENGINE_INC) -c $< -o $@

temp:
	@echo "\e[1;36mCompiling...\e[0m";

$(ENGINE_LIB):
	@make -C $(ENGINE)

clean:
	rm -rf $(OBJDIR)
	make -C $(ENGINE) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(ENGINE) fclean

re: fclean all

.PHONY: all clean fclean re
