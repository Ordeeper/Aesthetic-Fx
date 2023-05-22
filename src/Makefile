CC ?= gcc
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
CFLAGS = `pkg-config --cflags MagickWand`
LDFLAGS = `pkg-config --libs MagickWand`

all: install

install-dependencies:
	@echo "Installing ImageMagick dependencies..."
	@if command -v apt &> /dev/null; then \
		sudo apt install imagemagick -y; \
	elif command -v dnf &> /dev/null; then \
		sudo dnf install imagemagick -y; \
	elif command -v yay &> /dev/null; then \
		yay -S imagemagick --noconfirm --needed; \
	elif command -v pacman &> /dev/null; then \
		sudo pacman -S imagemagick --noconfirm --needed; \
	else \
		echo "Unsupported package manager. Please install ImageMagick dependencies manually."; \
		exit -1; \
	fi

install: image_processing.c error_handling.c | install-dependencies
	$(CC) $(CFLAGS) $(LDFLAGS) -c image_processing.c -o image_processing.o
	$(CC) $(CFLAGS) $(LDFLAGS) -c error_handling.c -o error_handling.o
	$(CC) $(CFLAGS) $(LDFLAGS) -c argparse.c -o argparse.o
	$(CC) $(CFLAGS) $(LDFLAGS) image_processing.o error_handling.o argparse.o -o $(BINDIR)/aestheticfx

clean:
	rm -f image_processing.o error_handling.o

uninstall:
	rm -f $(BINDIR)/aestheticfx

.PHONY: all install clean uninstall