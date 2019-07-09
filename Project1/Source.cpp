#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <string> 
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;

int main() {
	
	FILE * pFile;
	errno_t err;

	const char * fileName = "test.pmm";

	if ((err = fopen_s(&pFile, fileName, "wb")) != 0) {
		// There was an error and the file was not opened
		puts("whoops");
		return 1;
	}

	// File was opened, pFile can be used to access the stream.
	int nx = 200;
	int ny = 100;

	fprintf(pFile, "P3\n%d %d\n255\n", nx, ny);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = .2f;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			fprintf(pFile, "%d %d %d\n", ir, ig, ib);

		}
	}

	int x, y, n;

	stbi_write_png("imageResult.png", nx, ny, 3, pFile, 0);

	fclose(pFile);

	return 0;

}
