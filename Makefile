default: librunt_cairo.a rntcairo
CFLAGS += -ansi -Wall -pedantic -g -fPIC -I$(HOME)/.runt/include
LIBS += -lrunt -lcairo -ldl -L$(HOME)/.runt/lib
CONFIG?=

include $(CONFIG)

OBJ = cairo.o

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

librunt_cairo.a: $(OBJ)
	ar rcs $@ $(OBJ)

rntcairo: parse.c librunt_cairo.a
	$(CC) $(CFLAGS) $< -o $@ $(LIBS) librunt_cairo.a

install: rntcairo librunt_cairo.a
	mkdir -p ~/.runt/bin
	mkdir -p ~/.runt/lib
	install rntcairo ~/.runt/bin
	install librunt_cairo.a ~/.runt/lib

clean:
	rm -rf fill librunt_cairo.a $(OBJ) rntcairo *.png
