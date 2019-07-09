#include <cstdio>
#include "stb_image.h"
#include <stdio.h>
#include <string> 
using namespace std;

int main() {
	
	FILE * pFile;
	errno_t err;

	const char * fileName = "myfile.txt";

	if ((err = fopen_s(&pFile, fileName, "w")) != 0) {
		// There was an error and the file was not opened
		puts("whoops");
		return 1;
	}

	// File was opened, pFile can be used to access the stream.
	int nx = 200;
	int ny = 100;

	fprintf(pFile, "P3\n%d %d\n255", nx, ny);
	fclose(pFile);
}
