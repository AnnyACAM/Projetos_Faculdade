# Variáveis
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17
LDFLAGS = 

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

# Arquivos
SOURCES = $(SRC_DIR)/game.cpp $(SRC_DIR)/piece.cpp $(SRC_DIR)/tabletop.cpp $(SRC_DIR)/game_controller.cpp $(SRC_DIR)/main.cpp $(SRC_DIR)/lig4_game.cpp $(SRC_DIR)/lines_of_action.cpp $(SRC_DIR)/tic_tac_toe.cpp $(SRC_DIR)/player.cpp 
HEADERS = $(wildcard include/*.hpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/main.exe

# Regras principais
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Limpeza
clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) $(EXECUTABLE)

# Ajuda
.PHONY: all clean
