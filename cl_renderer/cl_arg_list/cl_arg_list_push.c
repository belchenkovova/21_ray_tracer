#include "cl_arg_list.h"

int					cl_arg_list_push
					(t_cl_arg_list *list, void *ptr,
					u_long size, cl_mem_flags type)
{
	int 			i;
	int 			error;

#ifndef RT_NO_OPEN_CL
	if (list->length == RT_CL_ARGS_CAPACITY)
		return (-1);
	i = list->length++;
	list->array[i].host = ptr;
	list->array[i].size = size;
	list->array[i].update_need = ptr != NULL;
	list->array[i].device = clCreateBuffer(list->context,
		type, size, NULL, &error);
	ASSERT(error == 0)
	return (i);
#else
	return (-1);
#endif
}