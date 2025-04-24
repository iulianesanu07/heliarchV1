# Variables
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -framework OpenGL -lGLEW -lglfw
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
PLIST = Info.plist

# Trouve tous les fichiers sources
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET = $(BUILD_DIR)/heliarch_v1

# Règle principale
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJECTS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS) -Wl,-sectcreate,__TEXT,__info_plist,$(PLIST)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all clean
