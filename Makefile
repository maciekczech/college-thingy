CXX = g++
CXXFLAGS = -g
CXXFLAGS += -Wall
CXXFLAGS += -std=c++11
NAME = Projekt1

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

DEPFLAGS = -MMD
DEPFLAGS += -MP

CXXFLAGS += $(DEPFLAGS)
CXXFLAGS += -lsfml-graphics
CXXFLAGS += -lsfml-window
CXXFLAGS += -lsfml-system
CXXFLAGS += -lm

all : $(NAME)
	

$(NAME) : $(OBJ)
	$(CXX) $(GXXFLAGS) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean :
	rm $(OBJ) $(DEP) $(NAME) 

run : $(NAME)
	./$(NAME)

.PHONY: clear run


 -include $(DEP)
