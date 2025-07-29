CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

# קבצים להרכבת השרת
SERVER_SRCS = server.cpp template.cpp
SERVER_OBJS = $(SERVER_SRCS:.cpp=.o)
SERVER_BIN = server

# קובץ הלקוח
CLIENT_SRCS = client.cpp
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)
CLIENT_BIN = client

all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(CLIENT_BIN): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(SERVER_BIN) $(CLIENT_BIN)
