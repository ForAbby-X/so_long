NAME	= so_long.out

# /!\ WARNING /!\
# /!\ WARNING /!\
# echo 'hpet' > /sys/devices/system/clocksource/clocksource0/current_clocksource
# /!\ WARNING /!\
# /!\ WARNING /!\

# directories
SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

# src / includes / obj files
SRC		= main.c \
		  engine.c \
		  event_1.c \
		  event_2.c \
		  color.c \
		  drawing_1.c \
		  drawing_2.c \
		  sprite_1.c \
		  utils.c \
		  map_1.c \
		  map_2.c

INC		= engine.h

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -lm -lrt -O0


# mlx library
MLX		= ./minilibx-linux/
MLX_LIB	= $(addprefix $(MLX),mlx_Linux.a)
MLX_INC	= -I $(MLX)
MLX_LNK	= -L $(MLX) -l mlx -lXext -lX11

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft -l pthread

# vec library
VEC		= ./libvec/
VEC_LIB	= $(addprefix $(VEC),libvec.a)
VEC_INC	= -I ./libvec
VEC_LNK	= -L ./libvec -l vec

# vectors library
VECTOR		= ./libvector/
VECTOR_LIB	= $(addprefix $(VECTOR),libvector.a)
VECTOR_INC	= -I ./libvector
VECTOR_LNK	= -L ./libvector -l vector

all: obj $(VECTOR_LIB) $(VEC_LIB) $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(VECTOR_INC) $(VEC_INC) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(VECTOR_LIB):
	@make -C $(VECTOR)

$(VEC_LIB):
	@make -C $(VEC)

$(FT_LIB):
	@make -C $(FT)

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(VECTOR_LNK) $(VEC_LNK) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

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
