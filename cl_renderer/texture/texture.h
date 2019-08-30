#ifndef TEXTURE_H
# define TEXTURE_H

# include <stdlib.h>
# include <OpenCL/opencl.h>

# include "libft_standart.h"

# include "rt_parameters.h"
# include "stb_image.h"
# include "rt_float.h"

# define TEXTURE_WOOD		"/Users/ashari/21_ray_tracer/cl_renderer/texture/texture_sources/wood.png"
# define TEXTURE_CHESS		"/Users/ashari/21_ray_tracer/cl_renderer/texture/texture_sources/chess.jpg"
# define TEXTURE_PLANET		"/Users/ashari/21_ray_tracer/cl_renderer/texture/texture_sources/planet.jpg"

# define TEXTURE_CHANNELS	4

typedef struct 				s_texture
{
	RT_F4_API				*data;
	int 					texture_length[MAX_TEXTURES_NUMBER];
	int						width[MAX_TEXTURES_NUMBER];
	int						height[MAX_TEXTURES_NUMBER];
	int 					textures_number;
}							t_texture;

t_texture					*texture_new(void);

void						texture_data_load(t_texture *texture, const char *path);

void						texture_fill_data(
							t_texture *texture,
							unsigned char *stbi_data);

void						texture_get_space(t_texture *texture);

void						texture_convert(
							const t_texture *texture,
							RT_F4_API *pointer,
							const unsigned char *stbi_data);

void 						texture_delete(t_texture **texture);

#endif
