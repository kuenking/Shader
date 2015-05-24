BIN=game
DBINDIR=.
BINDIR=../target
DSOURSEDIR=.
SOURSEDIR=../source
DCOMARG=-g -Wall -D DSHADER -std=c99
COMARG=-O -Wall -std=c99
$(BINDIR)/$(BIN):main.o \
	connection.o \
	ai.o
	gcc main.o connection.o ai.o -o $(BINDIR)/$(BIN) $(COMARG)
connection.o:$(SOURSEDIR)/connection.c \
	$(SOURSEDIR)/connection.h \
	$(SOURSEDIR)/my_types.h \
	$(SOURSEDIR)/error_code.h
	gcc -c $(SOURSEDIR)/connection.c $(COMARG)
main.o:$(SOURSEDIR)/main.c \
	$(SOURSEDIR)/error_code.h \
	$(SOURSEDIR)/connection.h
	gcc -c $(SOURSEDIR)/main.c $(COMARG)
ai.o:$(SOURSEDIR)/ai.c \
	$(SOURSEDIR)/my_types.h \
	$(SOURSEDIR)/error_code.h
	gcc -c $(SOURSEDIR)/ai.c $(COMARG)
debug:$(DSOURSEDIR)/main.c \
	$(DSOURSEDIR)/connection.c \
	$(DSOURSEDIR)/connection.h \
	$(DSOURSEDIR)/error_code.h \
	$(DSOURSEDIR)/debug_shader.h \
	$(DSOURSEDIR)/my_types.h \
	$(DSOURSEDIR)/ai.c \
	$(DSOURSEDIR)/ai.h
	gcc -o $(DBINDIR)/$(BIN) $(DSOURSEDIR)/main.c $(DSOURSEDIR)/ai.c  $(DSOURSEDIR)/connection.c $(DCOMARG)
clean:
	rm $(BINDIR)/$(BIN)
	rm *.o
dclean:
	rm $(DBINDIR)/$(BIN)
