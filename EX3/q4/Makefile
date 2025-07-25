CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: server client

server: server.cpp server.hpp
	$(CXX) $(CXXFLAGS) server.cpp -o server

client: client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client

clean:
	rm -f server client
