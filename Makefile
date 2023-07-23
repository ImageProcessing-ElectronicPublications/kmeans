PROJECT = kmeans
CXX = g++
CXXFLAGS = -O1 -Isrc
LDFLAGS = -lpthread -lX11
SRCS = src/kmeans.cpp src/kmeans.h src/kimages.cpp src/kimages.h src/main.cpp
RM = rm -f

all: $(PROJECT)

$(PROJECT): $(SRCS)
	$(CXX) $(CXXFLAGS) $^  $(LDFLAGS) -o $@

clean:
	$(RM) $(PROJECT)
