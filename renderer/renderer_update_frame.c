#include "renderer.h"

void 				renderer_update_frame(t_renderer *renderer)
{
	printf("sample iteration %d\n", ++renderer->sample_number);
//	for (int y = WINDOW_HEIGHT / 2 - 10; y <= WINDOW_HEIGHT / 2 + 10; ++y)
	for (int y = 0; y < WINDOW_HEIGHT; ++y)
	{
		if (RENDER_PROGRESS == 1 && !(y % 5))
			printf("%.2f%%\n", (y * 100.) / WINDOW_HEIGHT );

//		for (int x = WINDOW_WIDTH / 2 - 10; x <= WINDOW_WIDTH / 2 + 10; ++x)
		for (int x = 0; x < WINDOW_WIDTH; ++x)
		{
			renderer_build_ray(renderer, &x, &y);
			renderer_radiance(renderer);
			renderer_write_radiance(renderer, &x, &y);
		}
		if (RENDER_PROGRESS == 2)
			sdl_ctrl_upload(renderer->sdl);
	}
	if (RENDER_PROGRESS != 2 && renderer_check_interval(renderer))
		sdl_ctrl_upload(renderer->sdl);
}