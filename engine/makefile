# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 16:35:02 by alde-fre          #+#    #+#              #
#    Updated: 2023/02/27 12:42:28 by alde-fre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##########################################
#           Editable options             #
##########################################

# Compiler options
CC=clang
CFLAGS=-Wall -Wextra -Werror -Ofast
LDFLAGS=
BINARY_NAME=
LIBRARY_NAME=libengine.a

# Folders
SRC=src
INC=inc
BIN=bin
OBJ=obj

# Files
SOURCE_NAME= engine_1.c \
			 engine_2.c \
			 engine_config.c \
			 event_1.c \
			 event_2.c \
			 color.c \
			 drawing_1.c \
			 drawing_2.c \
			 drawing_3.c \
			 sprite_1.c \
			 utils.c \

##########################################
#    Don't touch anything below this     #
##########################################
SOURCE_FILES     = $(SOURCE_NAME:%.c=$(SRC)/%.c)
BINARY_FILES     = $(BINARY_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SOURCE_NAME:%.c=$(OBJ)/%.o)

# mlx library
MLX		= ./minilibx-linux/
MLX_LIB	= $(addprefix $(MLX),libmlx_Linux.a)
MLX_INC	= -I $(MLX)
MLX_LNK	= -lXext -lX11 -L $(MLX) -l mlx

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I $(FT)
FT_LNK	= -L ./libft -l ft -l pthread

# vec library
VEC		= ./libvec/
VEC_LIB	= $(addprefix $(VEC),libvec.a)
VEC_INC	= -I ./libvec/inc
VEC_LNK	= -L ./libvec -l vec

# vectors library
VECTOR		= ./libvector/
VECTOR_LIB	= $(addprefix $(VECTOR),libvector.a)
VECTOR_INC	= -I ./libvector/inc
VECTOR_LNK	= -L ./libvector -l vector

all: $(VECTOR_LIB) $(VEC_LIB) $(FT_LIB) $(MLX_LIB) $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJECT_FILES)
	@echo Packing $+ $(VECTOR_LIB) $(VEC_LIB) $(FT_LIB) $(MLX_LIB) ...
	@ar rcT $@ $+ $(VEC_LIB) $(FT_LIB) $(MLX_LIB) $(VECTOR_LIB)
	@ranlib $@
	@echo "Engine lib created succesfully!"

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.c
	@echo Compiling $<...
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) $(VEC_INC) $(VECTOR_INC) -I $(INC) -o $@ -c $<

$(VECTOR_LIB):
	@make -C $(VECTOR)

$(VEC_LIB):
	@make -C $(VEC)

$(FT_LIB):
	@make -C $(FT)

$(MLX_LIB):
	@make -C $(MLX)

clean:
	@echo Removing $(OBJ)...
	@rm -rf $(OBJ)
	@make -C $(VECTOR) clean
	@make -C $(VEC) clean
	@make -C $(FT) clean
	@make -C $(MLX) clean

fclean: clean
	@echo Removing $(LIBRARY_NAME)...
	@rm -rf $(LIBRARY_NAME)
	@make -C $(VECTOR) fclean
	@make -C $(VEC) fclean
	@make -C $(FT) fclean
	@make -C $(MLX) clean

re: fclean all

.PHONY: all fclean

