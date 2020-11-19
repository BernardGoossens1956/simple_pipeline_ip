#include "debug_simple_pipeline_ip.h"
#include "simple_pipeline_ip.h"
#include "fetch.h"
#include "decode.h"
#ifndef __SYNTHESIS__
#ifdef DEBUG_DISASSEMBLE
#include "disassemble.h"
#endif
#endif

void fetch_decode(
  fetch_decode_stage_t *fetch_out,
  unsigned int *code_mem,
  bit_t execute_wb_set_pc,
  code_address_t target_pc){
#pragma HLS INLINE off
  instruction_t instruction;
  fetch(fetch_out,
        code_mem,
        &instruction,
        execute_wb_set_pc,
        target_pc);
  decode(instruction,
         &(fetch_out->decoded_instruction));
#ifndef __SYNTHESIS__
#ifdef DEBUG_DISASSEMBLE
  disassemble(fetch_out->pc,
              instruction,
              fetch_out->decoded_instruction);
#endif
#endif
}
