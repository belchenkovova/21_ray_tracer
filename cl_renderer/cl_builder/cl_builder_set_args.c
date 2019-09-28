/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_builder_set_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashari <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 13:50:02 by ashari            #+#    #+#             */
/*   Updated: 2019/09/28 13:50:04 by ashari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_builder.h"

void				cl_builder_set_args(
					t_cl_builder *builder,
					t_cl_arg_list *list)
{
	int				i;

	i = 0;
	while (i < list->length)
	{
		builder->error = clSetKernelArg(builder->kernel,
			(u_long)i, sizeof(cl_mem), &list->array[i].device);
		rt_assert_critical(builder->error == 0, "Arg List : Arg error");
		i++;
	}
}
