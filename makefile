Options := -g -Wall
Headers := src/linklist.h src/note.h src/com.h

all: 
	gcc ${Options} src/main.c -c -o build/main.o
	gcc ${Options} src/linklist.c -c -o build/linklist.o
	gcc ${Options} src/com.c -c -o build/com.o
	gcc ${Options} src/note.c -c -o build/note.o
	gcc ${Options} src/task.c -c -o build/task.o

	gcc ${Headers} build/*.o -o ./notes

run:
	if [ -e notes ]; then ./notes ;fi

clean:
	for i in build/*.o; do rm "$$i"; done
	if [ -e notes ]; then rm notes ;fi