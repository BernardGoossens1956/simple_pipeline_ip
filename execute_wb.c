#include "debug_simple_pipeline_ip.h"
#include "simple_pipeline_ip.h"
#include "execute.h"
#ifndef __SYNTHESIS__
#ifdef DEBUG_EMULATE
#include "emulate.h"
#endif
#endif

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
  bit_t *exit_cond){
#pragma HLS INLINE off
  int rv1, rv2, rs, op_result, result;
  bit_t bcond, taken_branch, cancel, cancel_next;
  cancel = *cancel_execute_wb;
  if (!cancel){
    read_reg(reg_file,
             execute_in.decoded_instruction.rs1,
             execute_in.decoded_instruction.rs2,
             &rv1,
             &rv2);
    bcond = compute_branch_result(
            rv1,
            rv2,
            execute_in.decoded_instruction.func3);
    taken_branch =
           (execute_in.decoded_instruction.is_branch &&
            bcond);
    cancel_next =
            execute_in.decoded_instruction.is_jump ||
            taken_branch;
    rs = (execute_in.decoded_instruction.type == R_TYPE)?
          rv2:
     (int)execute_in.decoded_instruction.imm;
    op_result = compute_op_result(
      rv1,
      rs,
      execute_in.decoded_instruction);
    result = compute_result(
      rv1,
      op_result,
      execute_in);
    *target_pc = compute_next_pc(
      execute_in,
      rv1,
      bcond,
      execute_wb_set_pc);
    *cancel_execute_wb = cancel_next;
    *exit_cond =
       execute_in.decoded_instruction.is_ret &&
       reg_file[RA]==0;
    if (execute_in.decoded_instruction.is_store){
      mem_store(
        data_mem_0,
        data_mem_1,
        data_mem_2,
        data_mem_3,
       (data_address_t)result,
        rv2,
        execute_in.decoded_instruction.func3);
    }
    else if (execute_in.decoded_instruction.is_load)
      result = mem_load(
                 data_mem_0,
                 data_mem_1,
                 data_mem_2,
                 data_mem_3,
                (data_address_t)result,
                 execute_in.decoded_instruction.func3);
    write_reg(reg_file,
              execute_in.decoded_instruction,
              result);
    *nbi = *nbi + 1;
#ifndef __SYNTHESIS__
#ifdef DEBUG_EMULATE
    emulate(reg_file,
            execute_in.decoded_instruction,
           *target_pc);
#endif
#endif
  }
  else{
    *cancel_execute_wb = 0;
    *execute_wb_set_pc = 0;
    *exit_cond = 0;
#ifndef __SYNTHESIS__
#ifdef DEBUG_FETCH
    printf("%04d: cancelled\n", execute_in.pc);
#endif
#endif
  }
}
