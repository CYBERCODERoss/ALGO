CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = social_network
SRCS = main.cpp
HEADERS = social_network.hpp

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET) 