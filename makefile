CXX := clang++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror

SRCDIR := src
INCDIR := include

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, %.o, $(SRCS))

EXECUTABLE := traffic_simulator

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
