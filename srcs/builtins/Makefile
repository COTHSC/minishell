NAME = builtin_selector 

SRCS = env/env.c \
	   echo/echo.c \
	   cd/cd.c \
	   pwd/pwd.c \
	   export/export.c\
	   unset/unset.c \
	   exit/exit.c \
	   builtin_selector.c

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Linux)
        CC=clang-9
    endif
    ifeq ($(UNAME_S),Darwin)
        CC= clang
    endif

CFLAGS = -Wall -Wextra -Werror

GFLAG = -g3 -fsanitize=address

LIBS = -L./../../libs/libft -lft -L./../../libs/libft+ -lftp -lreadline

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

debug :
	$(CC) $(CFLAGS) $(GFLAG) -o $(NAME) $(SRCS) $(LIBS)

clean :
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
