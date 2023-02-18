build:
	g++ -o tema1 main.cpp mapper.cpp reducer.cpp map_reduce.cpp workpool.cpp -lpthread -lrt -Wall -Werror
clean:
	rm -f ./tema1
