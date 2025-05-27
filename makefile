main.exe: main.o admin.o client.o storage.o user.o vehicle.o booking.o hash.o list.o timeutils.o
	gcc main.o admin.o client.o storage.o user.o vehicle.o booking.o hash.o list.o timeutils.o -o main.exe

run_test_suite.exe: run_test_suite.o admin.o client.o storage.o user.o vehicle.o booking.o hash.o list.o timeutils.o
	gcc run_test_suite.o admin.o client.o storage.o user.o vehicle.o booking.o hash.o list.o timeutils.o -o run_test_suite.exe
	./run_test_suite.exe

main.o: main.c admin.h client.h storage.h
	gcc -c main.c

admin.o: admin.c admin.h vehicle.h user.h booking.h hash.h list.h
	gcc -c admin.c

client.o: client.c client.h vehicle.h user.h booking.h hash.h list.h timeutils.h
	gcc -c client.c

storage.o: storage.c storage.h vehicle.h user.h booking.h hash.h list.h
	gcc -c storage.c

user.o: user.c user.h hash.h
	gcc -c user.c

vehicle.o: vehicle.c vehicle.h hash.h list.h booking.h
	gcc -c vehicle.c

booking.o: booking.c booking.h vehicle.h list.h hash.h timeutils.h
	gcc -c booking.c

hash.o: hash.c hash.h
	gcc -c hash.c

list.o: list.c list.h
	gcc -c list.c

timeutils.o: timeutils.c timeutils.h
	gcc -c timeutils.c

run_test_suite.o: run_test_suite.c booking.h vehicle.h user.h storage.h hash.h list.h timeutils.h
	gcc -c run_test_suite.c

clean:
	del /Q *.o main.exe run_test_suite.exe result.txt TestCase*_output.txt 2>nul || exit 0
