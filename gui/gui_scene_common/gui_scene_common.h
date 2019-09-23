#ifndef GUI_SCENE_COMMON_H
# define GUI_SCENE_COMMON_H

# include "rt_parameters.h"

# include "scene.h"

# include <gtk/gtk.h>

typedef struct 		s_gui_scene_common
{
	t_rt_bool		connected;
	t_scene			*ptr_scene;
	t_rt_light_mod	*ptr_light;
	GtkListStore	*full;
	GtkListStore	*limited_main;
	GtkListStore	*limited_limit;
	GtkListStore	*csg;
	GtkListStore	*types;
	GtkListStore	*textures;
	GtkListStore	*background;
	t_rt_bool		reset_generator;
}					t_gui_scene_common;

t_gui_scene_common	*gui_scene_common_new(GtkBuilder *builder);
void				gui_scene_common_connect(t_gui_scene_common *common, ...);
void				gui_scene_common_delete(t_gui_scene_common **common);

typedef enum 		s_gui_scene_list_column
{
	gui_list_column_id,
	gui_list_column_name
}					t_gui_scene_list_column;

void				gui_scene_common_gen_name
					(t_gui_scene_common *scene, t_object *object);

void				gui_scene_common_add_to_list
					(GtkListStore *list, t_object *object);

void 				gui_scene_common_update_full
					(t_gui_scene_common *gui);
void				gui_scene_common_update_limited
					(t_gui_scene_common *gui);
void				gui_scene_common_update_csg
					(t_gui_scene_common *gui);
void 				gui_scene_common_update_types
					(t_gui_scene_common *gui);
void 				gui_scene_common_update_textures
					(t_gui_scene_common *gui);
void 				gui_scene_common_update_background
					(t_gui_scene_common *gui);
void 				gui_scene_common_update_all
					(t_gui_scene_common *gui);

#endif
