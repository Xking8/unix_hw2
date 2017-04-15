hw2.so: hw2.cpp
	g++ -o hw2.so -shared -fPIC hw2.cpp -ldl
