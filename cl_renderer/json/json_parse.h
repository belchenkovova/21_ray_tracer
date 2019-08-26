#ifndef JSON_PARSE
# define JSON_PARSE

# define JSMN_HEADER
# include "jsmn.h"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>

# include "material.h"
# include "material_list.h"

typedef struct	s_vector3
{
	float		x;
	float		y;
	float		z;
	float       w;
}				t_vector3;

typedef struct	s_parse_object
{
	t_vector3	*val_v1;
	t_vector3	*val_v2;
	char		*val_s1;
	char		*val_s2;
	float		*val_f;
	int			type;
	t_vector3	v1;
	t_vector3	v2;
	float		radius;
	char		*name;
	t_material	material;
}				t_obj;

void		load_scene(void *data, char *path);

char		*read_file(char *path);
int			ft_strequ(char const *s1, char const *s2);

jsmntok_t	*next_item(jsmntok_t *tokens);
char		*get_string_in_object(char *json, jsmntok_t *object, char *target);
t_vector3	*get_vector_in_object(char *json, jsmntok_t *object, char *target);
float		*get_float_in_object(char *json, jsmntok_t *object, char *target);
t_material	decide_material(char *mat_name);

void		parse_camera(void *data, char *json, jsmntok_t *tokens);
void		parse_sphere(void *data, char *json, jsmntok_t *tokens);
void		parse_plane(void *data, char *json, jsmntok_t *tokens);
void		parse_cone(void *data, char *json, jsmntok_t *tokens);
void		parse_cylinder(void *data, char *json, jsmntok_t *tokens);

#endif