CC = gcc 
FLAGS = -c -Wall
LIBRARY = -lm

all: command.o game.o game_reader.o graphic_engine.o object.o space.o game_loop.o juego enemy.o set.o clean

command.o: command.c command.h
	$(CC) $(FLAGS) $<
	
enemy.o: enemy.c enemy.h
	$(CC) $(FLAGS) $< $(LIBRARY)
	
game_reader.o: game_reader.c game_reader.h command.h space.h types.h game.h
	$(CC) $(FLAGS) $<

game.o: game.c game.h command.h space.h types.h
	$(CC) $(FLAGS) $<
	
graphic_engine.o: graphic_engine.c graphic_engine.h libscreen.h command.h space.h types.h
	$(CC) $(FLAGS) $< $(LIBRARY)

object.o: object.c object.h types.h
	$(CC) $(FLAGS) $< $(LIBRARY)
	
player.o: player.c player.h
	$(CC) $(FLAGS) $< $(LIBRARY)
	
set.o: set.c set.h
	$(CC) $(FLAGS) $<

space.o: space.c space.h types.h set.h object.h
	$(CC) $(FLAGS) $< $(LIBRARY)

game_loop.o: game_loop.c game.h command.h graphic_engine.h
	$(CC) $(FLAGS) $< 

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

#ENEMY_TEST
enemy_test.o: test/enemy_test.c test/enemy_test.h test/test.h enemy.h
	$(CC) $(FLAGS) $<

enemy_test: enemy_test.o enemy.o 
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

venemy_test: enemy_test
	valgrind --leak-check=full ./enemy_test


#SET_TEST
set_test.o: test/set_test.c test/set_test.h test/test.h set.h
	$(CC) $(FLAGS) $<

set_test: set_test.o set.o 
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vset_test: set_test
	valgrind --leak-check=full ./set_test


#SPACE_TEST
space_test.o: test/space_test.c test/space_test.h test/test.h space.h
	$(CC) $(FLAGS) $<

space_test: space_test.o space.o object.o set.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vspace_test: space_test
	valgrind --leak-check=full ./space_test


#OBJECT_TEST
object_test.o: test/object_test.c test/object_test.h test/test.h object.h
	$(CC) $(FLAGS) $<

object_test: object_test.o space.o object.o set.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vobject_test: object_test
	valgrind --leak-check=full ./object_test

#CLEAN
clean:
	rm -f *.o
	rm -f *.h.gch

xclean:
	rm -f juego
	rm -f space_test
	rm -f set_test
	rm -f enemy_test

sclean: clean xclean

testclean: clean
	rm -f test/*.h.gch
