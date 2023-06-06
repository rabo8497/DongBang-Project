program.exe:	main.o	book.o	bookManager.o	user.o	userManager.o account.o calendar.o device.o item.o itemManager.o comment.o
	g++ -o ../program.exe	main.o	book.o	bookManager.o	user.o	userManager.o	account.o calendar.o device.o item.o itemManager.o comment.o

main.o:	../styles/colors.h ../books/Book.h ../books/BookManager.h ../users/User.h ../users/UserManager.h ../items/account.h ../items/calendar.h ../items/device.h ../items/item.h ../items/itemManager.h ../main.cpp 
	g++ -c -o main.o ../main.cpp

book.o: ../styles/colors.h ../users/User.h ../books/book.h ../books/Comment.h ../books/book.cpp
	g++ -c -o book.o ../books/book.cpp

bookManager.o: ../styles/colors.h ../FileHandler.h ../users/User.h ../books/book.h	../books/BookManager.h ../books/bookManager.cpp
	g++ -c -o bookManager.o ../books/bookManager.cpp

comment.o: ../FileHandler.h ../users/user.h ../books/book.h ../users/userManager.h ../books/Comment.cpp
	g++ -c -o comment.o ../books/Comment.cpp

user.o: ../styles/colors.h ../books/book.h ../users/user.h ../users/user.cpp
	g++ -c -o user.o ../users/user.cpp

userManager.o: ../styles/colors.h ../FileHandler.h ../users/User.h ../users/userManager.h ../users/userManager.cpp
	g++ -c -o userManager.o	../users/userManager.cpp

account.o: ../styles/colors.h ../items/account.h ../users/User.h ../items/account.cpp
	g++ -c -o account.o ../items/account.cpp

calendar.o:	../styles/colors.h ../FileHandler.h ../users/User.h ../items/calendar.h ../items/calendar.cpp
	g++ -c -o calendar.o ../items/calendar.cpp

device.o:	../items/weekday.h ../styles/colors.h ../items/item.h ../items/calendar.h ../items/device.h ../items/device.cpp
	g++ -c -o device.o ../items/device.cpp

item.o: ../styles/colors.h ../items/item.h ../items/item.cpp
	g++ -c -o item.o ../items/item.cpp

itemManager.o:	../styles/colors.h ../FileHandler.h	../items/item.h	../items/account.h	../items/device.h ../items/itemManager.h ../items/itemManager.cpp
	g++ -c -o itemManager.o	../items/itemManager.cpp


clean:
	rm -rf *.o 
	rm -rf ../*.exe