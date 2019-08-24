#ifndef GUI_CAMERA_H
# define GUI_CAMERA_H

# include "rt_parameters.h"

# include "gui_entry.h"
# include "camera.h"

# include <gtk/gtk.h>

typedef struct				s_gui_camera
{
	GtkBox					*control;
	int						control_silent;
	GtkEntry				*position_x;
	GtkEntry				*position_y;
	GtkEntry				*position_z;
	GtkEntry				*rotation_x;
	GtkEntry				*rotation_y;
	GtkEntry				*rotation_z;
	GtkDialog				*screen_success;
	GtkDialog				*screen_fail;
	GtkSwitch				*antialiasing;
	GtkSwitch				*focus;
	GtkWidget				*focus_box;
	GtkEntry				*focal_length;
	GtkEntry				*aperture_size;
}							t_gui_camera;

t_gui_camera				*gui_camera_new(GtkBuilder *builder);
void 						gui_camera_delete(t_gui_camera **camera);

void 						gui_camera_show
							(t_gui_camera *gui, const t_camera *camera);
void 						gui_camera_reset
							(t_gui_camera *gui, const t_camera *camera);
void 						gui_camera_apply
							(t_gui_camera *gui, t_camera *camera);
void 						gui_camera_focus_enable(t_gui_camera *camera);
void 						gui_camera_focus_disable(t_gui_camera *camera);
#endif
