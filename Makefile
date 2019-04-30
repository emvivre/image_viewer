CFLAGS = -Wall -Wno-unused-value -Wno-comment -Werror -Wextra -g -std=c++11
LDFLAGS = -lpthread -lgd -lSDL -ltiff

all: image_viewer

image_viewer: main.o image.o
	$(CXX) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) -c -o $@ $< $(CFLAGS)

clean:
	@rm -f image_viewer main.o image.o
