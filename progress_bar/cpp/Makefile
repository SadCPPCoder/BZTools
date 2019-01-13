all: file_test console_test thread_test

file_test: progress_bar
	g++ -o file_test file_test.cpp ProgressBar.o -std=c++11 -lpthread

console_test: progress_bar
	g++ -o console_test console_test.cpp ProgressBar.o -std=c++11 -lpthread

thread_test: progress_bar
	g++ -o thread_test thread_test.cpp ProgressBar.o -std=c++11 -lpthread

progress_bar:
	g++ -c ProgressBar.cpp

clean:
	rm *.o
	rm file_test console_test thread_test
