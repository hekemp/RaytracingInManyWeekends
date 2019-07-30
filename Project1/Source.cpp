
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
#include "material.h"
#define drand48() (double)rand() / RAND_MAX

using namespace std;

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		return vec3(0, 0, 0);
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

	hitable *list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f, new lambertian(vec3(0.8f, 0.3f, 0.3f)));
	list[1] = new sphere(vec3(0, -100.5f, -1), 100, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f), 0.3f));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5f, new metal(vec3(0.8f, 0.8f, 0.8f), 1.0f));
	hitable *world = new hitable_list(list, 4);

	camera cam;

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {

			vec3 col(0, 0, 0);

			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0f);
				col += color(r, world, 0);
			}

			col /= float(ns);

			col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );

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
