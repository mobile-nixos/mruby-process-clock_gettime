#include <mruby.h>
#include <mruby/class.h>
#include <mruby/error.h>
#include <mruby/value.h>
#include <time.h>

static mrb_value mrb_process_clock_gettime(mrb_state *mrb, mrb_value self)
{
	int ret;
	struct timespec ts;
	mrb_int clock_arg = -1;

	mrb_get_args(mrb, "i", &clock_arg);

	ret = clock_gettime((clockid_t)clock_arg, &ts);

	if (ret == -1) {
		mrb_sys_fail(mrb, "clock_gettime");
	}

	return mrb_float_value(mrb, (float)ts.tv_sec + ((float)ts.tv_nsec)/1000000000);
}

#define CONST(name) mrb_define_const(mrb, process, #name, mrb_fixnum_value(name))

void mrb_mruby_process_clock_gettime_gem_init(mrb_state *mrb)
{
	struct RClass *process;
	process = mrb_module_get(mrb, "Process");
	mrb_define_class_method(mrb, process, "clock_gettime", mrb_process_clock_gettime, MRB_ARGS_ARG(1, 1));
	CONST(CLOCK_REALTIME);
	CONST(CLOCK_MONOTONIC);
	CONST(CLOCK_PROCESS_CPUTIME_ID);
	CONST(CLOCK_THREAD_CPUTIME_ID);
	CONST(CLOCK_BOOTTIME);
	CONST(CLOCK_REALTIME_ALARM);
	CONST(CLOCK_BOOTTIME_ALARM);
}

void mrb_mruby_process_clock_gettime_gem_final(mrb_state *mrb)
{
}
