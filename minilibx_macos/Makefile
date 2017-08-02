#
#

PROJECT			=	LIBMLX
NOM				=	libmlx.a
SRC				=	mlx_shaders.c \
					mlx_new_window.m \
					mlx_init_loop.m \
					mlx_new_image.m \
					mlx_xpm.c \
					mlx_int_str_to_wordtab.c
OBJ1			=	$(SRC:.c=.o)
OBJ				=	$(OBJ1:.m=.o)
CFLAGS			+=	-O2
CC				= gcc 

all: $(NOM)

$(NOM):	$(OBJ)
	@printf "[$(PROJECT)] Bin compilation done.                                           \n"
	@ar rc $(NOM) $(OBJ)
	@ranlib $(NOM)
	@printf "[$(PROJECT)] $(NOM) compiled.                                                \n"

%.o: %.c
	@printf "[$(PROJECT)] Compiling $< to $@                                              \r"
	@$(CC) -o $@ -c $<

%.o: %.m
	@printf "[$(PROJECT)] Compiling $< to $@                                              \r"
	@$(CC) -o $@ -c $<

clean:
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app
	@printf "[$(PROJECT)] Obj removed.                                                    \n"
