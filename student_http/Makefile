CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Icommon

SRC_DIR = src
COMMON_DIR = common
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj

SERVER_SRC = $(SRC_DIR)/server.cpp $(SRC_DIR)/student.cpp
CLIENT_SRC = $(SRC_DIR)/client.cpp $(SRC_DIR)/student.cpp

SERVER_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SERVER_SRC))
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CLIENT_SRC))

SERVER_EXE = $(BIN_DIR)/server
CLIENT_EXE = $(BIN_DIR)/client

all: $(SERVER_EXE) $(CLIENT_EXE)

$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

$(SERVER_EXE): $(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread

$(CLIENT_EXE): $(CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

run_server: $(SERVER_EXE)
	./$(SERVER_EXE)

run_client: $(CLIENT_EXE)
	./$(CLIENT_EXE)

.PHONY: all clean run_server run_client