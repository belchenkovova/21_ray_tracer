#include "gui_object_x.h"


t_gui_object_pair			gui_object_pair_init
							(t_gui_init_pair *init, GtkBuilder *builder)
{
	t_gui_object_pair		pair;

	pair.first_combo = RT_GUI_GET(builder, init->first_combo);
	pair.second_combo = RT_GUI_GET(builder, init->second_combo);
	pair.first_list = RT_GUI_GET(builder, init->first_list);
	pair.second_list = RT_GUI_GET(builder, init->second_list);
	return (pair);
}

static t_rt_bool			static_find_in_list
							(GtkTreeModel *model, int id, GtkTreeIter *iter)
{
	int 					temp;

	if (id < 0)
	{
		rt_assert(0, "GUI Pair : Invalid id (id = %i)", id);
		return (rt_false);
	}
	if (!gtk_tree_model_get_iter_first(model, iter))
	{
		rt_assert(0, "GUI Pair : List is empty");
		return (rt_false);
	}
	while (1)
	{
		gtk_tree_model_get(model, iter, gui_scene_column_id, &temp, -1);
		if (temp == id)
			return (rt_true);
		if (!gtk_tree_model_iter_next(model, iter))
		{
			rt_assert(0, "GUI Pair : id not found");
			return (rt_false);
		}
	}
}

void						gui_object_pair_get
							(t_gui_object_pair *gui, t_object *object)
{
	GtkTreeIter				iter;
	t_object_pair			*pair;
	t_rt_bool				result;

	pair = (t_object_pair *)object->data;
	result = static_find_in_list(GTK_TREE_MODEL(gui->first_list),
		pair->first_id, &iter);
	if (result == rt_false)
		return ;
	gtk_combo_box_set_active_iter(gui->first_combo, &iter);
	result = static_find_in_list(GTK_TREE_MODEL(gui->second_list),
		pair->second_id, &iter);
	if (result == rt_false)
		return ;
	gtk_combo_box_set_active_iter(gui->second_combo, &iter);
}

void 						gui_object_pair_set
							(t_gui_object_pair *gui, t_object *object)
{
	GtkTreeIter				iter[2];
	t_rt_bool				result[2];
	int 					i[2];
	CHAR_REF				str[2];
	t_object_pair			*pair;

	result[0] = gtk_combo_box_get_active_iter(gui->first_combo, iter + 0);
	result[1] = gtk_combo_box_get_active_iter(gui->second_combo, iter + 1);
	if (!result[0] || !result[1])
	{
		rt_assert(0, "GUI Pair : No object selected");
		return ;
	}
	pair = (t_object_pair *)object->data;
	gtk_tree_model_get(GTK_TREE_MODEL(gui->first_list), iter + 0,
		gui_scene_column_id, i + 0, gui_scene_column_name, str + 0, -1);
	gtk_tree_model_get(GTK_TREE_MODEL(gui->second_list), iter + 1,
		gui_scene_column_id, i + 1, gui_scene_column_name, str + 1, -1);
	pair->first_id = i[0];
	ft_strcpy(pair->first_name, str[0]);
	pair->second_id = i[1];
	ft_strcpy(pair->second_name, str[1]);
}