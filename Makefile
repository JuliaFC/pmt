all: 
	@mkdir -p bin
	@g++ -w -o bin/pmt src/pmt.cpp
	@export PATH=$PATH:/bin

clean:
	@rm -rf bin
	@make all -s