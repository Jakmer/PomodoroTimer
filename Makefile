CC = g++

CFLAGS = -std=c++17 -Wall -Wextra -pedantic

SERVER_SOURCES = Server_run.cpp Timer.cpp Server.cpp Message.cpp Config.cpp
CLIENT_SOURCES = Client_run.cpp Client.cpp Message.cpp Config.cpp

BIN = bin/
SERVER_EXECUTABLE = $(BIN)server
CLIENT_EXECUTABLE = $(BIN)client

all: server client

$(BIN):
	mkdir -p $(BIN)

server: $(BIN) $(SERVER_SOURCES)
	$(CC) $(CFLAGS) -o $(SERVER_EXECUTABLE) $(SERVER_SOURCES)

client: $(BIN) $(CLIENT_SOURCES)
	$(CC) $(CFLAGS) -o $(CLIENT_EXECUTABLE) $(CLIENT_SOURCES)

clean:
	rm -f $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE)

.PHONY: all server client clean