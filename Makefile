CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror
# básico: -std=c++20 -g -Wall

# pastas
BIN_FOLDER = bin
INC_FOLDER = include
OBJ_FOLDER = obj
SRC_FOLDER = src

TARGET = tp3
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)/%.cpp, $(OBJ_FOLDER)/%.o, $(SRC))

# processo de compilação
$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(INC_FOLDER)/

# criar diretórios, usando o comando mkdir do Windows
$(shell if not exist "$(BIN_FOLDER)/" mkdir "$(BIN_FOLDER)/")
$(shell if not exist "$(OBJ_FOLDER)/" mkdir "$(OBJ_FOLDER)/")

all: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_FOLDER)/$(TARGET) $(OBJ)

clean:
	@del /Q $(OBJ_FOLDER)\*.o
	@del /Q $(BIN_FOLDER)\*.exe

run_only:
	./$(BIN_FOLDER)/$(TARGET)

run_with_input:
	PowerShell -Command "Get-Content input.txt | ./bin/main.exe"
	
run: clean all
	@$(BIN_FOLDER)/$(TARGET)
