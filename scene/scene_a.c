/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashari <ashari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 19:12:36 by ashari            #+#    #+#             */
/*   Updated: 2019/07/01 14:48:18 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_list.h"

t_scene				*scene_a(void)
{
	t_scene			*scene;

	scene = scene_new();
	scene->camera.position = (t_vector3) {0., .3, 9.};
	scene_add_light(scene,
		light_create(light_ambient, .1));
	scene_add_light(scene,
		light_create(light_point, .3, (t_vector3){2., 0., 10.}));
	scene_add_light(scene,
		light_create(light_point, .4, (t_vector3) {0., 5., 5.}));
	scene_add_shape(scene,
		shape_sphere((t_vector3) {-.7, -.5, 1.}, .3, MATERIAL_RED));
	scene_add_shape(scene,
		shape_sphere((t_vector3) {0., -.5, 1.}, .3, MATERIAL_RED));
	scene_add_shape(scene,
		shape_sphere((t_vector3) {.7, -.5, 1.}, .3, MATERIAL_RED));
	scene_add_shape(scene,
		shape_sphere((t_vector3) {0., 0., 0.}, .5, MATERIAL_MIRROR));
	return (scene);
}
