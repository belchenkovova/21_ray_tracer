#include "gui_settings.h"

static RT_F			static_bound(RT_F value)
{
	if (value < (RT_F)0.01)
		return ((RT_F)0.01);
	if (value > (RT_F)1.)
		return (RT_F)1.;
	return (value);
}

void 				gui_settings_apply
					(t_gui_settings *gui, t_rt_settings *settings)
{
	settings->sample_limit = gui_entry_get_i(gui->pt_samples_limit);
	settings->sample_depth = gui_entry_get_i(gui->pt_depth);
	settings->rm_step_limit = gui_entry_get_i(gui->rm_steps);
	settings->rm_step_part = static_bound(gui_entry_get_f(gui->rm_part));
	settings->rm_max_distance = gui_entry_get_f(gui->rm_distance);
	settings->illumination_value = gui_entry_get_f(gui->illumination_value);
	gui_settings_show(gui, settings);
}
