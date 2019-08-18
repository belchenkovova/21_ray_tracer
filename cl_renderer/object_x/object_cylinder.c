#include "object_interaction.h"

void				    object_cylinder_build(t_object *space, va_list *args)
{
    t_object_cylinder	*data;

    data = (t_object_cylinder *)space->data;
    data->top = va_arg(*args, RT_F4_API);
    data->bottom = va_arg(*args, RT_F4_API);
    data->radius = (RT_F)va_arg(*args, double);
	data->axis = f4_normalize(f4_sub(data->top, data->bottom));
	space->type = object_cylinder;
}
