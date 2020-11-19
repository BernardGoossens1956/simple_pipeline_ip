#include "simple_pipeline_ip.h"

void new_cycle(
  fetch_decode_stage_t fetch_out,
  fetch_decode_stage_t *execute_in){
#pragma HLS INLINE off
  *execute_in = fetch_out;
}
