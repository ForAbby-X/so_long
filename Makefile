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
SRCDIR	=	./engine/src
INCDIR	=	-I ./engine/includes
OBJDIR	=	./engine/obj

# src / includes / obj files
SRC		= engine.c \
		  engine_config.c \
		  event_1.c \
		  event_2.c \
		  color.c \
		  drawing_1.c \
		  drawing_2.c \
		  drawing_3.c \
		  sprite_1.c \
		  utils.c \
		  \
		  main.c \
		  init_game.c \
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

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= clang
CFLAGS	= -MMD -Wall -Wextra -Werror -g3

# mlx library
MLX		= ./engine/minilibx-linux/
MLX_LIB	= $(addprefix $(MLX),mlx_Linux.a)
MLX_INC	= -I $(MLX)
MLX_LNK	= -L $(MLX) -l mlx -lXext -lX11

# ft library
FT		= ./engine/libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./engine/libft
FT_LNK	= -L ./engine/libft -l ft -l pthread

# vec library
VEC		= ./engine/libvec/
VEC_LIB	= $(addprefix $(VEC),libvec.a)
VEC_INC	= -I ./engine/libvec/inc
VEC_LNK	= -L ./engine/libvec -l vec

# vectors library
VECTOR		= ./engine/libvector/
VECTOR_LIB	= $(addprefix $(VECTOR),libvector.a)
VECTOR_INC	= -I ./engine/libvector/inc
VECTOR_LNK	= -L ./engine/libvector -l vector

all: obj $(VECTOR_LIB) $(VEC_LIB) $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(VECTOR_INC) $(VEC_INC) $(MLX_INC) $(FT_INC) $(INCDIR) -o $@ -c $<

$(VECTOR_LIB):
	@make -C $(VECTOR)

$(VEC_LIB):
	@make -C $(VEC)

$(FT_LIB):
	@make -C $(FT)

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(VECTOR_LNK) $(VEC_LNK) $(MLX_LNK) $(FT_LNK) -lm -lrt -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(VECTOR) clean
	make -C $(VEC) clean
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(VECTOR) clean
	make -C $(VEC) fclean
	make -C $(FT) fclean
	make -C $(MLX) clean

re: fclean all
