SRCS	=	shellsort.cpp
OBJS	=	$(SRCS:.cpp=.o)

LIBS	=
CC	=	g++
CFLAGS	=	-lm -std=c++11

test_shellsort: $(OBJS) test_shellsort.o
	${CC} $(CFLAGS) $(OBJS) test_shellsort.o $(LIBS) -o test_shellsort

.cpp.o:
	$(CC) $(CFLAGS) -c $<
