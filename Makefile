.PHONY: build clean run test

cc = g++
core = src/utils/ByteUtils.cpp src/R6502.cpp src/Memory.cpp src/Debugger.cpp
main = src/main.cpp $(core)

test = test/Test.cpp $(core)

build_dir = ./build
out = $(build_dir)/main
test_out=$(build_dir)/test
opts = -std=c++17

build: $(main)
	mkdir -p $(build_dir)
	$(cc) $(main) -o $(out) $(opts)
	chmod +x $(out)

clean:
	-\rm $(out)
	-\rm $(test_out)
	-\rm -r $(build_dir)

run: $(out)
	$(out)

test: $(test)
	mkdir -p $(build_dir)
	$(cc) $(test) -o $(test_out) $(opts)
	chmod +x $(test_out)
	$(test_out)
