#include "gui_queue.h"

void				gui_queue_start(t_gui_queue *queue)
{
	g_timeout_add(100, (GSourceFunc)gui_queue_push, queue);
}
