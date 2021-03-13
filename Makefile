# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 14:22:41 by rlucas        #+#    #+#                  #
#    Updated: 2021/03/13 15:30:56 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
TEST = container_tests

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
	  list_tests

TESTSRCLST = main \
			 vector \
			 Example \
			 test \
			 list \
			 map \
			 stack \
			 queue

TESTOBJDIR = testobj/
TESTDIR = tests/
TESTLIBS = -lgtest -lpthread

# Configuration above, logic below

SRC = $(addprefix $(SRCDIR)/, $(addsuffix $(EXT), $(SRCLST)))
TESTSRC = $(addprefix $(TESTDIR)/, $(addsuffix $(EXT), $(TESTSRCLST)))

FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
# FLAGS = -Wall -Wextra -Werror -std=c++11 -pedantic

OBJ := $(addprefix $(OBJDIR), $(SRCLST:%=%.o))
TESTOBJ := $(addprefix $(TESTOBJDIR), $(TESTSRCLST:%=%.o))

all: $(NAME)

test: $(TEST)

$(TEST): $(OBJ) $(TESTOBJ)
	@echo "Compiling test executable..."
	@$(CC) $(FLAGS) $(TESTOBJ) -o $(TEST) $(INCLUDES) $(TESTLIBS)

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
	@rm -f $(TEST)

re: fclean all

.PHONY: clean fclean all re
