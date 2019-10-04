/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_edit_init_light_x.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:11:34 by bshanae           #+#    #+#             */
/*   Updated: 2019/10/03 13:11:59 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_scene_edit.h"

void						gui_scene_edit_init_light_point
	(t_gui_scene_edit *edit, GtkBuilder *builder)
{
	t_gui_init_light_point	init;

	ft_strcpy(init.position_x, "object_edit_light_point_position_x");
	ft_strcpy(init.position_y, "object_edit_light_point_position_y");
	ft_strcpy(init.position_z, "object_edit_light_point_position_z");
	edit->light_point = gui_object_light_point_init(&init, builder);
}

void						gui_scene_edit_init_light_direct
	(t_gui_scene_edit *edit, GtkBuilder *builder)
{
	t_gui_init_light_direct	init;

	ft_strcpy(init.direction_x, "object_edit_light_direct_direction_x");
	ft_strcpy(init.direction_y, "object_edit_light_direct_direction_y");
	ft_strcpy(init.direction_z, "object_edit_light_direct_direction_z");
	edit->light_direct = gui_object_light_direct_init(&init, builder);
}
