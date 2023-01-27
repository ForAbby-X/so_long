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

NAME	= so_long

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
		  game_drawing.c \
		  particles.c \
		  raycast.c \
		  collisions.c \
		  uuid.c \
		  entities.c \
		  entities_utils.c \
		  ent_tank.c \
		  ent_tank_drawing.c \
		  ent_bullet.c \
		  ent_enn_base.c \
		  ent_shell.c \
		  ent_coin.c \
		  ent_exit.c

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

raw: CFLAGS += -O0
raw: obj $(ENGINE_LIB) $(NAME)

fast: CFLAGS += -Ofast
fast: obj $(ENGINE_LIB) $(NAME)

debug: CFLAGS += -g3
debug: obj $(ENGINE_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) -lm $+ $(ENGINE_LNK)

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCDIR) $(ENGINE_INC) -c $< -o $@

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
