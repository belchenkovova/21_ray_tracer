#ifndef RT_PARAMETERS_H
# define RT_PARAMETERS_H

# define RT_GUI_BUILD					"./gui/source/build.glade"
# define RT_GUI_THEME					"./gui/source/theme_breeze/gtk-3.20/gtk.css"
# define RT_GUI_GET						gtk_builder_get_object

# define RT_GUI_WIDTH					480
# define RT_GUI_HEIGHT					480

# define RT_CL_OBJECT_DATA_CAPACITY		64
# define RT_CL_SCENE_OBJECTS_CAPACITY	16

# define RT_CL_PATH_DEPTH				1
# define RT_CL_SAMPLES					2
# define RT_CL_RUSSIAN_DEPTH			10
# define RT_CL_SRGB						1
# define RT_CL_LIGHT_PB					1
# define RT_CL_LIGHT_EXPLICIT			1
# define RT_CL_ANTIALIASING				1
# define RT_CL_FOCUS					0
# define RT_CL_APERTURE_SIZE			5.
# define RT_CL_FOCAL_LENGTH				40.

#ifdef RT_FLOAT
#  define INTERSECTION_MIN				0.0001
#endif

#ifdef RT_DOUBLE
#  define INTERSECTION_MIN				0.000001
#endif

# define RT_INTERSECTION_MAX		INFINITY

#endif
