NAME		=	ft_ssl

SRCDIR		=	./src/
UTLDIR		=	$(SRCDIR)util/
RSADIR		=	$(SRCDIR)rsa/
CRYPTDIR	=	$(SRCDIR)encrypt/
PROCDIR		=	$(SRCDIR)process/
BINDIR		=	./bin/
INCLUDEDIR	=	./include/

SRCFILES	=	ft_ssl.c			\
				cmd.c				\
				process_util.c		\
				process_genrsa.c	\
				process_rsautl.c	\
				process_rsa.c		\
				key_util.c			\
				gen_prime.c			\
				gen_priv_exp.c		\
				gen_priv_key.c		\
				encoding.c			\
				encrypt.c			\
				encrypt_util.c		\
				byte_array.c		\
				base64.c			\
				uint128.c			\
				base16.c			\
				error.c				\
				file.c				\
				math.c				\
				print.c				\
				string.c			\
				random.c			\

BINFILES	=	$(notdir $(SRCFILES:.c=.o))

SRCS		=	$(addprefix $(SRCDIR), $(SRCFILES))
BINS		=	$(addprefix $(BINDIR), $(BINFILES))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
POSTFLAGS	=	-lm
RM			=	rm -rf

all:		$(NAME)

$(NAME):	$(BINS)
			@$(CC) $(CFLAGS) $(BINS) -o $(NAME) $(POSTFLAGS)
			@echo "compiling $(NAME)"

$(BINDIR)%.o:	$(SRCDIR)%.c
			@mkdir -p $(BINDIR)
			@$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@
			@echo "compiling $<"

$(BINDIR)%.o:	$(UTLDIR)%.c
			@mkdir -p $(BINDIR)
			@$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@
			@echo "compiling $<"

$(BINDIR)%.o:	$(RSADIR)%.c
			@mkdir -p $(BINDIR)
			@$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@
			@echo "compiling $<"

$(BINDIR)%.o:	$(CRYPTDIR)%.c
			@mkdir -p $(BINDIR)
			@$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@
			@echo "compiling $<"

$(BINDIR)%.o:	$(PROCDIR)%.c
			@mkdir -p $(BINDIR)
			@$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@
			@echo "compiling $<"

clean:
			@$(RM) $(NAME)

fclean:		clean
			@$(RM) $(BINDIR)

re:		fclean all

.PHONY:		all clean fclean re
