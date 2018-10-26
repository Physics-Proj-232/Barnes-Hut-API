NAME = BHAPI.a

OBJS = foo.o

all: $(NAME)

$(NAME):
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm $(NAME)
