##########################################
#           Editable options             #
##########################################

# Compiler options
CC=cc
CFLAGS= -MMD -MP -Wall -Wextra -Werror -Ofast -fPIE
LDFLAGS=
BINARY_NAME=
LIBRARY_NAME=libvector.a

# Folders
SRC=src
INC=inc
BIN=bin
OBJ=obj

# Files
SOURCE_NAME= utils.c \
			 manager.c \
			 methods.c \
			 method_choice.c \
			 size_modifiers.c \
			 iterations.c \
			 getter.c \
			 adder.c \
			 remover.c

##########################################
#    Don't touch anything below this     #
##########################################
SOURCE_FILES     = $(SOURCE_NAME:%.c=$(SRC)/%.c)
BINARY_FILES     = $(BINARY_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SOURCE_NAME:%.c=$(OBJ)/%.o)

build: obj $(LIBRARY_NAME)

clean:
	@echo Removing $(OBJ)...
	@rm -r -f $(OBJ)
	@rm -rf .print_rule

fclean: clean
	@echo Removing $(LIBRARY_NAME)...
	@rm -r -f $(LIBRARY_NAME)

re: fclean build

.PHONY: build fclean

obj:
	@rm -rf .print_rule
	@mkdir -p $(OBJ)

$(LIBRARY_NAME): $(OBJECT_FILES)
	@echo "\e[1;35mPacking...\e[0m"
	@ar -crs $@ $+
	@echo "\e[1;32m➤" $@ "created succesfully !\e[0m"

.print_rule:
	@> $@
	@echo "\e[1;36mCompiling...\e[0m"

$(OBJ)/%.o: $(SRC)/%.c .print_rule
	@echo "\e[0;36m ↳\e[0;36m" $< "\e[0m"
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -I $(INC) -c -o $@ $<

