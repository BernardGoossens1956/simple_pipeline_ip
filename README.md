# simple_pipeline_ip
An IP to implement a 2-stage pipeline to run the RV32I ISA (runnable on a Xilinx FPGA, e.g. as on the Pynq-Z1 development board).

The implemented processor is pipelined. The pipeline has two stages: fetch+decode, execute+write back.

The code files are structured as in a vitis_hls (Xilinx High Level Synthesis) project.

The "simple_pipeline_ip.c" file contains the IP main function "simple_pipeline_ip()".

The "testbench_simple_pipeline_ip.c" file contains the "main" function to test the IP within the vitis_hls tool.

The "helloworld.c" file contains another "main" function to run the IP on a FPGA based development board.

The "test_...dump.h" files contain the hexadecimal encoding of a set of RISC-V programs to serve as data for the "simple_pipeline_ip" IP. Every program dumps the processor registers state at the end of the run.

The "vitis_hls.txt" file contains the prints after the runs of the IP on the "test_...dump.h" examples in the vitis_hls tool (print of the "main" function in the "testbench_simple_pipeline_ip.c" file).

The "pynq_z1.txt" file contains the print after the run of the IP on the "test_mem_dump.h" example on a Pynq-Z1 development board (print of the "main" function in the "helloworld.c" file).

Complementary informations are available in the book "A RISC-V processor with High Level Synthesis ; a Do-It-Yourself approach", Bernard Goossens.

The IP is composed of two units, each implementing a stage of the pipeline.
