
prefixe=p

# exige 3 fichiers:
# - $(prefixe).y (fichier bison)
# - $(prefixe).lex (fichier flex)
# - main.c (programme principal)
# construit un exécutable nommé "main"

# note : le programme principal ne doit surtout pas s'appeler $(prefixe).c
# (make l'écraserait parce qu'il a une règle "%.c: %.y")

LDFLAGS = -g -Werror -Wextra -Wall

all: main

main: $(prefixe).tab.o lex.yy.o main.o tabsymbole.o gencode.o usefull.o SoS2MIPS.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

SoSMIPS.o : SoS2MIPS.c
	gcc -o SoS2MIPS.o -c SoS2MIPS.c $(LDFLAGS)

tabsymbole.o : tabsymbole.c
	gcc -o tabsymbole.o -c tabsymbole.c $(LDFLAGS)

gencode.o : gencode.c
	gcc -o gencode.o -c gencode.c $(LDFLAGS)

usefull.o : usefull.c
	gcc -o usefull.o -c usefull.c $(LDFLAGS)

$(prefixe).tab.c: $(prefixe).y
	bison -t -d $(prefixe).y

lex.yy.c: $(prefixe).lex $(prefixe).tab.h
	flex $(prefixe).lex

doc:
	bison --report=all --report-file=$(prefixe).output \
		--graph=$(prefixe).dot --output=/dev/null \
		$(prefixe).y
	dot -Tpdf < $(prefixe).dot > $(prefixe).pdf

test: 
	./lauch_test

clean:
	rm -f *.o $(prefixe).tab.c $(prefixe).tab.h lex.yy.c main \
		$(prefixe).output $(prefixe).dot $(prefixe).pdf

tar:
	tar -cvf ../TP2_exo3_RIO.tar ./