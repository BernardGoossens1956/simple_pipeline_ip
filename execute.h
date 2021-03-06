#ifndef __EXECUTE
#define __EXECUTE

#include "simple_pipeline_ip.h"

void read_reg(
  int *reg_file,
  reg_num_t rs1,
  reg_num_t rs2,
  int *rv1,
  int *rv2);
void write_reg(
  int *reg_file,
  decoded_instruction_t d_i,
  int result);
bit_t compute_branch_result(
  int rv1,
  int rv2,
  func3_t func3);
int compute_op_result(
  int rv1,
  int rv2,
  decoded_instruction_t d_i);
int compute_result(
  int rv1,
  int op_result,
  fetch_decode_stage_t fetch_decode);
code_address_t compute_next_pc(
  fetch_decode_stage_t fetch_decode,
  int rv1,
  bit_t cond,
  bit_t *execute_wb_set_pc);
void mem_store(
  char *data_mem_0,
  char *data_mem_1,
  char *data_mem_2,
  char *data_mem_3,
  data_address_t address,
  int rv2,
  uint2 msize);
int mem_load(
  char *data_mem_0,
  char *data_mem_1,
  char *data_mem_2,
  char *data_mem_3,
  data_address_t address,
  func3_t func3);

#endif
