#ifndef CL_RENDERER_SETTINGS_H
# define CL_RENDERER_SETTINGS_H

typedef struct 		s_cl_renderer_settings
{
	int				sample_count;
	int				sample_limit;
	int 			sample_depth;
	int				russian_depth;
	int				srgb;
	int				light_pb;
	int 			light_explicit;
	int 			rm_mod;
	int 			rm_step_limit;
	RT_F			rm_step_part;
	int 			rm_max_distance;
	int				cartoon_effect; // todo: for this we need Phong lightning
	int				filter_sepia;
	int 			filter_stereoscopy;
}					t_cl_renderer_settings;

#endif
