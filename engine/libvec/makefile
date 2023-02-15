##########################################
#           Editable options             #
##########################################

# Compiler options
CC=clang
CFLAGS=-c -Wall -Wextra -Werror
LDFLAGS=
BINARY_NAME=
LIBRARY_NAME=libvec.a

# Folders
SRC=src
INC=inc
BIN=bin
OBJ=obj

# Files
SOURCE_NAME= vec2f_algo.c \
			 vec2i_algo.c \

##########################################
#    Don't touch anything below this     #
##########################################
SOURCE_FILES     = $(SOURCE_NAME:%.c=$(SRC)/%.c)
BINARY_FILES     = $(BINARY_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SOURCE_NAME:%.c=$(OBJ)/%.o)

build: $(LIBRARY_NAME)

clean:
	@echo Removing $(OBJ)...
	@rm -r -f $(OBJ)

fclean: clean
	@echo Removing $(LIBRARY_NAME)...
	@rm -r -f $(LIBRARY_NAME)

re: fclean build

.PHONY: build fclean

$(LIBRARY_NAME): $(OBJECT_FILES)
	@echo Packing $+...
	@ar -crs $@ $+
	@echo "Veclib created succesfully!"

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.c
	@echo Compiling $<...
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -I $(INC) -o $@ $<

