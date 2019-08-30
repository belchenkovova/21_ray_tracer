#include "texture.h"

t_texture			*texture_new(void)
{
	t_texture		*new;

	new = (t_texture *)malloc(sizeof(t_texture));
	ft_bzero(new, sizeof(t_texture));
	new->textures_number = -1;
	texture_data_load(new, TEXTURE_CHESS);
	texture_data_load(new, TEXTURE_WOOD);
	texture_data_load(new, TEXTURE_PLANET);
	return (new);
}
