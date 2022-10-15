NAME	= pipex
HEADER	= pipex.h
FILES	= ft_utils1.c\
		  ft_utils2.c\
  		  ft_split.c\
  		  gnl.c\
  		  parse_cmd.c\
  		  pipex_fds.c\
  		  pipex.c\

FILES_O	= $(FILES:.c=.o)
SRCS 	= $(addprefix src/, $(FILES))
OBJS 	= $(addprefix obj/, $(FILES_O))
OBJDIR	= obj
CC		= gcc
CFLAGS	= -I. -Wall -Wextra -Werror
RM		= rm -rf

obj/%.o:	src/%.c $(HEADER) 
			@ $(CC) $(CFLAGS) -c $< -o $@

all:		$(OBJDIR) $(NAME)
			@ $(CC) $(FLAGS)  -o $(NAME) $(OBJS) 

$(OBJDIR):		
			@ mkdir $(OBJDIR)

$(NAME):	$(OBJS)

clean:			
			@ $(RM) $(OBJDIR)

fclean:		clean
			@ $(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
