CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

# קובצי מקור
SERVER_SRCS = server.cpp reactor.cpp
CLIENT_SRCS = client.cpp

# קובצי פלט
SERVER_BIN = server
CLIENT_BIN = client

# מטרות ברירת מחדל
all: $(SERVER_BIN) $(CLIENT_BIN)

# קומפילציה של השרת
$(SERVER_BIN): $(SERVER_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# קומפילציה של הלקוח
$(CLIENT_BIN): $(CLIENT_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ניקוי
clean:
	rm -f *.o $(SERVER_BIN) $(CLIENT_BIN)
