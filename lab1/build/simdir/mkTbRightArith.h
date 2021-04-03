/*
 * Generated by Bluespec Compiler (build ad73d8a)
 * 
 * On Thu Mar 18 20:40:23 KST 2021
 * 
 */

/* Generation options: */
#ifndef __mkTbRightArith_h__
#define __mkTbRightArith_h__

#include "bluesim_types.h"
#include "bs_module.h"
#include "bluesim_primitives.h"
#include "bs_vcd.h"


/* Class declaration for the mkTbRightArith module */
class MOD_mkTbRightArith : public Module {
 
 /* Clock handles */
 private:
  tClock __clk_handle_0;
 
 /* Clock gate handles */
 public:
  tUInt8 *clk_gate[0];
 
 /* Instantiation parameters */
 public:
 
 /* Module state */
 public:
  MOD_Reg<tUInt32> INST_cycle;
  MOD_Reg<tUInt8> INST_randomShift_init;
  MOD_Reg<tUInt8> INST_randomVal_init;
 
 /* Constructor */
 public:
  MOD_mkTbRightArith(tSimStateHdl simHdl, char const *name, Module *parent);
 
 /* Symbol init methods */
 private:
  void init_symbols_0();
 
 /* Reset signal definitions */
 private:
  tUInt8 PORT_RST_N;
 
 /* Port definitions */
 public:
 
 /* Publicly accessible definitions */
 public:
  tUInt32 DEF__read__h65;
  tUInt8 DEF_cycle_EQ_128___d6;
 
 /* Local definitions */
 private:
  tUInt64 DEF_x__h589;
  tUInt64 DEF_TASK_getRandom___d10;
 
 /* Rules */
 public:
  void RL_randomVal_initialize();
  void RL_randomShift_initialize();
  void RL_test();
 
 /* Methods */
 public:
 
 /* Reset routines */
 public:
  void reset_RST_N(tUInt8 ARG_rst_in);
 
 /* Static handles to reset routines */
 public:
 
 /* Pointers to reset fns in parent module for asserting output resets */
 private:
 
 /* Functions for the parent module to register its reset fns */
 public:
 
 /* Functions to set the elaborated clock id */
 public:
  void set_clk_0(char const *s);
 
 /* State dumping routine */
 public:
  void dump_state(unsigned int indent);
 
 /* VCD dumping routines */
 public:
  unsigned int dump_VCD_defs(unsigned int levels);
  void dump_VCD(tVCDDumpType dt, unsigned int levels, MOD_mkTbRightArith &backing);
  void vcd_defs(tVCDDumpType dt, MOD_mkTbRightArith &backing);
  void vcd_prims(tVCDDumpType dt, MOD_mkTbRightArith &backing);
};

#endif /* ifndef __mkTbRightArith_h__ */
