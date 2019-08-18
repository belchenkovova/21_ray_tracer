#include "cl_arg_list.h"

void				cl_args_list_write(t_cl_arg_list *list, int i)
{
	int 			error;
	t_cl_arg		*arg;

	arg = list->array + i;
	error = clEnqueueWriteBuffer(list->queue, arg->device,
		CL_TRUE, 0, arg->size, arg->host, 0, NULL, NULL);
	ASSERT(error == 0)
}