CC = g++

CFLAGS = -std=c++17 -Wall -Wextra -pedantic

SERVER_SOURCES = server_run.cpp Timer.cpp Server.cpp EChoice.cpp
CLIENT_SOURCES = client_run.cpp Client.cpp EChoice.cpp

SERVER_EXECUTABLE = server
CLIENT_EXECUTABLE = client

all: server client

server: $(SERVER_SOURCES)
	$(CC) $(CFLAGS) -o $(SERVER_EXECUTABLE) $(SERVER_SOURCES)

client: $(CLIENT_SOURCES)
	$(CC) $(CFLAGS) -o $(CLIENT_EXECUTABLE) $(CLIENT_SOURCES)

clean:
	rm -f $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE)

.PHONY: all server client clean
