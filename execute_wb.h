#ifndef __EXECUTE_WB
#define __EXECUTE_WB

#include "simple_pipeline_ip.h"

void execute_wb(
  int *reg_file,
  fetch_decode_stage_t execute_in,
  char *data_mem_0,
  char *data_mem_1,
  char *data_mem_2,
  char *data_mem_3,
  bit_t *cancel_execute_wb,
  bit_t *execute_wb_set_pc,
  code_address_t *target_pc,
  unsigned int *nbi,
  bit_t *exit_cond);

#endif
