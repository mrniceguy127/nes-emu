.PHONY: build clean run

cc = g++
main = src/main.cpp src/R6502.cpp src/Memory.cpp src/Debugger.cpp

test = test/Test.cpp src/R6502.cpp src/Memory.cpp src/Debugger.cpp

build_dir = ./build
out = $(build_dir)/main
test_out=$(build_dir)/test

build: $(main)
	mkdir -p $(build_dir)
	$(cc) $(main) -o $(out)
	chmod +x $(out)

clean:
	-\rm $(out)
	-\rm $(test_out)
	-\rm -r $(build_dir)

run: $(out)
	$(out)

test: $(test)
	mkdir -p $(build_dir)
	$(cc) $(test) -o $(test_out)
	chmod +x $(test_out)
	$(test_out)
