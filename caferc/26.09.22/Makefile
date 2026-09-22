CC = cc
CFLAGS = -static -Wall
TARGET = CafeRC
SRC = cafeRC.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
