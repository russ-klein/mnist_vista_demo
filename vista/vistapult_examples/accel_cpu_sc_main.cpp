//v2: comments beginning with v2 are generated and used by V2
//v2: please don't remove or modify these comments

//v2: begin of includes section
#include "accel_cpu.h"
//v2: end of includes section

int sc_main(int argc, char *argv[]) {

//v2: begin of channel declarations section
//v2: end of channel declarations section


//v2: begin of instantiations section
//v2: instance inst_accel_cpu - instance number 0 of module accel_cpu
accel_cpu *inst_accel_cpu = new accel_cpu("accel_cpu");
//v2: end of instantiations section


//v2: begin of ports assignment section
//v2: ports assignment for instance inst_accel_cpu
//v2: end of ports assignment section

 sc_start();

//v2: begin of instantiations section
delete inst_accel_cpu;
//v2: end of instantiations section

 return 0;
}
