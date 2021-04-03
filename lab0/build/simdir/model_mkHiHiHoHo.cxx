/*
 * Generated by Bluespec Compiler (build ad73d8a)
 * 
 * On Fri Mar  5 09:58:50 KST 2021
 * 
 */
#include "bluesim_primitives.h"
#include "model_mkHiHiHoHo.h"

#include <cstdlib>
#include <time.h>
#include "bluesim_kernel_api.h"
#include "bs_vcd.h"
#include "bs_reset.h"


/* Constructor */
MODEL_mkHiHiHoHo::MODEL_mkHiHiHoHo()
{
  mkHiHiHoHo_instance = NULL;
}

/* Function for creating a new model */
void * new_MODEL_mkHiHiHoHo()
{
  MODEL_mkHiHiHoHo *model = new MODEL_mkHiHiHoHo();
  return (void *)(model);
}

/* Schedule functions */

static void schedule_posedge_CLK(tSimStateHdl simHdl, void *instance_ptr)
       {
	 MOD_mkHiHiHoHo &INST_top = *((MOD_mkHiHiHoHo *)(instance_ptr));
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_inc_counter;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_inc_counter;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_say_hi;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_say_hi;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_say_ho;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_say_ho;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_say_bye;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_say_bye;
	 DEF_INST_top_DEF_CAN_FIRE_RL_inc_counter = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE_RL_inc_counter = DEF_INST_top_DEF_CAN_FIRE_RL_inc_counter;
	 INST_top.DEF_x__h104 = INST_top.INST_counter.METH_read();
	 DEF_INST_top_DEF_CAN_FIRE_RL_say_bye = (INST_top.DEF_x__h104) == (tUInt8)4u;
	 DEF_INST_top_DEF_WILL_FIRE_RL_say_bye = DEF_INST_top_DEF_CAN_FIRE_RL_say_bye;
	 DEF_INST_top_DEF_CAN_FIRE_RL_say_hi = (INST_top.DEF_x__h104) < (tUInt8)2u;
	 DEF_INST_top_DEF_WILL_FIRE_RL_say_hi = DEF_INST_top_DEF_CAN_FIRE_RL_say_hi;
	 DEF_INST_top_DEF_CAN_FIRE_RL_say_ho = (INST_top.DEF_x__h104) < (tUInt8)4u && !((INST_top.DEF_x__h104) <= (tUInt8)1u);
	 DEF_INST_top_DEF_WILL_FIRE_RL_say_ho = DEF_INST_top_DEF_CAN_FIRE_RL_say_ho;
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_say_bye)
	   INST_top.RL_say_bye();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_say_hi)
	   INST_top.RL_say_hi();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_say_ho)
	   INST_top.RL_say_ho();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_inc_counter)
	   INST_top.RL_inc_counter();
	 if (do_reset_ticks(simHdl))
	 {
	   INST_top.INST_counter.rst_tick__clk__1((tUInt8)1u);
	 }
       };

/* Model creation/destruction functions */

void MODEL_mkHiHiHoHo::create_model(tSimStateHdl simHdl, bool master)
{
  sim_hdl = simHdl;
  init_reset_request_counters(sim_hdl);
  mkHiHiHoHo_instance = new MOD_mkHiHiHoHo(sim_hdl, "top", NULL);
  bk_get_or_define_clock(sim_hdl, "CLK");
  if (master)
  {
    bk_alter_clock(sim_hdl, bk_get_clock_by_name(sim_hdl, "CLK"), CLK_LOW, false, 0llu, 5llu, 5llu);
    bk_use_default_reset(sim_hdl);
  }
  bk_set_clock_event_fn(sim_hdl,
			bk_get_clock_by_name(sim_hdl, "CLK"),
			schedule_posedge_CLK,
			NULL,
			(tEdgeDirection)(POSEDGE));
  (mkHiHiHoHo_instance->set_clk_0)("CLK");
}
void MODEL_mkHiHiHoHo::destroy_model()
{
  delete mkHiHiHoHo_instance;
  mkHiHiHoHo_instance = NULL;
}
void MODEL_mkHiHiHoHo::reset_model(bool asserted)
{
  (mkHiHiHoHo_instance->reset_RST_N)(asserted ? (tUInt8)0u : (tUInt8)1u);
}
void * MODEL_mkHiHiHoHo::get_instance()
{
  return mkHiHiHoHo_instance;
}

/* Fill in version numbers */
void MODEL_mkHiHiHoHo::get_version(unsigned int *year,
				   unsigned int *month,
				   char const **annotation,
				   char const **build)
{
  *year = 0u;
  *month = 0u;
  *annotation = NULL;
  *build = "ad73d8a";
}

/* Get the model creation time */
time_t MODEL_mkHiHiHoHo::get_creation_time()
{
  
  /* Fri Mar  5 00:58:50 UTC 2021 */
  return 1614905930llu;
}

/* Control run-time licensing */
tUInt64 MODEL_mkHiHiHoHo::skip_license_check()
{
  return 0llu;
}

/* State dumping function */
void MODEL_mkHiHiHoHo::dump_state()
{
  (mkHiHiHoHo_instance->dump_state)(0u);
}

/* VCD dumping functions */
MOD_mkHiHiHoHo & mkHiHiHoHo_backing(tSimStateHdl simHdl)
{
  static MOD_mkHiHiHoHo *instance = NULL;
  if (instance == NULL)
  {
    vcd_set_backing_instance(simHdl, true);
    instance = new MOD_mkHiHiHoHo(simHdl, "top", NULL);
    vcd_set_backing_instance(simHdl, false);
  }
  return *instance;
}
void MODEL_mkHiHiHoHo::dump_VCD_defs()
{
  (mkHiHiHoHo_instance->dump_VCD_defs)(vcd_depth(sim_hdl));
}
void MODEL_mkHiHiHoHo::dump_VCD(tVCDDumpType dt)
{
  (mkHiHiHoHo_instance->dump_VCD)(dt, vcd_depth(sim_hdl), mkHiHiHoHo_backing(sim_hdl));
}
