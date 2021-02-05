make: main.o execution.o commands.o
  gcc -o make main.o execution.o commands.o

main.o: main.c header.h
	gcc -c main.c

commands.o: commands.c header.h
	gcc -c commands.c

execution.o: execution.c header.h
  gcc -c execution.c

clean:
	rm main.o commands.o execution.o make
