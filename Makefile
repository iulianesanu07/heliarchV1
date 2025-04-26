# === VARIABLES ===
CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude -I/opt/homebrew/include
LDFLAGS  = -L/opt/homebrew/lib -framework OpenGL -lglfw
BUILD_DIR = build
OBJ_DIR   = obj
SRC_DIR   = src

# === FICHIERS ===
# Prend tous les .cpp et .c du dossier src/
SRCS_CPP = $(wildcard $(SRC_DIR)/*.cpp)
SRCS_C   = $(wildcard $(SRC_DIR)/*.c)
SRCS     = $(SRCS_CPP) $(SRCS_C)

# Génère les .o correspondants dans obj/
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_CPP)) \
       $(patsubst $(SRC_DIR)/%.c,   $(OBJ_DIR)/%.o, $(SRCS_C))

TARGET = $(BUILD_DIR)/heliarch_v1

# === REGLES ===
.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile .cpp en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

