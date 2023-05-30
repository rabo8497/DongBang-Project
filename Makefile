program.exe:	main.o	book.o	bookmanager.o	user.o	userManager.o
	g++	-o	program.exe	main.o	book.o	bookmanager.o	user.o	userManager.o

main.o:	./books/Book.h ./books/BookManager.h ./users/User.h ./users/UserManager.h main.cpp
	g++ -c	-o main.o main.cpp

book.o: ./users/User.h ./books/book.h ./books/book.cpp
	g++ -c	-o book.o	./books/book.cpp

bookmanager.o: FileHandler.h ./users/User.h ./books/book.h	./books/bookmanager.h ./books/bookmanager.cpp
	g++ -c	-o	bookmanager.o	./books/bookmanager.cpp

user.o: ./books/book.h ./users/user.h ./users/user.cpp
	g++	-c	-o	user.o	./users/user.cpp

userManager.o: FileHandler.h ./users/User.h ./users/userManager.h ./users/userManager.cpp
	g++	-c	-o	userManager.o	./users/userManager.cpp

clean:
	rm -rf *.o *.exe