CC=g++
C_FLAGS=-g -std=c++17 -Wall

SRC_FILES=$(filter-out $(wildcard main.cpp),$(wildcard *.pp))
APP=chess

custom_tests:
	$(CC) $(C_FLAGS) poly.cpp main.cpp -o pol

valgrind:
	valgrind --leak-check=full ./$(APP) $(TEST)

