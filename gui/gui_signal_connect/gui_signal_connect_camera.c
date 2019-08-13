#include "gui_signal_connect.h"

void 				gui_signal_connect_camera(t_gui *gui)
{
	GUI_CONNECT(gui->builder, gui_signal_camera_position_x)
	GUI_CONNECT(gui->builder, gui_signal_camera_position_y)
	GUI_CONNECT(gui->builder, gui_signal_camera_position_z)
	GUI_CONNECT(gui->builder, gui_signal_camera_rotation_x)
	GUI_CONNECT(gui->builder, gui_signal_camera_rotation_y)
	GUI_CONNECT(gui->builder, gui_signal_camera_rotation_z)
}