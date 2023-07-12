TARGET = Regex

#directories
HEADERDIR := headers
SOURCEDIR := sources
OBJSDIR := OBJS

#compile definitions
CC = g++

CCFLAGS = -c -Wall -std=c++11 -O2

INCLUDES = -I $(HEADERDIR)

#source file lijst------------------------------------------------------
SOURCES:= $(wildcard $(SOURCEDIR)/*.cc)

#OBJS lijst-------------------------------------------------------------
OBJS := $(addprefix $(OBJSDIR)/,$(notdir $(patsubst %.cc, %.o, $(SOURCES))))

#DEPS lijst-------------------------------------------------------------
DEPS := $(patsubst %.o, %.d, $(OBJS))

#make opties------------------------------------------------------------
.PHONY: all clean debug release
release: CCFLAGS += -O3 -DNDEBUG
release: all
debug: CCFLAGS += -O0 -DDEBUG -ggdb3
debug: all
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./$(TARGET) 
log:
	git log --all --decorate --oneline --graph
all: $(TARGET)
clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

#Compileren-------------------------------------------------------------
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(OBJSDIR)/%.o: $(SOURCEDIR)/%.cc
	$(CC) $(CCFLAGS) -MMD $< -o $@
# als t niet helemaal soepel werkt, probeer deze hieronder,
# dat is zonder .d file gedoe
# 	$(CC) $(CCFLAGS) $(INCLUDES) $< -o $@
