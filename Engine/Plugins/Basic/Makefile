all:
	# compile code into object files with proper includes
	g++ -c basic.cpp -fPIC -o basic.o -I../../Source/Runtime/Core/Public -I../../Source/Runtime/Raptor/Public -std=c++11

	# link object file into shared library
	g++ basic.o -shared -o libbasic.so

	# delete temporary object file
	rm basic.o
