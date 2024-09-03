# Vars
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./player -I./roulette -pthread

# Directories
SRCDIR_PLAYER = player
SRCDIR_ROULETTE = roulette
OBJDIR = obj
BINDIR = bin

# Source and object files
SRC_MAIN = main.cpp
SRC_PLAYER = $(SRCDIR_PLAYER)/betNote.cpp $(SRCDIR_PLAYER)/player.cpp
SRC_ROULETTE = $(SRCDIR_ROULETTE)/roulette.cpp

OBJ_MAIN = $(OBJDIR)/main.o
OBJ_PLAYER = $(OBJDIR)/betNote.o $(OBJDIR)/player.o
OBJ_ROULETTE = $(OBJDIR)/roulette.o

# Binary file
TARGET = $(BINDIR)/roulette_game

# Building rules
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ_MAIN) $(OBJ_PLAYER) $(OBJ_ROULETTE)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build the object files
$(OBJDIR)/%.o: $(SRCDIR_PLAYER)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_ROULETTE)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: $(SRC_MAIN)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean generated files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
