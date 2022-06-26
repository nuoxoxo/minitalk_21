CC		=	cc
RM		=	/bin/rm -f
FLAGS		=	-Wall -Werror -Wextra -fsanitize=address

P		=	./ft_printf/
U		=	./ft_utils/

PRINTF_FLE	=	ft_printf.c route_cs.c route_id.c route_p.c route_u.c route_x.c
PRINTF_SRC	=	$(addprefix $(P), $(PRINTF_FLE))
PRINTF_BUD	=	$(PRINTF_SRC:.c=.o)

UTILS_FLE	=	ft_atoi.c ft_strlen.c ft_putchar.c
UTILS_SRC	=	$(addprefix $(U), $(UTILS_FLE))
UTILS_BUD	=	$(UTILS_SRC:.c=.o)

EXE_SRC		=	client.c server.c
EXE_BUD		=	$(EXE_SRC:.c=.o)

SERVER		=	server
CLIENT		=	client
NAME		=	$(SERVER) $(CLIENT)

%.o		: 	%.c
		$(CC) $(FG) -c $< -o $@

all		:	${NAME}

${SERVER}	: 	${EXE_BUD} ${PRINTF_BUD} ${UTILS_BUD}
		$(CC) $(FG) $(PRINTF_BUD) $(UTILS_BUD) server.o -o ${SERVER}
		@echo "$(MS)$(R) server built successfully $(R)"	

${CLIENT}	: 	${EXE_BUD} ${PRINTF_BUD} ${UTILS_BUD}
		$(CC) $(FG) $(PRINTF_BUD) $(UTILS_BUD) client.o -o ${CLIENT}
		@echo "$(MS)$(R) client built successfully $(R)"

clean	:	
		$(RM) $(EXE_BUD) $(PRINTF_BUD) $(UTILS_BUD) 
		@echo "$(MI)$(R) all object files cleaned $(R)"

fclean	:	clean
		$(RM) $(NAME)
		@echo "$(MI)$(R) all executables and object files cleaned $(R)"

re	:	fclean all

bonus	:	all

.PHONY	:	all clean fclean re

G	=	\e[92m
Y	=	\e[36m
R	=	\e[0;0m
MS	=	[$(G)Success$(G)]
MI	=	[$(Y)Message$(Y)]
