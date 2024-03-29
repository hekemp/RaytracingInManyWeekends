/*
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <string>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#define drand48() (double)rand() / RAND_MAX

using namespace std;

vec3 color(const ray& r, hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0f, FLT_MAX, rec)) {
		return 0.5f * vec3((rec.normal.x() + 1), (rec.normal.y() + 1), (rec.normal.z() + 1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + (t * vec3(0.5f, 0.7f, 1.0f));
}

int main() {

	int nx = 200;
	int ny = 100;
	int ns = 100;
	int channels = 3; // RGB; no alpha

	uint8_t* data = new uint8_t[nx * ny * channels];

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f);
	list[1] = new sphere(vec3(0, -100.5f, -1), 100);
	hitable *world = new hitable_list(list, 2);

	camera cam;

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {

			vec3 col(0, 0, 0);

			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0f);
				col += color(r, world);
			}

			col /= float(ns);

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