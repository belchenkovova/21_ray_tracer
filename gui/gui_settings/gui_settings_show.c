#include "gui_settings.h"

void 				gui_settings_show
					(t_gui_settings *gui, t_rt_settings *settings)
{
	gui->tracing_block = rt_true;
	gtk_toggle_button_set_active(gui->tracing_rt,
		settings->tracing_mod == rt_tracing_mod_rt);
	gtk_toggle_button_set_active(gui->tracing_rm,
		settings->tracing_mod == rt_tracing_mod_rm);
	gui->tracing_block = rt_false;
	gui_entry_set_i(gui->rm_steps, settings->rm_step_limit);
	gui_entry_set_f(gui->rm_part, settings->rm_step_part);
	gui_entry_set_f(gui->rm_distance, settings->rm_max_distance);
	rt_assert_critical(!(settings->light_basic && settings->light_area),
		"GUI Settings : Invalid settings");
	gtk_toggle_button_set_active(gui->light_basic, settings->light_basic);
	gtk_toggle_button_set_active(gui->light_area, settings->light_area);
	gtk_switch_set_active(gui->illumination_state, settings->illumination);
	gui_entry_set_f(gui->illumination_value, settings->illumination_value);
	gui_entry_set_i(gui->pt_samples, settings->sample_limit);
	gui_entry_set_i(gui->pt_depth, settings->sample_depth);
	gui_control_hide(&gui->control);
}