
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

hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5f, 0.5f, 0.5f)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = float(drand48());
			vec3 center(float(a + (0.9f * drand48())), 0.2f, float(b + (0.9f * drand48())));
			if ((center - vec3(4, 0.2f, 0)).length() > 0.9f) {
				if (choose_mat < 0.8f) { // diffuse
					list[i++] = new sphere(center, 0.2f, 
						new lambertian(vec3(float(drand48() * drand48()), float(drand48() * drand48()), float(drand48() * drand48()))));
				} else if (choose_mat < 0.95f) { // metal
					list[i++] = new sphere(center, 0.2f,
						new metal(vec3(0.5f * float(1 + drand48()), 0.5f * float(1 + drand48()), 0.5f * float(1 + drand48())), 0.5f * float(drand48())));
				} else { // glass
					list[i++] = new sphere(center, 0.2f,
						new dielectric(1.5f));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0f, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0f, new lambertian(vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.2f));

	return new hitable_list(list, i);

}

int main() {

	int nx = 200;
	int ny = 100;
	int ns = 100;
	int channels = 3; // RGB; no alpha

	uint8_t* data = new uint8_t[nx * ny * channels];

	hitable *world = random_scene();

	vec3 lookfrom(3, 3, 2);
	vec3 lookat(0, 0, - 1);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 0.5f;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 40, float(nx)/float(ny), aperture, dist_to_focus);
	//camera cam(vec3(-2, 2, 1), vec3(0, 0, -1), vec3(0, 1, 0), 45, float(nx)/float(ny));

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
