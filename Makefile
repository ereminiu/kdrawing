make:
	g++ -g main.cpp -o `pkg-config --cflags --libs opencv4`