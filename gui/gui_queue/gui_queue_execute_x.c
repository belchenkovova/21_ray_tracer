#include "gui_queue.h"

void				gui_queue_execute(void *ptr, t_gui_queue *queue)
{
	int 			force;

	force = queue->force_execute;
	queue->force_execute = 0;
	if (!force && queue->wait)
	{
		queue->wait--;
		return ;
	}
	if (!force && g_thread_pool_unprocessed(queue->pool) > RT_GUI_QUEUE_CEILING)
		return ;
	if (!force && queue->block)
		return ;
	queue->master_function(queue->master_data);
}


void				gui_queue_execute_force(t_gui_queue *queue)
{
	gui_queue_push(queue);
	queue->force_execute = 1;
	queue->wait = RT_GUI_QUEUE_WAIT;
}