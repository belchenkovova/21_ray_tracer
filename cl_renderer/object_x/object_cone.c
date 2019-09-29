/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashari <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 13:10:24 by ashari            #+#    #+#             */
/*   Updated: 2019/09/29 13:10:25 by ashari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_interaction.h"

void				object_cone_build(t_object *space, va_list *args)
{
	t_object_cone	*data;
	RT_F4_API		temp_axis;
	RT_F4_API		temp_bottom;

	data = (t_object_cone *)space->data;
	data->top = va_arg(*args, RT_F4_API);
	data->bottom = va_arg(*args, RT_F4_API);
	data->radius = (RT_F)va_arg(*args, double);
	temp_axis = f4_sub(data->bottom, data->top);
	data->tangent = data->radius / f4_length(temp_axis);
	data->axis = f4_normalize(temp_axis);
	space->type = object_type_cone;
	temp_bottom = (RT_F4_API)
			{data->bottom.x + data->radius, data->bottom.y, data->bottom.z};
	data->length_line = f4_length(f4_sub(data->top, temp_bottom));
	data->length = data->length_line + data->radius;
}
