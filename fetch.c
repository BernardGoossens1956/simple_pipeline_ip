#include "debug_simple_pipeline_ip.h"
#include "simple_pipeline_ip.h"
#ifndef __SYNTHESIS__
#ifdef DEBUG_FETCH
#include <stdio.h>
#endif
#endif

void fetch(fetch_decode_stage_t *fetch_out,
           instruction_t *code_mem,
           instruction_t *instruction,
           bit_t execute_wb_set_pc,
           code_address_t target_pc){
#pragma HLS INLINE
  fetch_out->pc = (execute_wb_set_pc)?
                   target_pc:
                   fetch_out->pc + 4;
  *instruction = code_mem[fetch_out->pc >> 2];
#ifndef __SYNTHESIS__
#ifdef DEBUG_FETCH
  printf("%04d: %08x      ", (unsigned int)fetch_out->pc,
                             (unsigned int)*instruction);
#ifndef DEBUG_DISASSEMBLE
  printf("\n");
#endif
#endif
#endif
}
