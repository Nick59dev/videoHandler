#include <iostream>

#include <processingFile.h>

using namespace std;
using namespace handler;

int main(int argc, char **argv) {
	videoHandler handler;

	printf("This program is working\n");
	handler.reading_rgb(argv[1], argv[2], (unsigned long)atoi(argv[3]), (unsigned long)atoi(argv[4]), (unsigned long)atoi(argv[5]), argv[6]);
	// "media/Picture2.bmp", "flower.yuv", 249, 352, 288

	// cout << argv[1] << argv[2] << argv[3];

	return 0;
}
