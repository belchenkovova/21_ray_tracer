/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_arg_list_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashari <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 13:42:25 by ashari            #+#    #+#             */
/*   Updated: 2019/10/01 18:09:14 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_arg_list.h"

void				cl_args_list_write(t_cl_arg_list *list, int i)
{
	int				error;
	t_cl_arg		*arg;

	arg = list->array + i;
	if (!arg->host)
		return ;
	error = clEnqueueWriteBuffer(list->queue, arg->device,
		CL_TRUE, 0, arg->size, arg->host, 0, NULL, NULL);
	rt_assert(error == 0, "Arg List : Writing error");
}
