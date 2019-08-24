#ifndef GUI_OBJECT_ADD_H
# define GUI_OBJECT_ADD_H

# include "rt_parameters.h"

# include "libft_standart.h"
# include "gui_material.h"
# include "gui_object_x.h"
# include "object_definition.h"
# include "color_list.h"

# include <gtk/gtk.h>

typedef enum 					e_gui_scene_add_list
{
	scene_add_type_name,
	scene_add_type_id
}								t_gui_scene_add_list;

typedef struct 					s_gui_scene_add
{
	GtkDialog					*dialog;
	GtkEntry					*name;
	GtkComboBox					*type_combo;
	GtkEntry					*type_entry;
	GtkListStore				*type_list;
	t_gui_object_light_point	light_point;
	t_gui_object_light_direct	light_direct;
	t_gui_object_sphere			sphere;
	t_gui_object_plane			plane;
	t_gui_object_cone			cone;
	t_gui_object_cylinder		cylinder;
	t_gui_object_box			box;
	t_gui_object_paraboloid		paraboloid;
	t_gui_object_moebius		moebius;
	t_gui_object_torus			torus;
	t_gui_object_mandelbulb		mandelbulb;
	t_gui_object_julia			julia;
	GtkWidget					*material_color_box;
	int 						material_color_silent;
	t_gui_material				material;
	GtkStack					*stack;
	t_object_type				current_type;
	int 						gen_name_next;
}								t_gui_scene_add;

t_gui_scene_add					*gui_scene_add_new(GtkBuilder *builder);
void 							gui_scene_add_delete(t_gui_scene_add **object);

void 							gui_scene_add_init_own
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_light_point
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_light_direct
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_sphere
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_plane
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_cone
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_cylinder
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_box
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_paraboloid
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_moebius
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_torus
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_mandelbulb
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_julia
								(t_gui_scene_add *add, GtkBuilder *builder);
void 							gui_scene_add_init_material
								(t_gui_scene_add *add, GtkBuilder *builder);

void 							gui_scene_add_update
								(t_gui_scene_add *add);
void 							gui_scene_add_material_state_light
								(t_gui_scene_add *add);
void 							gui_scene_add_material_state_non_light
								(t_gui_scene_add *add);
char							*gui_scene_add_gen_name
								(t_gui_scene_add *add);
void							gui_scene_add_build_object
								(t_gui_scene_add *add, t_object *space);

#endif
