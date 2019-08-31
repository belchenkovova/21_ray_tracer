#include "texture.h"

RT_F4_API			*texture_iter(t_texture *texture)
{
	RT_F4_API		*pointer;
	int 			i;

	i = 0;
	pointer = &texture->data[0];
	while (i < texture->textures_number)
		pointer += texture->texture_length[i++];
	return (pointer);
}
