CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I./common -I./server
LDFLAGS := -lzmq

SERVER_OUT := bin/server
CLIENT_OUT := bin/client
BIN_DIR := bin

SERVER_SRCS := server/server.cpp server/student_utils.cpp
CLIENT_SRCS := client/client.cpp 

all: prepare $(SERVER_OUT) $(CLIENT_OUT)

prepare:
	mkdir -p $(BIN_DIR)

$(SERVER_OUT): $(SERVER_SRCS) common/student.h server/student_utils.h
	$(CXX) $(CXXFLAGS) $(SERVER_SRCS) -o $@ $(LDFLAGS)

$(CLIENT_OUT): $(CLIENT_SRCS) common/student.h common/zmq_utils.h
	$(CXX) $(CXXFLAGS) $(CLIENT_SRCS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(BIN_DIR)

deploy_data:
	cp server/student_file_1.txt $(BIN_DIR)/
	cp server/student_file_2.txt $(BIN_DIR)/

all: prepare deploy_data $(SERVER_OUT) $(CLIENT_OUT)

.PHONY: all clean prepare deploy_data
