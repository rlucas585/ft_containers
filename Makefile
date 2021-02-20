# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 14:22:41 by rlucas        #+#    #+#                  #
#    Updated: 2021/02/20 14:05:02 by rlucas        ########   odam.nl          #
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
HEADEREXT = .hpp

SRCLST = main \
	  utils \
	  vector_tests \
	  list_tests

HEADERSLST = vector \
		  sfinae \
		  list \
		  list_iterator \
		  random_access_iterator \
		  colors \
		  utils \
		  test

TESTHEADERSLST = Example \
				 test_fixture_classes \
				 test

TESTSRCLST = main \
			 vector \
			 Example \
			 test \
			 list

TESTOBJDIR = testobj/
TESTDIR = tests/
TESTLIBS = -lgtest -lpthread

# Configuration above, logic below

SRC = $(addprefix $(SRCDIR)/, $(addsuffix $(EXT), $(SRCLST)))
TESTSRC = $(addprefix $(TESTDIR)/, $(addsuffix $(EXT), $(TESTSRCLST)))
HEADERS = $(addprefix $(SRCDIR)/, $(addsuffix $(HEADEREXT), $(HEADERSLST)))
TESTHEADERS = $(addprefix $(TESTDIR)/, $(addsuffix $(HEADEREXT), $(TESTHEADERSLST)))

FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
# FLAGS = -Wall -Wextra -Werror -std=c++11 -pedantic

OBJ := $(addprefix $(OBJDIR), $(SRCLST:%=%.o))
TESTOBJ := $(addprefix $(TESTOBJDIR), $(TESTSRCLST:%=%.o))

all: $(NAME)

test: $(NAME) $(TESTOBJ)
	@echo "Compiling test executable..."
	@$(CC) $(FLAGS) $(TESTOBJ) -o $(TESTNAME) $(INCLUDES) $(TESTLIBS)

$(NAME): $(OBJ)
	@echo "Compiling executable..."
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(INCLUDES)

$(OBJ):	$(SRC) $(HEADERS)
	@mkdir -p $(OBJDIR)
	@echo "Compiling $@"
	@$(CC) -c $(FLAGS) -o $@ $(patsubst $(OBJDIR)%.o,$(SRCDIR)%.cpp, $@) $(INCLUDES)

$(TESTOBJ): $(TESTSRC) $(TESTHEADERS)
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
