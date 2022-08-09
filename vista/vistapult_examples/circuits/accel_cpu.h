#pragma once
#include "mgc_vista_schematics.h"
$includes_begin;
#include <systemc.h>
#include "../models/accel_bus_model.h"
#include "../models/Dense_model.h"
#include "../models/axi_mem_model.h"
#include "../models/riscv_model.h"
#include "../models/conv_2d_model.h"
#include "../models/console_out_model.h"
$includes_end;

$module_begin("accel_cpu");
SC_MODULE(accel_cpu) {
public:
  typedef accel_cpu SC_CURRENT_USER_MODULE;
  accel_cpu(::sc_core::sc_module_name name):
    ::sc_core::sc_module(name)
    $initialization_begin
$init("console"),
console(0)
$end
$init("axi_fabric"),
axi_fabric(0)
$end
$init("dense"),
dense(0)
$end
$init("riscv_cpu"),
riscv_cpu(0)
$end
$init("conv_2d"),
conv_2d(0)
$end
$init("code_and_data"),
code_and_data(0)
$end
$init("shared_memory"),
shared_memory(0)
$end
    $initialization_end
{
    $elaboration_begin;
$create_component("console");
console = new console_out_pvt("console");
$end;
$create_component("axi_fabric");
axi_fabric = new accel_bus_pvt("axi_fabric");
$end;
$create_component("dense");
dense = new Dense_pvt("dense");
$end;
$create_component("riscv_cpu");
riscv_cpu = new riscv_pvt("riscv_cpu");
$end;
$create_component("conv_2d");
conv_2d = new conv_2d_pvt("conv_2d");
$end;
$create_component("code_and_data");
code_and_data = new axi_mem_pvt("code_and_data");
$end;
$create_component("shared_memory");
shared_memory = new axi_mem_pvt("shared_memory");
$end;
$bind("conv_2d->master","axi_fabric->conv_2d_master");
vista_bind(conv_2d->master, axi_fabric->conv_2d_master);
$end;
$bind("axi_fabric->code_and_data","code_and_data->slave");
vista_bind(axi_fabric->code_and_data, code_and_data->slave);
$end;
$bind("conv_2d->int_out","riscv_cpu->irq_0");
vista_bind(conv_2d->int_out, riscv_cpu->irq_0);
$end;
$bind("riscv_cpu->master","axi_fabric->cpu_master");
vista_bind(riscv_cpu->master, axi_fabric->cpu_master);
$end;
$bind("axi_fabric->conv_2d_slave","conv_2d->slave");
vista_bind(axi_fabric->conv_2d_slave, conv_2d->slave);
$end;
$bind("dense->master","axi_fabric->dense_master");
vista_bind(dense->master, axi_fabric->dense_master);
$end;
$bind("axi_fabric->console","console->slave");
vista_bind(axi_fabric->console, console->slave);
$end;
$bind("axi_fabric->shared_memory","shared_memory->slave");
vista_bind(axi_fabric->shared_memory, shared_memory->slave);
$end;
$bind("axi_fabric->dense_slave","dense->slave");
vista_bind(axi_fabric->dense_slave, dense->slave);
$end;
    $elaboration_end;
  $vlnv_assign_begin;
m_library = "circuits";
m_vendor = "Mentor.com";
m_version = "1.0";
  $vlnv_assign_end;
  }
  ~accel_cpu() {
    $destructor_begin;
$destruct_component("console");
delete console; console = 0;
$end;
$destruct_component("axi_fabric");
delete axi_fabric; axi_fabric = 0;
$end;
$destruct_component("dense");
delete dense; dense = 0;
$end;
$destruct_component("riscv_cpu");
delete riscv_cpu; riscv_cpu = 0;
$end;
$destruct_component("conv_2d");
delete conv_2d; conv_2d = 0;
$end;
$destruct_component("code_and_data");
delete code_and_data; code_and_data = 0;
$end;
$destruct_component("shared_memory");
delete shared_memory; shared_memory = 0;
$end;
    $destructor_end;
  }
public:
  $fields_begin;
$component("console");
console_out_pvt *console;
$end;
$component("axi_fabric");
accel_bus_pvt *axi_fabric;
$end;
$component("dense");
Dense_pvt *dense;
$end;
$component("riscv_cpu");
riscv_pvt *riscv_cpu;
$end;
$component("conv_2d");
conv_2d_pvt *conv_2d;
$end;
$component("code_and_data");
axi_mem_pvt *code_and_data;
$end;
$component("shared_memory");
axi_mem_pvt *shared_memory;
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

