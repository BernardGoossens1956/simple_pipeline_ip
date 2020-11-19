#ifndef __FETCH
#define __FETCH

#include "simple_pipeline_ip.h"

void fetch(
  fetch_decode_stage_t *fetch_out,
  instruction_t *code_mem,
  instruction_t *instruction,
  bit_t execute_wb_set_pc,
  code_address_t target_pc);

#endif
