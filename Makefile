Warnings = -Wall -Werror -Wextra

all : bigint

bigint: obj/bigint.o obj/BigInt.o
	g++ -std=c++17 $(Warnings) obj/bigint.o obj/BigInt.o -o bigint

obj/bigint.o: src/main.cpp include/test_runner.h include/BigInt.h | obj
	g++ -c -std=c++17 $(Warnings) -Iinclude src/main.cpp -o obj/bigint.o

obj/BigInt.o: src/BigInt.cpp include/BigInt.h | obj
	g++ -c -std=c++17 $(Warnings) -Iinclude src/BigInt.cpp -o obj/BigInt.o

obj:
	mkdir obj

clean:
	rm -rf bigint obj