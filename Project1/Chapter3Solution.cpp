/*

#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <string> 
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ray.h"
using namespace std;

vec3 color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + (t * vec3(0.5f, 0.7f, 1.0f));
}

int mainThree() {
	
	int nx = 200;
	int ny = 100;
	int channels = 3; // RGB; no alpha

	uint8_t* data = new uint8_t[nx * ny * channels];

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {

			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + (u * horizontal) + (v * vertical));
			vec3 col = color(r);

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