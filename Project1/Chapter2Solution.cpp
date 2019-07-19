/*
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <string> 
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vec3.h"
using namespace std;

int main() {
	
	int nx = 200;
	int ny = 100;
	int channels = 3; // RGB; no alpha

	uint8_t* data = new uint8_t[nx * ny * channels];

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2f);

			int ir = int(255.00 * col[0]);
			int ig = int(255.00 * col[1]);
			int ib = int(255.00 * col[2]);

			int index = 3 * (j * nx + i);
			data[index + 0] = ir;
			data[index + 1] = ig;
			data[index + 2] = ib;

		}
	}

	stbi_flip_vertically_on_write(1);
	stbi_write_png("image.png", nx, ny, 3, data, 0);
	delete[] data;

	return 0;

}
*/