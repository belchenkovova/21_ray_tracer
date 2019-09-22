#include "rt_settings.h"

void 				cl_renderer_settings_init(t_rt_settings *settings)
{
	settings->light_basic = RT_LIGHT_BASIC;
	settings->light_area = RT_LIGHT_AREA;
	settings->illumination = RT_ILLUMINATION;
	settings->illumination_value = RT_ILLUMINATION_VALUE;
	settings->sample_count = 1;
	settings->sample_limit = RT_PT_SAMPLE_LIMIT;
	settings->sample_depth = RT_PT_DEPTH;
	settings->motion_blur = RT_MOTION_BLUR;
	settings->motion_blur_sample_count = 1;
	settings->tracing_mod = RT_TRACING_MOD;
	settings->tracing_mod_mask = RT_TRACING_MOD ?
								 RT_OBJECT_RM : RT_OBJECT_RT;
	settings->rm_step_limit = RT_RM_STEP_LIMIT;
	settings->rm_step_part = RT_RM_STEP_PART;
	settings->rm_max_distance = RT_RM_MAX_DISTANCE;
}