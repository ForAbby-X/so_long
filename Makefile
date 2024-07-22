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
		  [1]utils.c \
		  [2]utils.c \
		  init_game.c \
		  map/map.c \
		  map/loader.c \
		  map/[1]parsing.c \
		  map/[2]parsing.c \
		  render/[1]game.c \
		  render/[2]game.c \
		  render/[1]menu.c \
		  render/[2]menu.c \
		  particles_1.c \
		  particles_2.c \
		  raycast.c \
		  collisions.c \
		  uuid.c \
		  entities/entities.c \
		  entities/utils.c \
		  entities/tank.c \
		  entities/rambo.c \
		  entities/rambo_update.c \
		  entities/tank_update.c \
		  entities/tank_drawing.c \
		  entities/bullet.c \
		  entities/enn_base.c \
		  entities/enn_action.c \
		  entities/shell.c \
		  entities/coin.c \
		  entities/exit.c \
		  entities/objects.c \
		   \
		  generator/manager.c \
		  generator/recursive.c \
		  generator/rooms.c \


INC		= game.h

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

DEPENDS := $(patsubst %.o,%.d,$(OBJ))
-include $(DEPENDS)

# compiler
CC		= cc
CFLAGS	= -MMD -MP -Wall -Wextra -Werror

# engine library
ENGINE		= ./engine/
ENGINE_LIB	= $(addprefix $(ENGINE),libengine.a)
ENGINE_INC	= -I ./engine/inc
ENGINE_LNK	= -l Xext -l X11 -L ./engine -l engine -l m

all: obj $(ENGINE_LIB) $(NAME)

raw: CFLAGS += -O0
raw: obj $(ENGINE_LIB) $(NAME)

fast: CFLAGS += -Ofast
fast: obj $(ENGINE_LIB) $(NAME)

debug: CFLAGS += -g3
debug: obj $(ENGINE_LIB) $(NAME)

obj:
	@rm -rf .print
	@mkdir -p $(OBJDIR)

.print:
	@> $@
	@echo "\e[1;36mCompiling...\e[0m"

$(NAME): $(OBJ)
	@echo "\e[1;35mLinking...\e[0m"
	@$(CC) -o $(NAME) $+ $(ENGINE_LNK)
	@echo "\e[1;32m➤" $@ "created succesfully !\e[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c .print
	@echo "\e[0;36m ↳\e[0;36m" $<"\e[0m"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCDIR) $(ENGINE_INC) -c $< -o $@

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
