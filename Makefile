CXX=	c++
CXXFLAGS=	-Wall -Wextra -Werror --std=c++17 -g -fsanitize=address
LDFLAGS= 	-lglfw -lGL

NAME=	scop

SRCS=	test.cpp shader.cpp loadTex.cpp
OBJS=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

test: $(NAME)
	./scop

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean $(NAME)