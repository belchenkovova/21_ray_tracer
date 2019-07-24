#include "kd_tree.h"

t_kd_tree_side		kd_tree_bb_find_triangle_side(const t_triangle *triangle, t_kd_tree_axis axis, const float *median)
{
	if (axis == axis_x)
	{
		printf("%f < %f = %d\n", triangle->c.x, *median, triangle->c.x < *median);
		printf("side = %s\n", (triangle->center.x < *median ? side_left : side_right) == side_left ? "left" : "right");
		return (triangle->center.x < *median ? side_left : side_right);
	}
	if (axis == axis_y)
		return (triangle->center.y < *median ? side_left : side_right);
	if (axis == axis_z)
		return (triangle->center.z < *median ? side_left : side_right);
	exit(3);
}