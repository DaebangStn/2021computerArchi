/*
 * Generated by Bluespec Compiler (build ad73d8a)
 * 
 * On Wed Apr 28 12:06:53 KST 2021
 * 
 */
#include "bluesim_primitives.h"
#include "module_decode.h"


/* Constructor */
MOD_module_decode::MOD_module_decode(tSimStateHdl simHdl, char const *name, Module *parent)
  : Module(simHdl, name, parent), DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212(67u)
{
  PORT_decode.setSize(75u);
  PORT_decode.clear();
  symbol_count = 1u;
  symbols = new tSym[symbol_count];
  init_symbols_0();
}


/* Symbol init fns */

void MOD_module_decode::init_symbols_0()
{
  init_symbol(&symbols[0u], "decode", SYM_PORT, &PORT_decode, 75u);
}


/* Rule actions */


/* Methods */

tUWide MOD_module_decode::METH_decode(tUInt32 ARG_decode_inst)
{
  tUInt32 DEF_x__h1643;
  tUInt32 DEF_x__h1687;
  tUInt32 DEF_x__h1775;
  tUInt8 DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b101111_1___d82;
  tUInt8 DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b1111___d80;
  tUInt8 DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b10111___d98;
  tUInt8 DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_OR_decod_ETC___d74;
  tUInt8 DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d78;
  tUInt8 DEF_decode_inst_BITS_14_TO_12_EQ_0b10___d4;
  tUInt8 DEF_decode_inst_BITS_11_TO_7_0_EQ_0___d21;
  tUInt8 DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b1_9_THEN_IF__ETC___d27;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b1110011___d18;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b1101111___d17;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b110011___d12;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b10011___d7;
  tUInt8 DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b11___d2;
  tUInt8 DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_0_ELSE_ETC___d62;
  tUInt8 DEF_IF_decode_inst_BIT_30_4_THEN_8_ELSE_9___d45;
  tUInt8 DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55;
  tUInt8 DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52;
  tUInt8 DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d142;
  tUInt32 DEF_immJ__h27;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b1100111___d16;
  tUInt32 DEF_immB__h25;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b1100011___d15;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b110111___d13;
  tUInt32 DEF_immS__h24;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b100011___d9;
  tUInt32 DEF_immU__h26;
  tUInt8 DEF_decode_inst_BITS_6_TO_0_EQ_0b10111___d8;
  tUInt32 DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d208;
  tUInt8 DEF_decode_inst_BIT_30___d44;
  tUInt8 DEF_decode_inst_BIT_31___d190;
  tUInt8 DEF_funct3__h19;
  tUInt8 DEF_decode_inst_BITS_11_TO_7___d20;
  tUInt8 DEF_rs1__h20;
  tUInt8 DEF_opcode__h17;
  tUInt32 DEF_x__h1543;
  tUInt32 DEF_immI__h23;
  tUInt32 DEF_immI_BITS_11_TO_0___h1563;
  DEF_x__h1543 = (tUInt32)(ARG_decode_inst >> 20u);
  DEF_immI__h23 = primSignExt32(32u, 12u, (tUInt32)(DEF_x__h1543));
  DEF_immI_BITS_11_TO_0___h1563 = (tUInt32)(4095u & DEF_immI__h23);
  DEF_opcode__h17 = (tUInt8)((tUInt8)127u & ARG_decode_inst);
  DEF_rs1__h20 = (tUInt8)((tUInt8)31u & (ARG_decode_inst >> 15u));
  DEF_decode_inst_BITS_11_TO_7___d20 = (tUInt8)((tUInt8)31u & (ARG_decode_inst >> 7u));
  DEF_funct3__h19 = (tUInt8)((tUInt8)7u & (ARG_decode_inst >> 12u));
  DEF_decode_inst_BIT_31___d190 = (tUInt8)(ARG_decode_inst >> 31u);
  DEF_decode_inst_BIT_30___d44 = (tUInt8)((tUInt8)1u & (ARG_decode_inst >> 30u));
  DEF_decode_inst_BITS_6_TO_0_EQ_0b10111___d8 = DEF_opcode__h17 == (tUInt8)23u;
  DEF_immU__h26 = ((tUInt32)(ARG_decode_inst >> 12u)) << 12u;
  DEF_decode_inst_BITS_6_TO_0_EQ_0b100011___d9 = DEF_opcode__h17 == (tUInt8)35u;
  DEF_decode_inst_BITS_6_TO_0_EQ_0b110111___d13 = DEF_opcode__h17 == (tUInt8)55u;
  DEF_decode_inst_BITS_6_TO_0_EQ_0b1100011___d15 = DEF_opcode__h17 == (tUInt8)99u;
  DEF_decode_inst_BITS_6_TO_0_EQ_0b1100111___d16 = DEF_opcode__h17 == (tUInt8)103u;
  switch (DEF_opcode__h17) {
  case (tUInt8)55u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d142 = (tUInt8)0u;
    break;
  default:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d142 = DEF_rs1__h20;
  }
  DEF_IF_decode_inst_BIT_30_4_THEN_8_ELSE_9___d45 = DEF_decode_inst_BIT_30___d44 ? (tUInt8)8u : (tUInt8)9u;
  switch (DEF_funct3__h19) {
  case (tUInt8)0u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52 = (tUInt8)0u;
    break;
  case (tUInt8)7u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52 = (tUInt8)2u;
    break;
  case (tUInt8)1u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52 = (tUInt8)7u;
    break;
  case (tUInt8)2u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52 = (tUInt8)5u;
    break;
  case (tUInt8)3u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52 = (tUInt8)6u;
    break;
  case (tUInt8)4u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52 = (tUInt8)4u;
    break;
  case (tUInt8)5u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52 = DEF_IF_decode_inst_BIT_30_4_THEN_8_ELSE_9___d45;
    break;
  default:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52 = (tUInt8)3u;
  }
  switch (DEF_funct3__h19) {
  case (tUInt8)0u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55 = DEF_decode_inst_BIT_30___d44 ? (tUInt8)1u : (tUInt8)0u;
    break;
  case (tUInt8)7u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55 = (tUInt8)2u;
    break;
  case (tUInt8)1u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55 = (tUInt8)7u;
    break;
  case (tUInt8)2u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55 = (tUInt8)5u;
    break;
  case (tUInt8)3u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55 = (tUInt8)6u;
    break;
  case (tUInt8)4u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55 = (tUInt8)4u;
    break;
  case (tUInt8)5u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55 = DEF_IF_decode_inst_BIT_30_4_THEN_8_ELSE_9___d45;
    break;
  default:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55 = (tUInt8)3u;
  }
  switch (DEF_opcode__h17) {
  case (tUInt8)19u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_0_ELSE_ETC___d62 = DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_0_E_ETC___d52;
    break;
  case (tUInt8)51u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_0_ELSE_ETC___d62 = DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_THEN_IF__ETC___d55;
    break;
  default:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_0_ELSE_ETC___d62 = (tUInt8)0u;
  }
  DEF_decode_inst_BITS_6_TO_0_EQ_0b11___d2 = DEF_opcode__h17 == (tUInt8)3u;
  DEF_decode_inst_BITS_6_TO_0_EQ_0b10011___d7 = DEF_opcode__h17 == (tUInt8)19u;
  DEF_decode_inst_BITS_6_TO_0_EQ_0b110011___d12 = DEF_opcode__h17 == (tUInt8)51u;
  DEF_decode_inst_BITS_6_TO_0_EQ_0b1101111___d17 = DEF_opcode__h17 == (tUInt8)111u;
  DEF_decode_inst_BITS_6_TO_0_EQ_0b1110011___d18 = DEF_opcode__h17 == (tUInt8)115u;
  DEF_decode_inst_BITS_11_TO_7_0_EQ_0___d21 = DEF_decode_inst_BITS_11_TO_7___d20 == (tUInt8)0u;
  switch (DEF_funct3__h19) {
  case (tUInt8)1u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b1_9_THEN_IF__ETC___d27 = DEF_decode_inst_BITS_11_TO_7_0_EQ_0___d21 ? (tUInt8)8u : (tUInt8)0u;
    break;
  case (tUInt8)2u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b1_9_THEN_IF__ETC___d27 = DEF_rs1__h20 == (tUInt8)0u ? (tUInt8)7u : (tUInt8)0u;
    break;
  default:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b1_9_THEN_IF__ETC___d27 = (tUInt8)0u;
  }
  DEF_decode_inst_BITS_14_TO_12_EQ_0b10___d4 = DEF_funct3__h19 == (tUInt8)2u;
  switch (DEF_opcode__h17) {
  case (tUInt8)3u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = DEF_decode_inst_BITS_14_TO_12_EQ_0b10___d4 ? (tUInt8)2u : (tUInt8)0u;
    break;
  case (tUInt8)19u:
  case (tUInt8)51u:
  case (tUInt8)55u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = (tUInt8)1u;
    break;
  case (tUInt8)23u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = (tUInt8)9u;
    break;
  case (tUInt8)35u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = DEF_decode_inst_BITS_14_TO_12_EQ_0b10___d4 ? (tUInt8)3u : (tUInt8)0u;
    break;
  case (tUInt8)99u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = (tUInt8)6u;
    break;
  case (tUInt8)103u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = (tUInt8)5u;
    break;
  case (tUInt8)111u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = (tUInt8)4u;
    break;
  case (tUInt8)115u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b1_9_THEN_IF__ETC___d27;
    break;
  default:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38 = (tUInt8)0u;
  }
  switch (DEF_funct3__h19) {
  case (tUInt8)0u:
  case (tUInt8)1u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_OR_decod_ETC___d74 = DEF_funct3__h19;
    break;
  case (tUInt8)4u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_OR_decod_ETC___d74 = (tUInt8)2u;
    break;
  case (tUInt8)5u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_OR_decod_ETC___d74 = (tUInt8)4u;
    break;
  case (tUInt8)6u:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_OR_decod_ETC___d74 = (tUInt8)3u;
    break;
  default:
    DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_OR_decod_ETC___d74 = (tUInt8)5u;
  }
  switch (DEF_opcode__h17) {
  case (tUInt8)99u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d78 = DEF_IF_decode_inst_BITS_14_TO_12_EQ_0b0_9_OR_decod_ETC___d74;
    break;
  case (tUInt8)103u:
  case (tUInt8)111u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d78 = (tUInt8)6u;
    break;
  default:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d78 = (tUInt8)7u;
  }
  DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b10111___d98 = !DEF_decode_inst_BITS_6_TO_0_EQ_0b10111___d8;
  DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b1111___d80 = !(DEF_opcode__h17 == (tUInt8)15u);
  DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b101111_1___d82 = !(DEF_opcode__h17 == (tUInt8)47u);
  DEF_x__h1775 = 2097151u & (((((((tUInt32)(DEF_decode_inst_BIT_31___d190)) << 20u) | (((tUInt32)((tUInt8)((tUInt8)255u & (ARG_decode_inst >> 12u)))) << 12u)) | (((tUInt32)((tUInt8)((tUInt8)1u & (ARG_decode_inst >> 20u)))) << 11u)) | (((tUInt32)(1023u & (ARG_decode_inst >> 21u))) << 1u)) | (tUInt32)((tUInt8)0u));
  DEF_immJ__h27 = primSignExt32(32u, 21u, (tUInt32)(DEF_x__h1775));
  DEF_x__h1687 = 8191u & (((((((tUInt32)(DEF_decode_inst_BIT_31___d190)) << 12u) | (((tUInt32)((tUInt8)((tUInt8)1u & (ARG_decode_inst >> 7u)))) << 11u)) | (((tUInt32)((tUInt8)((tUInt8)63u & (ARG_decode_inst >> 25u)))) << 5u)) | (((tUInt32)((tUInt8)((tUInt8)15u & (ARG_decode_inst >> 8u)))) << 1u)) | (tUInt32)((tUInt8)0u));
  DEF_immB__h25 = primSignExt32(32u, 13u, (tUInt32)(DEF_x__h1687));
  DEF_x__h1643 = 4095u & ((((tUInt32)((tUInt8)(ARG_decode_inst >> 25u))) << 5u) | (tUInt32)(DEF_decode_inst_BITS_11_TO_7___d20));
  DEF_immS__h24 = primSignExt32(32u, 12u, (tUInt32)(DEF_x__h1643));
  switch (DEF_opcode__h17) {
  case (tUInt8)3u:
  case (tUInt8)19u:
  case (tUInt8)103u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d208 = DEF_immI__h23;
    break;
  case (tUInt8)23u:
  case (tUInt8)55u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d208 = DEF_immU__h26;
    break;
  case (tUInt8)35u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d208 = DEF_immS__h24;
    break;
  case (tUInt8)99u:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d208 = DEF_immB__h25;
    break;
  default:
    DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d208 = DEF_immJ__h27;
  }
  DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212.set_bits_in_word(DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d78,
										 2u,
										 0u,
										 3u).build_concat(!DEF_decode_inst_BITS_11_TO_7_0_EQ_0___d21 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b11___d2 || (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b1111___d80 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b10011___d7 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b10111___d8 || (!DEF_decode_inst_BITS_6_TO_0_EQ_0b100011___d9 && (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b101111_1___d82 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b110011___d12 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b110111___d13 || (!DEF_decode_inst_BITS_6_TO_0_EQ_0b1100011___d15 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b1100111___d16 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b1101111___d17 || DEF_decode_inst_BITS_6_TO_0_EQ_0b1110011___d18))))))))))),
												  63u,
												  1u).set_bits_in_word(DEF_decode_inst_BITS_11_TO_7___d20,
														       1u,
														       26u,
														       5u).set_bits_in_word(DEF_decode_inst_BITS_6_TO_0_EQ_0b11___d2 || (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b1111___d80 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b10011___d7 || (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b10111___d98 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b100011___d9 || (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b101111_1___d82 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b110011___d12 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b110111___d13 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b1100011___d15 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b1100111___d16 || DEF_decode_inst_BITS_6_TO_0_EQ_0b1110011___d18))))))))),
																	    1u,
																	    25u,
																	    1u).set_bits_in_word(DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d142,
																				 1u,
																				 20u,
																				 5u).set_bits_in_word(!DEF_decode_inst_BITS_6_TO_0_EQ_0b11___d2 && (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b1111___d80 && (!DEF_decode_inst_BITS_6_TO_0_EQ_0b10011___d7 && (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b10111___d98 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b100011___d9 || (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b101111_1___d82 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b110011___d12 || DEF_decode_inst_BITS_6_TO_0_EQ_0b1100011___d15)))))),
																						      1u,
																						      19u,
																						      1u).set_bits_in_word((tUInt8)((tUInt8)31u & (ARG_decode_inst >> 20u)),
																									   1u,
																									   14u,
																									   5u).set_bits_in_word(DEF_decode_inst_BITS_6_TO_0_EQ_0b1110011___d18,
																												1u,
																												13u,
																												1u).set_bits_in_word(DEF_immI_BITS_11_TO_0___h1563,
																														     1u,
																														     1u,
																														     12u).set_bits_in_word(DEF_decode_inst_BITS_6_TO_0_EQ_0b11___d2 || (DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b1111___d80 && (DEF_decode_inst_BITS_6_TO_0_EQ_0b10011___d7 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b10111___d8 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b100011___d9 || ((DEF_NOT_decode_inst_BITS_6_TO_0_EQ_0b101111_1___d82 && !DEF_decode_inst_BITS_6_TO_0_EQ_0b110011___d12) && (DEF_decode_inst_BITS_6_TO_0_EQ_0b110111___d13 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b1100011___d15 || (DEF_decode_inst_BITS_6_TO_0_EQ_0b1100111___d16 || DEF_decode_inst_BITS_6_TO_0_EQ_0b1101111___d17)))))))),
																																	   1u,
																																	   0u,
																																	   1u).set_whole_word(DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d208,
																																			      0u);
  PORT_decode.set_bits_in_word(2047u & (((((tUInt32)(DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_IF_dec_ETC___d38)) << 7u) | (((tUInt32)(DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_THEN_0_ELSE_ETC___d62)) << 3u)) | (tUInt32)(DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212.get_bits_in_word8(2u,
																																					    0u,
																																					    3u))),
			       2u,
			       0u,
			       11u).set_whole_word(DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212.get_whole_word(1u),
						   1u).set_whole_word(DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212.get_whole_word(0u),
								      0u);
  return PORT_decode;
}

tUInt8 MOD_module_decode::METH_RDY_decode()
{
  tUInt8 PORT_RDY_decode;
  tUInt8 DEF_CAN_FIRE_decode;
  DEF_CAN_FIRE_decode = (tUInt8)1u;
  PORT_RDY_decode = DEF_CAN_FIRE_decode;
  return PORT_RDY_decode;
}


/* Reset routines */


/* Static handles to reset routines */


/* Functions for the parent module to register its reset fns */


/* Functions to set the elaborated clock id */


/* State dumping routine */
void MOD_module_decode::dump_state(unsigned int indent)
{
}


/* VCD dumping routines */

unsigned int MOD_module_decode::dump_VCD_defs(unsigned int levels)
{
  vcd_write_scope_start(sim_hdl, inst_name);
  vcd_num = vcd_reserve_ids(sim_hdl, 2u);
  unsigned int num = vcd_num;
  for (unsigned int clk = 0u; clk < bk_num_clocks(sim_hdl); ++clk)
    vcd_add_clock_def(sim_hdl, this, bk_clock_name(sim_hdl, clk), bk_clock_vcd_num(sim_hdl, clk));
  vcd_write_def(sim_hdl, num++, "IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212", 67u);
  vcd_write_def(sim_hdl, num++, "decode", 75u);
  vcd_write_scope_end(sim_hdl);
  return num;
}

void MOD_module_decode::dump_VCD(tVCDDumpType dt, unsigned int levels, MOD_module_decode &backing)
{
  vcd_defs(dt, backing);
}

void MOD_module_decode::vcd_defs(tVCDDumpType dt, MOD_module_decode &backing)
{
  unsigned int num = vcd_num;
  if (dt == VCD_DUMP_XS)
  {
    vcd_write_x(sim_hdl, num++, 67u);
    vcd_write_x(sim_hdl, num++, 75u);
  }
  else
    if (dt == VCD_DUMP_CHANGES)
    {
      if ((backing.DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212) != DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212)
      {
	vcd_write_val(sim_hdl, num, DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212, 67u);
	backing.DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212 = DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212;
      }
      ++num;
      if ((backing.PORT_decode) != PORT_decode)
      {
	vcd_write_val(sim_hdl, num, PORT_decode, 75u);
	backing.PORT_decode = PORT_decode;
      }
      ++num;
    }
    else
    {
      vcd_write_val(sim_hdl, num++, DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212, 67u);
      backing.DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212 = DEF_IF_decode_inst_BITS_6_TO_0_EQ_0b11_OR_decode_i_ETC___d212;
      vcd_write_val(sim_hdl, num++, PORT_decode, 75u);
      backing.PORT_decode = PORT_decode;
    }
}
