#include "cl_builder.h"

void 				cl_builder_log(t_cl_builder *builder)
{
	char			*log;
	u_long			log_length;
	FILE			*file;

	clGetProgramBuildInfo(builder->program->program, builder->device_id,
		CL_PROGRAM_BUILD_LOG, 0, NULL, &log_length);
	log = ft_strnew(log_length);
	clGetProgramBuildInfo(builder->program->program, builder->device_id,
		CL_PROGRAM_BUILD_LOG, log_length + 1, log, NULL);
	printf("cl compilation log (%d): \n%s\n", builder->program->error, log);
	free(log);
	file = fopen("./cl_renderer/cl_build.c", "w");
	fprintf(file, "%s\n", builder->program->buffer);
	fclose(file);
	exit(1);
}
