# Compila programas do curso de OpenGL no ambiente Linux
# Substitua nome_do_programa pelo nome do programa ...
# ...que se está trabalhando
#
# Antes das linhas que contém "gcc...", não pode haver espaço em
# branco e sim uma marca de tabulação
#
# CESET, 2005, Prof. Marco Antonio
#

# Variables
LIBS	=	-lglut -lGL -lGLU
CFLAGS	=	$(INCPATH)	-g
LFLAGS	=	$(LIBPATH) $(LIBS)

# Main targets
main: main.o
	g++ -o main main.o $(LFLAGS)

# Source targets
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)
