all: computer main
	@g++ ./*.o -o ./main.x

computer: computer.h computer.cpp
	@g++ -c ./computer.cpp -ggdb -o ./computer.o

main: main.cpp
	@g++ -c -ggdb ./main.cpp

run: all
	./main.x