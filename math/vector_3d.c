#include "vector_3d.h"
#include <stdio.h>

int main(void)
{
	vec3 A = {3, 2, 1};
	vec3 B = {1, 1, 1};
	vec3 X = {1, 0, 0};
	vec3 Y = {0, 1, 0};
	vec3 v[3] = {{0, 4, 0}, {2, 2, 1}, {1, 1, 1}};
	vec3 w[3] = {};
	vec3 R = {0, 0, 0, 
			  vec3_add, vec3_sub, vec3_scale,
			  vec3_dot, vec3_cross, print_vec3,
			  gramschmidt_normalization};

	R.add(A, B, &R);
	R.print(R);

	R.sub(A, B, &R);
	R.print(R);

	R.scale(3, R, &R);
	R.print(R);

	printf("A dot B = %f\n", R.dot(A, B));

	R.cross(X, Y, &R);
	printf("A cross B = ");
	R.print(R);

	R.gramschmidt(v, w, R);

	return 0;
}
