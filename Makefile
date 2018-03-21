.PHONY: all clean
CC = gcc
CFLAGS = -std=c89 -lXt -lX11 
PREFIX = $(DESTDIR)/usr/local
TARGET = xvisbell

all: $(TARGET)

$(TARGET):%:%.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	install -D -m 0755 -t $(PREFIX)/bin/ $^

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)
