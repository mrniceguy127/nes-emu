.PHONY: build clean run

cc = g++
main = src/main.cpp src/R6502.cpp src/Memory.cpp

build_dir = ./build
out = $(build_dir)/main

build: $(main)
	mkdir -p $(build_dir)
	$(cc) $(main) -o $(out)
	chmod +x $(out)

clean:
	-\rm $(out)
	-\rm -r $(build_dir)

run: $(out)
	$(out)

