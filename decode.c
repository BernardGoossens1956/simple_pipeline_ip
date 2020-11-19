#include "simple_pipeline_ip.h"
#include "type.h"
#include "immediate.h"

void decode(
  instruction_t instruction,
  decoded_instruction_t *decoded_instruction){
#pragma HLS INLINE
  decoded_instruction->inst_31    = (instruction >> 31);
  decoded_instruction->inst_30_25 = (instruction >> 25);
  decoded_instruction->inst_24_21 = (instruction >> 21);
  decoded_instruction->inst_20    = (instruction >> 20);
  decoded_instruction->inst_19_12 = (instruction >> 12);
  decoded_instruction->inst_11_8  = (instruction >>  8);
  decoded_instruction->inst_7     = (instruction >>  7);
  decoded_instruction->inst_6_2   = (instruction >>  2);
  decoded_instruction->opcode     = (instruction >>  2);
  decoded_instruction->inst_1_0   = (instruction      );
  decoded_instruction->rd         = (instruction >>  7);
  decoded_instruction->func3      = (instruction >> 12);
  decoded_instruction->rs1        = (instruction >> 15);
  decoded_instruction->rs2        = (instruction >> 20);
  decoded_instruction->func7      = (instruction >> 25);
  decoded_instruction->is_load    = 
                  (decoded_instruction->opcode == LOAD);
  decoded_instruction->is_store   =
                  (decoded_instruction->opcode == STORE);
  decoded_instruction->is_branch  =
                  (decoded_instruction->opcode == BRANCH);
  decoded_instruction->is_jal     =
                  (decoded_instruction->opcode == JAL);
  decoded_instruction->is_jalr    =
                  (decoded_instruction->opcode == JALR);
  decoded_instruction->is_ret     = (instruction == RET);
  decoded_instruction->is_lui     =
                  (decoded_instruction->opcode == LUI);
  decoded_instruction->is_op_imm  =
                  (decoded_instruction->opcode == OP_IMM);
  decoded_instruction->is_system  =
                  (decoded_instruction->opcode == SYSTEM);
  decoded_instruction->is_jump    =
                  (decoded_instruction->is_jal ||
                   decoded_instruction->is_jalr);
  decoded_instruction->is_ctrl    =
                  (decoded_instruction->is_branch ||
                   decoded_instruction->is_jump);
  decoded_instruction->opch       =
                   decoded_instruction->opcode>>3;
  decoded_instruction->opcl       =
                   decoded_instruction->opcode;
  decoded_instruction->type       =
              type(decoded_instruction->opch,
                   decoded_instruction->opcl);
  switch(decoded_instruction->type){
    case UNDEFINED_TYPE: decoded_instruction->imm = 0;
                         break;
    case R_TYPE:         decoded_instruction->imm = 0;
                         break;
    case I_TYPE:         decoded_instruction->imm =
                           i_immediate(decoded_instruction);
                         break;
    case S_TYPE:         decoded_instruction->imm =
                           s_immediate(decoded_instruction);
                         break;
    case B_TYPE:         decoded_instruction->imm =
                           b_immediate(decoded_instruction);
                         break;
    case U_TYPE:         decoded_instruction->imm =
                           u_immediate(decoded_instruction);
                         break;
    case J_TYPE:         decoded_instruction->imm =
                           j_immediate(decoded_instruction);
                         break;
    case OTHER_TYPE:     decoded_instruction->imm = 0;
                         break;
  }
}
