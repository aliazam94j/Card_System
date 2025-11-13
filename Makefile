PROG=main.exe
# CC=gcc
DEPS=
SOURCES=main.c cardfunction.c card.c menu.c safeinput.c
CFLAGS=-Wall -Werror -g
OUTPUTDIR=obj
OBJS = $(addprefix $(OUTPUTDIR)/, $(SOURCES:.c=.o))

all: $(OUTPUTDIR) $(PROG)

$(PROG): $(OBJS) 
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTPUTDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(OUTPUTDIR):
	@mkdir "$(OUTPUTDIR)"

clean:
	@del /q "$(OUTPUTDIR)" 
	@del /q $(PROG)


.PHONY: prep clean