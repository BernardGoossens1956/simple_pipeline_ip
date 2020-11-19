#include "ap_cint.h"
#include "debug_simple_pipeline_ip.h"
#include "simple_pipeline_ip.h"
#include "new_cycle.h"
#include "fetch_decode.h"
#include "execute_wb.h"
#ifndef __SYNTHESIS__
#ifdef DEBUG_REG_FILE
#include "print.h"
#endif
#endif

void init_reg_file(int *reg_file){
#pragma HLS INLINE off
  uint6 i;
  for (i = 0; i < NB_REGISTER; i++)
    reg_file[i] = 0;
}
void simple_pipeline_ip(
  unsigned int  pc[2],
  unsigned int  code_mem  [CODE_MEM_SIZE/sizeof(int)],
  char          data_mem_0[DATA_MEM_SIZE/sizeof(int)],
  char          data_mem_1[DATA_MEM_SIZE/sizeof(int)],
  char          data_mem_2[DATA_MEM_SIZE/sizeof(int)],
  char          data_mem_3[DATA_MEM_SIZE/sizeof(int)],
  unsigned int *nb_instruction){
#pragma HLS INTERFACE s_axilite port=pc
#pragma HLS INTERFACE s_axilite port=code_mem
#pragma HLS INTERFACE s_axilite port=data_mem_0
#pragma HLS INTERFACE s_axilite port=data_mem_1
#pragma HLS INTERFACE s_axilite port=data_mem_2
#pragma HLS INTERFACE s_axilite port=data_mem_3
#pragma HLS INTERFACE s_axilite port=nb_instruction
#pragma HLS INTERFACE ap_ctrl_none port=return
  int reg_file[NB_REGISTER];
#pragma HLS ARRAY_PARTITION variable=reg_file dim=1 complete
  code_address_t       target_pc;
  fetch_decode_stage_t fetch_out;
  fetch_decode_stage_t execute_in;
  unsigned int         nbi;
  bit_t                exit_cond;
  bit_t                cancel_execute_wb;
  bit_t                execute_wb_set_pc;
  init_reg_file(reg_file);
  cancel_execute_wb = 1;
  execute_wb_set_pc = 1;
  target_pc         = pc[0];
  fetch_out.pc      = pc[0]-4;
  nbi               = 0;
  exit_cond         = 0;
  while(!exit_cond){
#pragma HLS PIPELINE off
    new_cycle(fetch_out,
              &execute_in);
    fetch_decode(&fetch_out,
                 code_mem,
                 execute_wb_set_pc,
                 target_pc);
    execute_wb(reg_file,
               execute_in,
               data_mem_0,
               data_mem_1,
               data_mem_2,
               data_mem_3,
               &cancel_execute_wb,
               &execute_wb_set_pc,
               &target_pc,
               &nbi,
               &exit_cond);
  };
#ifndef __SYNTHESIS__
#ifdef DEBUG_FETCH
  printf("%04d: cancelled\n", fetch_out.pc);
#endif
#endif
  pc[1]           = fetch_out.pc - 4;
  *nb_instruction = nbi;
#ifndef __SYNTHESIS__
#ifdef DEBUG_REG_FILE
  print_reg(reg_file);
#endif
#endif
}
