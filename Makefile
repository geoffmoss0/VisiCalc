cursor: cursor.o layout.o functions.o data.o
	gcc -o cursor cursor.o layout.o functions.o data.o -lncurses 

layout.o: layout.c functions.c
	gcc -c layout.c -lncurses

functions.o: functions.c functions.h
	gcc -c functions.c 

cursor.o: layout.c functions.c cursor.c cursor.h
	gcc -c cursor.c -lncurses

data.o: data.h data.c
	gcc -c data.c -lncurses

clean:
	rm *.o
