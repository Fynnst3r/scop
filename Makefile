CXX=	c++
CXXFLAGS=	-Wall -Wextra -Werror --std=c++17
LDFLAGS= 	-lglfw -lGL

NAME=	scop

SRCS=	test.cpp
OBJS=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean $(NAME)