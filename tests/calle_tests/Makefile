NAME = test 

SRCS = ./declare_var.c\
       ../../srcs/utils/split_var_by_name_value_pair.c\
       ../../libs/libft/ft_calloc.c \
       ../../libs/libft/ft_putstr_fd.c \
       ../../libs/libft/ft_putchar_fd.c

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Linux)
        CC=clang
    endif
    ifeq ($(UNAME_S),Darwin)
        CC= clang
    endif

CFLAGS = -Wall -Wextra -Werror

GFLAG = -g3 -fsanitize=address

INCLUDES= -I includes/

DIR_LFT=../../libs/libft/ 

DIR_LFTP=../../libs/libft+/

LFT=../../libs/libft/libft.a 

LFTP=../../libs/libft+/libft+.a

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(DIR_LFT)
	$(MAKE) -C $(DIR_LFTP)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT) $(LFTP) -lreadline

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(INCLUDES)

debug :
	$(MAKE) -C $(DIR_LFT) debug
	$(MAKE) -C $(DIR_LFTP) debug
	$(CC) $(CFLAGS) $(GFLAG) -o $(NAME) $(SRCS) $(LFT) $(LFTP) -lreadline

debug_lldb :
	$(MAKE) -C $(DIR_LFT) debug_lldb
	$(MAKE) -C $(DIR_LFTP) debug_lldb
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) $(LFT) $(LFTP) -lreadline

clean :
	rm -f $(OBJS)
	$(MAKE) -C $(DIR_LFT) clean
	$(MAKE) -C $(DIR_LFTP) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(DIR_LFT) fclean
	$(MAKE) -C $(DIR_LFTP) fclean

re: fclean all
