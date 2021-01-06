# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 14:22:41 by rlucas        #+#    #+#                  #
#    Updated: 2021/01/06 16:38:22 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers

ifeq ($(shell uname), Linux)
	CC = g++
else
	CC = clang++
endif

SRCDIR = src/
OBJDIR = obj/
INCLUDES = -Isrc/
EXT = .cpp

SRCLST = main \
	  utils

# Configuration above, logic below

SRC = $(addprefix $(SRCDIR)/, $(addsuffix $(EXT), $(SRCLST)))

FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

OBJ := $(addprefix $(OBJDIR), $(SRCLST:%=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling executable..."
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(INCLUDES)

$(OBJ):	$(SRC)
	@mkdir -p $(OBJDIR)
	@echo "Compiling $@"
	@$(CC) -c $(FLAGS) -o $@ $(patsubst $(OBJDIR)%.o,$(SRCDIR)%.cpp, $@) $(INCLUDES)

clean:
	@echo "Removing objects..."
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Deleting executable..."
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
