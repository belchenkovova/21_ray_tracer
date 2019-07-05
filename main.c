#include "rp.h"
#include "shape_list.h"
#include "material_list.h"

int 				main()
{
	t_rp			*rp;

	rp = rp_new();

	scene_add_light(rp->scene, (t_light){.4, (t_vector3){0., -.3, -4.}});

	scene_add_shape(rp->scene, shape_sphere(
			(t_vector3){0., 0., -5.},
			.5,
			MATERIAL_WHITE));

	scene_add_shape(rp->scene, shape_plane(
			(t_vector3){0., -.51, 0.},
			(t_vector3){0., 1., 0.},
			MATERIAL_RED));

//	scene_add_shape(rp->scene, shape_plane(
//			(t_vector3){0., .3, 0.},
//			(t_vector3){0., -1., 0.},
//			MATERIAL_WHITE));
//
//	scene_add_shape(rp->scene, shape_plane(
//			(t_vector3){-.5, 0., 0.},
//			(t_vector3){1., 0., 0.},
//			MATERIAL_WHITE));
//
//	scene_add_shape(rp->scene, shape_plane(x
//			(t_vector3){.5, 0., 0.},
//			(t_vector3){-1., 0., 0.},
//			MATERIAL_WHITE));

	rp_render(rp);

	mlx_hook(rp->win_ptr, 2, 1, rp_key_press, rp);
	mlx_hook(rp->win_ptr, 17u >> 1u, 1, rp_exit, rp);
	mlx_loop(rp->mlx_ptr);
}
