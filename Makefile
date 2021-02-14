# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 14:22:41 by rlucas        #+#    #+#                  #
#    Updated: 2021/02/14 13:36:30 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
TESTNAME = test

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
	  utils \
	  vector_tests \
	  list_tests \
	  map_tests

TESTSRCLST = main \
			 vector

TESTOBJDIR = testobj/
TESTDIR = tests/
TESTLIBS = -L/mnt/hard_drive/usr/local/lib/ -lgtest -lpthread

# Configuration above, logic below

SRC = $(addprefix $(SRCDIR)/, $(addsuffix $(EXT), $(SRCLST)))
TESTSRC = $(addprefix $(TESTDIR)/, $(addsuffix $(EXT), $(TESTSRCLST)))

FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
# FLAGS = -Wall -Wextra -Werror -std=c++11 -pedantic

OBJ := $(addprefix $(OBJDIR), $(SRCLST:%=%.o))
TESTOBJ := $(addprefix $(TESTOBJDIR), $(TESTSRCLST:%=%.o))

all: $(NAME)

test: $(TESTOBJ)
	@echo "Compiling test executable..."
	@$(CC) $(FLAGS) $(TESTOBJ) -o $(TESTNAME) $(INCLUDES) $(TESTLIBS)

$(NAME): $(OBJ)
	@echo "Compiling executable..."
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(INCLUDES)

$(OBJ):	$(SRC)
	@mkdir -p $(OBJDIR)
	@echo "Compiling $@"
	@$(CC) -c $(FLAGS) -o $@ $(patsubst $(OBJDIR)%.o,$(SRCDIR)%.cpp, $@) $(INCLUDES)

$(TESTOBJ): $(TESTSRC)
	@mkdir -p $(TESTOBJDIR)
	@echo "Compiling $@"
	@$(CC) -c $(FLAGS) -o $@ $(patsubst $(TESTOBJDIR)%.o,$(TESTDIR)%.cpp, $@) $(INCLUDES)

clean:
	@echo "Removing objects..."
	@rm -rf $(OBJDIR)
	@rm -rf $(TESTOBJDIR)

fclean: clean
	@echo "Deleting executable..."
	@rm -f $(NAME)
	@rm -f $(TESTNAME)

re: fclean all

.PHONY: clean fclean all re
