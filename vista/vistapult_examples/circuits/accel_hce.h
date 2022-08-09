#pragma once
#include "mgc_vista_schematics.h"
$includes_begin;
#include <systemc.h>
#include "../models/accel_bus_model.h"
#include "../models/Dense_model.h"
#include "../models/axi_mem_model.h"
#include "../models/conv_2d_model.h"
#include "../models/console_out_model.h"
#include "../models/hce_cpu_model.h"
$includes_end;

$module_begin("accel_hce");
SC_MODULE(accel_hce) {
public:
  typedef accel_hce SC_CURRENT_USER_MODULE;
  accel_hce(::sc_core::sc_module_name name):
    ::sc_core::sc_module(name)
    $initialization_begin
$init("console"),
console(0)
$end
$init("riscv_cpu"),
riscv_cpu(0)
$end
$init("shared_mem"),
shared_mem(0)
$end
$init("conv_2d_accel"),
conv_2d_accel(0)
$end
$init("dense_accel"),
dense_accel(0)
$end
$init("axi_bus"),
axi_bus(0)
$end
$init("code_and_data"),
code_and_data(0)
$end
    $initialization_end
{
    $elaboration_begin;
$create_component("console");
console = new console_out_pvt("console");
$end;
$create_component("riscv_cpu");
riscv_cpu = new hce_cpu_pvt("riscv_cpu");
$end;
$create_component("shared_mem");
shared_mem = new axi_mem_pvt("shared_mem");
$end;
$create_component("conv_2d_accel");
conv_2d_accel = new conv_2d_pvt("conv_2d_accel");
$end;
$create_component("dense_accel");
dense_accel = new Dense_pvt("dense_accel");
$end;
$create_component("axi_bus");
axi_bus = new accel_bus_pvt("axi_bus");
$end;
$create_component("code_and_data");
code_and_data = new axi_mem_pvt("code_and_data");
$end;
$bind("conv_2d_accel->master","axi_bus->conv_2d_master");
vista_bind(conv_2d_accel->master, axi_bus->conv_2d_master);
$end;
$bind("conv_2d_accel->int_out","riscv_cpu->int_0");
vista_bind(conv_2d_accel->int_out, riscv_cpu->int_0);
$end;
$bind("axi_bus->console","console->slave");
vista_bind(axi_bus->console, console->slave);
$end;
$bind("dense_accel->int_out","riscv_cpu->int_1");
vista_bind(dense_accel->int_out, riscv_cpu->int_1);
$end;
$bind("axi_bus->dense_slave","dense_accel->slave");
vista_bind(axi_bus->dense_slave, dense_accel->slave);
$end;
$bind("axi_bus->conv_2d_slave","conv_2d_accel->slave");
vista_bind(axi_bus->conv_2d_slave, conv_2d_accel->slave);
$end;
$bind("axi_bus->shared_memory","shared_mem->slave");
vista_bind(axi_bus->shared_memory, shared_mem->slave);
$end;
$bind("dense_accel->master","axi_bus->dense_master");
vista_bind(dense_accel->master, axi_bus->dense_master);
$end;
$bind("riscv_cpu->cpu_master","axi_bus->cpu_master");
vista_bind(riscv_cpu->cpu_master, axi_bus->cpu_master);
$end;
$bind("axi_bus->code_and_data","code_and_data->slave");
vista_bind(axi_bus->code_and_data, code_and_data->slave);
$end;
    $elaboration_end;
  $vlnv_assign_begin;
m_library = "circuits";
m_vendor = "Mentor.com";
m_version = "1.0";
  $vlnv_assign_end;
  }
  ~accel_hce() {
    $destructor_begin;
$destruct_component("console");
delete console; console = 0;
$end;
$destruct_component("riscv_cpu");
delete riscv_cpu; riscv_cpu = 0;
$end;
$destruct_component("shared_mem");
delete shared_mem; shared_mem = 0;
$end;
$destruct_component("conv_2d_accel");
delete conv_2d_accel; conv_2d_accel = 0;
$end;
$destruct_component("dense_accel");
delete dense_accel; dense_accel = 0;
$end;
$destruct_component("axi_bus");
delete axi_bus; axi_bus = 0;
$end;
$destruct_component("code_and_data");
delete code_and_data; code_and_data = 0;
$end;
    $destructor_end;
  }
public:
  $fields_begin;
$component("console");
console_out_pvt *console;
$end;
$component("riscv_cpu");
hce_cpu_pvt *riscv_cpu;
$end;
$component("shared_mem");
axi_mem_pvt *shared_mem;
$end;
$component("conv_2d_accel");
conv_2d_pvt *conv_2d_accel;
$end;
$component("dense_accel");
Dense_pvt *dense_accel;
$end;
$component("axi_bus");
accel_bus_pvt *axi_bus;
$end;
$component("code_and_data");
axi_mem_pvt *code_and_data;
$end;
  $fields_end;
  $vlnv_decl_begin;
public:
const char* m_library;
const char* m_vendor;
const char* m_version;
  $vlnv_decl_end;
};
$module_end;

