NAME = avm
COMPILER = g++
FLAGS = -Wall -Wextra -Werror -std=c++11

SOURCES = main.cpp AVM_Exception.cpp AbstractVM.cpp  OperandFactory.cpp
INCLUDES = AbstractVM.hpp AVM_Exception.hpp OperandFactory.hpp IOperand.hpp Operand.hpp
OBJECTS = $(addprefix $(D_OBJ), $(SOURCES:.cpp=.o))

D_INCLUDES = ./includes/
D_SRC = ./src/
D_OBJ = ./obj/

all: MKDIR_OBJ $(NAME)

MKDIR_OBJ:
	@mkdir -p $(D_OBJ)

$(NAME): $(OBJECTS)
	@$(COMPILER) $(FLAGS) -o $(NAME) $(OBJECTS)

$(D_OBJ)%.o: $(D_SRC)%.cpp $(addprefix $(D_INCLUDES), $(INCLUDES))
	@$(COMPILER) $(FLAGS) -I $(D_INCLUDES) -c -o $@ $<

clean:
	@rm -rf $(D_OBJ)

fclean:
	@rm -rf $(D_OBJ)
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all