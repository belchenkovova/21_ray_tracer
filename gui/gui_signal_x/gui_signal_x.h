#ifndef GUI_SIGNAL_H
# define GUI_SIGNAL_H

# include "gui_entry.h"
# include "gui.h"

# include <time.h>

# define GTK_SIGNAL_SIGNATURE GtkWidget *w, gpointer p

void 				gui_signal_exit
					(GTK_SIGNAL_SIGNATURE);
gboolean			gui_signal_key
					(GtkWidget *widget, GdkEventKey *event, gpointer ptr);
void				gui_signal_notebook_fix
					(GtkNotebook *notebook, GtkWidget *page,
					guint page_num, gpointer ptr);

void 				gui_signal_parser_select
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_parser_load
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_parser_dialog_run
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_parser_dialog_select
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_parser_dialog_response_close
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_parser_dialog_response_no
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_parser_dialog_response_yes
					(GTK_SIGNAL_SIGNATURE);

void				gui_signal_camera_entry_insert
					(GtkEntry *entry, const char *new,
					int length, int *position, gpointer ptr);
void 				gui_signal_camera_entry_delete
					(GtkEntry *entry, int start, int end, gpointer ptr);
gboolean			gui_signal_camera_antialiasing
					(GtkWidget *widget, gboolean state, gpointer ptr);
void				gui_signal_camera_filter
					(GtkWidget *widget, gpointer ptr);
gboolean			gui_signal_camera_focus_enable
					(GtkWidget *widget, gboolean state, gpointer ptr);
void				gui_signal_camera_focus_auto
					(GtkWidget *widget, gpointer ptr);
void				gui_signal_camera_screen_save
					(GtkWidget *widget, gpointer ptr);
void				gui_signal_camera_screen_success_close
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_camera_screen_fail_close
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_camera_reset
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_camera_apply
					(GTK_SIGNAL_SIGNATURE);

void				gui_signal_scene_edit_entry_insert
					(GtkEntry *entry, const char *new,
					int length, int *position, gpointer ptr);
void 				gui_signal_scene_edit_entry_delete
					(GtkEntry *entry, int start, int end, gpointer ptr);
void 				gui_signal_scene_edit_entry_changed
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_scene_edit_select
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_reset
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_apply
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_material_color
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_material_emission
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_add
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_remove
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_remove_response_cancel
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_remove_response_yes
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_edit_remove_response_no
					(GTK_SIGNAL_SIGNATURE);

void				gui_signal_scene_add_response_cancel
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_scene_add_response_yes
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_scene_add_response_no
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_scene_add_type
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_add_material_color
					(GTK_SIGNAL_SIGNATURE);
void				gui_signal_scene_add_material_emission
					(GTK_SIGNAL_SIGNATURE);

void				gui_signal_settings_entry_changed
					(GtkWidget *widget, gpointer ptr);
void				gui_signal_settings_entry_insert
					(GtkEntry *entry, const char *new,
					int length, int *position, gpointer ptr);
void 				gui_signal_settings_entry_delete
					(GtkEntry *entry, int start, int end, gpointer ptr);
void 				gui_signal_settings_reset
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_settings_apply
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_settings_light
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_settings_tracing_rt
					(GTK_SIGNAL_SIGNATURE);
void 				gui_signal_settings_tracing_rm
					(GTK_SIGNAL_SIGNATURE);

gboolean 			gui_signal_image_click
					(GtkWidget *widget, GdkEventButton *event, gpointer ptr);

gboolean			gui_signal_task_add(gpointer ptr);
void				gui_signal_task_execute(gpointer ptr, gpointer user_ptr);

#endif
