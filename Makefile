
CC = gcc 
FLAGS = -c -Wall
LIBRARY = -lm

all: command.o game.o game_reader.o graphic_engine.o object.o space.o game_loop.o juego enemy.o set.o

command.o: command.c command.h
	$(CC) $(FLAGS) $^
	
enemy.o: enemy.c enemy.h
	$(CC) $(FLAGS) $^ $(LIBRARY)
	
game_reader.o: game_reader.c game_reader.h command.h space.h types.h game.h
	$(CC) $(FLAGS) $^

game.o: game.c game.h command.h space.h types.h
	$(CC) $(FLAGS) $^
	
graphic_engine.o: graphic_engine.c graphic_engine.h libscreen.h command.h space.h types.h
	$(CC) $(FLAGS) $^ $(LIBRARY)

object.o: object.c object.h types.h
	$(CC) $(FLAGS) $^ $(LIBRARY)
	
player.o: player.c player.h
	$(CC) $(FLAGS) $^ $(LIBRARY)
	
set.o: set.c set.h
	$(CC) $(FLAGS) $^

space.o: space.c space.h types.h set.h object.h
	$(CC) $(FLAGS) $^ $(LIBRARY)

game_loop.o: game_loop.c game.h command.h graphic_engine.h
	$(CC) $(FLAGS) $^ 

juego: command.o game.o game_reader.o graphic_engine.o object.o player.o space.o game_loop.o libscreen.a enemy.o set.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

#GAME
run:
	@echo ">>>>>>Running main"
	./juego hormiguero.dat

runv:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./juego hormiguero.dat

juego_permisos: juego
	chmod u+x ./juego

#SET_TEST
SET_TEST: set_test.o set_test
	$(CC) $(FLAGS) set_test.c set_test.h set.h test.h
	$(CC) -o set_test -Wall set_test.o set.o
	valgrind --leak-check=full ./set_test

set_test.o: set_test.c set.h
	$(CC) $(FLAGS) $^

set_test: set_test.o set.o 
	$(CC) -o $@ -Wall $^
	
#SET_TEST2
SET_TEST2: set_test2.o set_test
	$(CC) $(FLAGS) set_test2.c set.h
	$(CC) -o set_test2 -Wall set_test2.o set.o
	valgrind --leak-check=full ./set_test2

set_test2.o: set_test2.c set.h
	$(CC) $(FLAGS) $^

set_test2: set_test2.o set.o 
	$(CC) -o $@ -Wall $^

#SPACE_TEST
SPACE_TEST: space_test.o space_test
	$(CC) $(FLAGS) space_test.c space_test.h space.h test.h
	$(CC) -o space_test -Wall space_test.o space.o object.o set.o $(LIBRARY)
	valgrind --leak-check=full ./space_test

space_test.o: space_test.c space_test.h space.h test.h
	$(CC) $(FLAGS) $^

space_test: space_test.o space.o object.o set.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

#CLEAN
clean:
	rm -f *.o
	rm -f *.h.gch
