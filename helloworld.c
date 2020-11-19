#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

unsigned int *pc       =
  (unsigned int *)(0x40000000
               +   0x10   );
unsigned int *code_mem =
  (unsigned int *)(0x40000000
               +   0x1000   );
char         *data_mem_0 =
  (        char *)(0x40000000
               +   0x400  );
char         *data_mem_1 =
  (        char *)(0x40000000
               +   0x800  );
char         *data_mem_2 =
  (        char *)(0x40000000
               +   0xc00  );
char         *data_mem_3 =
  (        char *)(0x40000000
               +   0x2000 );
unsigned int *nbi      =
  (unsigned int *)(0x40000000
               +   0x18);

unsigned int code_memory[64]=
{
  0x00000513,
  0x00000593,
  0x00000613,
  0x02860693,
  0x00158593,
  0x00b62023,
  0x00460613,
  0xfed61ae3,
  0x00000593,
  0x00000613,
  0x00062703,
  0x00e50533,
  0x00460613,
  0xfed61ae3,
  0x00008067
};

int main()
{
  unsigned int i;
  char c0, c1, c2, c3;
  int w;
  pc[0] = 0;
  pc[1] = 0;
  for (i=0; i<64; i++)
    code_mem[i] = code_memory[i];

  init_platform();

  while (pc[1]==0);
  print("pc ");
  xil_printf("%d", pc[1]);
  print("\n\r");
  print("nb instructions ");
  xil_printf("%d", *nbi);
  print("\n\r");
  for (i=0; i<16; i++){
    c0 = data_mem_0[i];
    c1 = data_mem_1[i];
    c2 = data_mem_2[i];
    c3 = data_mem_3[i];
    w = (c3<<24) | (c2<<16) | (c1<<8) | c0;
    if (w != 0){
      print("m[");
      xil_printf("%2d", i);
      print("] = ");
      xil_printf("%10d", w);
      print("\n\r");
    }
  }

  cleanup_platform();
  return 0;
}
