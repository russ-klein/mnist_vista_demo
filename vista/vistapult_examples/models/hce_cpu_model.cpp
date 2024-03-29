
/**************************************************************/
/*                                                            */
/*               Copyright (c) Siemens 2021                   */
/*                  All Rights Reserved                       */
/*                                                            */
/*       THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY      */
/*         INFORMATION WHICH IS THE PROPERTY OF SIEMENS       */
/*             CORPORATION OR ITS LICENSORS AND IS            */
/*                 SUBJECT TO LICENSE TERMS.                  */
/*                                                            */
/**************************************************************/

//*<
//* Generated By Model Builder, Mentor Graphics Computer Systems, Inc.
//*
//* This file is write protected. 
//* DO NOT MODIFY THIS FILE.
//*
//* This file is generated according to the parameters in the 
//* Model Builder form.
//* This class contains the infrastructure to define the behavior of the component.
//* The hce_cpu_pv will be derived from this class.
//*
//* Model Builder version: 5.1.0
//* Generated on: Jul. 21, 2022 11:14:14 AM, (user: russk)
//*>


#include "hce_cpu_model.h"

#ifdef MODEL_BUILDER_VERSION_NUMBER
#if 5100 != MODEL_BUILDER_VERSION_NUMBER
#error "This model was generated using Model Builder version: 5.1.0. Please regenerate model."
#endif
#else
#error "Please regenerate model."
#endif

using namespace sc_core;
using namespace sc_dt;
using namespace std;



hce_cpu_pv_base::hce_cpu_pv_base(sc_module_name& module_name) :
  hce_cpu_pv_base_mb_compatibility(module_name),
  hce_cpu_pv_base_parameters(this),
  VISTA_MB_PV_INIT_MEMBER(cpu_master),
  VISTA_MB_PV_INIT_MEMBER(int_0),
  VISTA_MB_PV_INIT_MEMBER(int_1) {
  
  


  // cpu_master - not a vector port
  // int_0 - not a vector port
  // int_1 - not a vector port
  unsigned u = 0;



  payload_on_stack = 0;
  payload_for_token = 0;
  reset_registers();
  
  // reset value for output signals

  // reset value for input signals

  // int_0 reset value not defined
  int_0.register_cb(this, &self::cb_signal_int_0);
  // int_1 reset value not defined
  int_1.register_cb(this, &self::cb_signal_int_1);
  // cpu_master bw binding 
  VISTA_MB_PV_BIND_BW_PROCESS_TO_MASTER(cpu_master);
  // cpu_master bw callbacks 
  VISTA_MB_PV_REGISTER_SELF_BW_PROCESS_CALLBACKS(cpu_master);

}


hce_cpu_pv_base::~hce_cpu_pv_base() {
  
}



void hce_cpu_pv_base::reset_registers() {
  // reset all registers
  unsigned u = 0;


}


void hce_cpu_pv_base::reset_model() {
  
  reset_registers();
  // reset value for output signals

  // reset value for input signals

  // int_0 reset value not defined
  // int_1 reset value not defined


}

hce_cpu_pv_base_parameters::hce_cpu_pv_base_parameters(sc_object* object) :
  m_object(object),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, clock, sc_core::sc_time(10, sc_core::SC_NS), "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, signal_clock, clock, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, axi_clock, clock, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, nominal_voltage, 1, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, port_enable, true, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, verbose_parameters, true, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, dmi_enabled, true, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, warning_level, "WARNING", "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, cpu_master_outstanding, 1, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, cpu_master_read_data_queue_size, 0, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, cpu_master_write_data_queue_size, 0, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, int_0_pipeline_length, 2, "hce_cpu"),
  SD_INITIALIZE_PARAMETER_EXTERNALLY(object, int_1_pipeline_length, 2, "hce_cpu")
{
  if(verbose_parameters) print_parameters();
}

void hce_cpu_pv_base_parameters::print_parameters()
{
  const char* name;
  if (!strcmp(m_object->basename(), "PV"))
    name = m_object->get_parent_object()->name();
  else
    name = m_object->name();

  std::cout.setf(ios::hex, ios::basefield);
  std::cout.setf(ios::showbase);
  std::cout << name << "::parameters:\n";
  std::cout << "\tclock = " << clock << "\n";
  std::cout << "\tsignal_clock = " << signal_clock << "\n";
  std::cout << "\taxi_clock = " << axi_clock << "\n";
  std::cout << "\tnominal_voltage = " << nominal_voltage << "\n";
  std::cout << "\tport_enable = " << port_enable << "\n";
  std::cout << "\tverbose_parameters = " << verbose_parameters << "\n";
  std::cout << "\tdmi_enabled = " << dmi_enabled << "\n";
  std::cout << "\twarning_level = " << warning_level << "\n";
  std::cout << "\tcpu_master_outstanding = " << cpu_master_outstanding << "\n";
  std::cout << "\tcpu_master_read_data_queue_size = " << cpu_master_read_data_queue_size << "\n";
  std::cout << "\tcpu_master_write_data_queue_size = " << cpu_master_write_data_queue_size << "\n";
  std::cout << "\tint_0_pipeline_length = " << int_0_pipeline_length << "\n";
  std::cout << "\tint_1_pipeline_length = " << int_1_pipeline_length << "\n";
  std::cout.unsetf(ios::showbase);
  std::cout.setf(ios::dec, ios::basefield);
  std::cout << std::endl;
}





/**************************************************************/
/*                                                            */
/*               Copyright (c) Siemens 2021                   */
/*                  All Rights Reserved                       */
/*                                                            */
/*       THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY      */
/*         INFORMATION WHICH IS THE PROPERTY OF SIEMENS       */
/*             CORPORATION OR ITS LICENSORS AND IS            */
/*                 SUBJECT TO LICENSE TERMS.                  */
/*                                                            */
/**************************************************************/

//*<
//* Generated By Model Builder, Mentor Graphics Computer Systems, Inc.
//*
//* This file is write protected. 
//* DO NOT MODIFY THIS FILE.
//*
//* This file is generated according to the parameters in the 
//* Model Builder form.
//* 
//* Any change in parameters, policies, ports, protocols, etc. will change this file
//* upon generation of the timing model (using generate_timing_model command).
//* The hce_cpu_t will be derived from this class.
//*
//* Model Builder version: 5.1.0
//* Generated on: Jul. 21, 2022 11:14:15 AM, (user: russk)
//*>




#include "hce_cpu_model.h"
#include <math.h>
#include <stdlib.h>

using namespace esl::tlm_sim;
using namespace esl::sc_sim;
using namespace std;
using namespace sc_dt;
using namespace sc_core;




void hce_cpu_t_base::schedule_axi_READ
(long port_index,
 sc_dt::uint64 delay,
 long& transactionSize,
 esl::include::transaction_power& power , long TR_ID, long ARADDR, long* RDATA, long ARSIZE, long block_size, long ARBURST, long ARLEN, long ARLOCK) {
  sc_dt::uint64 local_address = 0;
  local_address = ARADDR,
  scheduleGenericTransaction(port_index,
                             0,
                             local_address,
                             (unsigned char*)RDATA,
                             transactionSize,
                             block_size,
                             0, papoulis::getSimulationTime() + delay,
                             0,
                             0);
}



void hce_cpu_t_base::schedule_axi_WRITE
(long port_index,
 sc_dt::uint64 delay,
 long& transactionSize,
 esl::include::transaction_power& power , long TR_ID, long AWADDR, long* WDATA, long AWSIZE, long block_size, long AWBURST, long AWLEN, long AWLOCK) {
  sc_dt::uint64 local_address = 0;
  local_address = AWADDR,
  scheduleGenericTransaction(port_index,
                             1,
                             local_address,
                             (unsigned char*)WDATA,
                             transactionSize,
                             block_size,
                             0, papoulis::getSimulationTime() + delay,
                             0,
                             0);
}




void hce_cpu_t_base::start_transaction_axi_READ
(esl::include::TRequest* request,
 unsigned port_index,
 sc_dt::uint64 startTime,
 sc_dt::uint64 endTime,
 sc_dt::uint64* parameters,
 bool hasBeenError) {
  
  long burstSize = request->getSize();
  parameters[1] = request->getAddress();
  parameters[2] = request->getFirstDataBlock();
  parameters[4] = request->getBlockSize();
  
  
  this->accept_axi_READ
    (port_index, 
     startTime, 
     burstSize, 
     parameters[0], 
     parameters[1], 
     parameters[2], 
     parameters[3], 
     parameters[4], 
     parameters[5], 
     parameters[6], 
     parameters[7]);
}


void hce_cpu_t_base::end_transaction_axi_READ
(esl::include::TRequest* request,
 unsigned port_index,
 sc_dt::uint64 startTime,
 sc_dt::uint64 endTime,
 sc_dt::uint64* parameters,
 bool hasBeenError) {
  long burstSize = request->getSize();
  parameters[1] = request->getAddress();
  parameters[2] = request->getFirstDataBlock();
  parameters[4] = request->getBlockSize();                                                                         
  
  this->end_axi_READ
    (port_index,
     endTime,
     burstSize,
     parameters[0],
     parameters[1],
     parameters[2],
     parameters[3],
     parameters[4],
     parameters[5],
     parameters[6],
     parameters[7]);
}

void hce_cpu_t_base::start_transaction_axi_WRITE
(esl::include::TRequest* request,
 unsigned port_index,
 sc_dt::uint64 startTime,
 sc_dt::uint64 endTime,
 sc_dt::uint64* parameters,
 bool hasBeenError) {
  
  long burstSize = request->getSize();
  parameters[1] = request->getAddress();
  parameters[2] = request->getFirstDataBlock();
  parameters[4] = request->getBlockSize();
  
  
  this->accept_axi_WRITE
    (port_index, 
     startTime, 
     burstSize, 
     parameters[0], 
     parameters[1], 
     parameters[2], 
     parameters[3], 
     parameters[4], 
     parameters[5], 
     parameters[6], 
     parameters[7]);
}


void hce_cpu_t_base::end_transaction_axi_WRITE
(esl::include::TRequest* request,
 unsigned port_index,
 sc_dt::uint64 startTime,
 sc_dt::uint64 endTime,
 sc_dt::uint64* parameters,
 bool hasBeenError) {
  long burstSize = request->getSize();
  parameters[1] = request->getAddress();
  parameters[2] = request->getFirstDataBlock();
  parameters[4] = request->getBlockSize();                                                                         
  
  this->end_axi_WRITE
    (port_index,
     endTime,
     burstSize,
     parameters[0],
     parameters[1],
     parameters[2],
     parameters[3],
     parameters[4],
     parameters[5],
     parameters[6],
     parameters[7]);
}

void hce_cpu_t_base::start_transaction_signal_WRITE
(esl::include::TRequest* request,
 unsigned port_index,
 sc_dt::uint64 startTime,
 sc_dt::uint64 endTime,
 sc_dt::uint64* parameters,
 bool hasBeenError) {
  
  long burstSize = request->getSize();
  parameters[0] = request->getAddress();
  parameters[1] = request->getFirstDataBlock();
  parameters[2] = request->getBlockSize();
  
  
  this->accept_signal_WRITE
    (port_index, 
     startTime, 
     burstSize, 
     parameters[0], 
     parameters[1], 
     parameters[2]);
}


void hce_cpu_t_base::end_transaction_signal_WRITE
(esl::include::TRequest* request,
 unsigned port_index,
 sc_dt::uint64 startTime,
 sc_dt::uint64 endTime,
 sc_dt::uint64* parameters,
 bool hasBeenError) {
  long burstSize = request->getSize();
  parameters[0] = request->getAddress();
  parameters[1] = request->getFirstDataBlock();
  parameters[2] = request->getBlockSize();                                                                         
  
  this->end_signal_WRITE
    (port_index,
     endTime,
     burstSize,
     parameters[0],
     parameters[1],
     parameters[2]);
}

 hce_cpu_t_base::TransactionCallbackFunctionPointer hce_cpu_t_base::getTransactionCallback(unsigned callbackIndex) {
  static TransactionCallbackFunctionPointer funcArray[] = {
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::start_transaction_axi_READ),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::start_transaction_axi_WRITE),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::null_transaction_callback),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::start_transaction_signal_WRITE),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::null_transaction_callback),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::start_transaction_signal_WRITE),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::end_transaction_axi_READ),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::end_transaction_axi_WRITE),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::null_transaction_callback),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::end_transaction_signal_WRITE),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::null_transaction_callback),
    static_cast<TransactionCallbackFunctionPointer>(&hce_cpu_t_base::end_transaction_signal_WRITE),
    0
  };
  if(callbackIndex >= sizeof(funcArray) / sizeof(*funcArray) - 1)
    return 0;
  return funcArray[callbackIndex];
}


config::real80 hce_cpu_t_base::get_state_power() {
  config::real80 power_value = 0;

  

  return power_value;
}


hce_cpu_t_base::hce_cpu_t_base(sc_module_name& module_name, long simulation) :
  papoulis::SystemCBaseModel(module_name),
  SD_INITIALIZE_PARAMETER(clock, sc_core::sc_time(10, sc_core::SC_NS), "hce_cpu"),
  SD_INITIALIZE_PARAMETER(signal_clock, clock, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(axi_clock, clock, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(nominal_voltage, 1, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(port_enable, true, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(verbose_parameters, true, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(dmi_enabled, true, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(warning_level, "WARNING", "hce_cpu"),
  SD_INITIALIZE_PARAMETER(cpu_master_outstanding, 1, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(cpu_master_read_data_queue_size, 0, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(cpu_master_write_data_queue_size, 0, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(int_0_pipeline_length, 2, "hce_cpu"),
  SD_INITIALIZE_PARAMETER(int_1_pipeline_length, 2, "hce_cpu"),
  m_simulation(simulation)
{
  bool separate_read_channel = false;  
  bool separate_write_channel = false;
  char* buffer = 0;
  unsigned port_index = 0;
  
  fix_clock_parameter(axi_clock, "axi_clock");
    separate_read_channel = false;
    separate_write_channel = false;
    buffer = new char[20];
    sprintf(buffer, "cpu_master");
    port_index = cpu_master;
    port_descriptions[port_index].port_name = buffer;
    separate_read_channel = true;
    port_descriptions[port_index].port_kind = PortDescription::READ_CHANNEL_PORT;
    separate_write_channel = true;
    port_descriptions[port_index].port_kind = PortDescription::WRITE_CHANNEL_PORT;
    if (separate_write_channel && separate_read_channel)
      port_descriptions[port_index].port_kind = PortDescription::SEPARATE_READ_WRIE_CHANNEL_PORT;
    port_descriptions[port_index].is_read_write_address_channel = 0;
    
    port_descriptions[port_index].is_master_port = 1;
    port_descriptions[port_index].is_signal_port = 0;
    port_descriptions[port_index].port_width = ((32 + 7) >> 3);
    port_descriptions[port_index].port_cast  = 0;
    port_descriptions[port_index].port_width_in_bits = 32;
    port_descriptions[port_index].protocol_name = "axi";
    port_descriptions[port_index].ipxactBusDef.vendor = "amba.com";
    port_descriptions[port_index].ipxactBusDef.library = "AMBA3";
    port_descriptions[port_index].ipxactBusDef.name = "AXI";
    port_descriptions[port_index].ipxactBusDef.version = "r1p0_5"; 
    port_descriptions[port_index].ipxactAbstrDef.vendor = "Mentor.com";
    port_descriptions[port_index].ipxactAbstrDef.library = "Lib_ipxact";
    port_descriptions[port_index].ipxactAbstrDef.name = "AXI_tlm20";
    port_descriptions[port_index].ipxactAbstrDef.version = "1.0";
    port_descriptions[port_index].port_must_bind = 1;
    port_descriptions[port_index].params_count = 8 + 10;
    if (cpu_master_outstanding == 0) {
      cpu_master_outstanding = 1;
      printf("WARNING: in \"%s\" the \"cpu_master_outstanding\" parameter is 0, a default value of 1 is used\n", name());
    }
    port_descriptions[port_index].pending = cpu_master_outstanding;
    port_descriptions[port_index].read_data_queue_size = cpu_master_read_data_queue_size;
    port_descriptions[port_index].write_data_queue_size = cpu_master_write_data_queue_size;
    port_descriptions[port_index].clock = axi_clock;
    port_descriptions[port_index].add_read_phase(tlm::tlm_phase(tlm::BEGIN_REQ), !1, 0);
    port_descriptions[port_index].add_read_phase(tlm::tlm_phase(tlm::END_REQ), !0, 0);
    port_descriptions[port_index].add_read_phase(tlm::tlm_phase(tlm::BEGIN_RESP), !0, 1);
    port_descriptions[port_index].add_read_phase(tlm::tlm_phase(tlm::END_RESP), !1, 1);
    port_descriptions[port_index].add_write_phase(tlm::tlm_phase(tlm::BEGIN_REQ), !1, 0);
    port_descriptions[port_index].add_write_phase(tlm::tlm_phase(tlm::END_REQ), !0, 0);
    port_descriptions[port_index].add_write_phase(tlm::tlm_phase(tlm::BEGIN_RESP), !0, 1);
    port_descriptions[port_index].add_write_phase(tlm::tlm_phase(tlm::END_RESP), !1, 1);
  
  
  fix_clock_parameter(signal_clock, "signal_clock");
    separate_read_channel = false;
    separate_write_channel = false;
    buffer = new char[15];
    sprintf(buffer, "int_0");
    port_index = int_0;
    port_descriptions[port_index].port_name = buffer;
    separate_write_channel = true;
    port_descriptions[port_index].port_kind = PortDescription::WRITE_CHANNEL_PORT;
    if (separate_write_channel && separate_read_channel)
      port_descriptions[port_index].port_kind = PortDescription::SEPARATE_READ_WRIE_CHANNEL_PORT;
    port_descriptions[port_index].is_read_write_address_channel = 0;
    
    port_descriptions[port_index].is_master_port = 0;
    port_descriptions[port_index].is_signal_port = 1;
    port_descriptions[port_index].port_width = ((1 + 7) >> 3);
    port_descriptions[port_index].port_cast  = 0;
    port_descriptions[port_index].port_width_in_bits = 1;
    port_descriptions[port_index].protocol_name = "signal";
    port_descriptions[port_index].ipxactBusDef.vendor = "Mentor.com";
    port_descriptions[port_index].ipxactBusDef.library = "Lib_ipxact";
    port_descriptions[port_index].ipxactBusDef.name = "signal";
    port_descriptions[port_index].ipxactBusDef.version = "1.0"; 
    port_descriptions[port_index].ipxactAbstrDef.vendor = "Mentor.com";
    port_descriptions[port_index].ipxactAbstrDef.library = "Lib_ipxact";
    port_descriptions[port_index].ipxactAbstrDef.name = "signal_tlm20";
    port_descriptions[port_index].ipxactAbstrDef.version = "1.0";
    port_descriptions[port_index].port_must_bind = 1;
    port_descriptions[port_index].params_count = 3 + 10;
    port_descriptions[port_index].clock = signal_clock;
    port_descriptions[port_index].add_write_phase(tlm::tlm_phase(tlm::BEGIN_REQ), !0, 1);
    port_descriptions[port_index].add_write_phase(tlm::tlm_phase(tlm::BEGIN_RESP), !1, 1);
  
  
  fix_clock_parameter(signal_clock, "signal_clock");
    separate_read_channel = false;
    separate_write_channel = false;
    buffer = new char[15];
    sprintf(buffer, "int_1");
    port_index = int_1;
    port_descriptions[port_index].port_name = buffer;
    separate_write_channel = true;
    port_descriptions[port_index].port_kind = PortDescription::WRITE_CHANNEL_PORT;
    if (separate_write_channel && separate_read_channel)
      port_descriptions[port_index].port_kind = PortDescription::SEPARATE_READ_WRIE_CHANNEL_PORT;
    port_descriptions[port_index].is_read_write_address_channel = 0;
    
    port_descriptions[port_index].is_master_port = 0;
    port_descriptions[port_index].is_signal_port = 1;
    port_descriptions[port_index].port_width = ((1 + 7) >> 3);
    port_descriptions[port_index].port_cast  = 0;
    port_descriptions[port_index].port_width_in_bits = 1;
    port_descriptions[port_index].protocol_name = "signal";
    port_descriptions[port_index].ipxactBusDef.vendor = "Mentor.com";
    port_descriptions[port_index].ipxactBusDef.library = "Lib_ipxact";
    port_descriptions[port_index].ipxactBusDef.name = "signal";
    port_descriptions[port_index].ipxactBusDef.version = "1.0"; 
    port_descriptions[port_index].ipxactAbstrDef.vendor = "Mentor.com";
    port_descriptions[port_index].ipxactAbstrDef.library = "Lib_ipxact";
    port_descriptions[port_index].ipxactAbstrDef.name = "signal_tlm20";
    port_descriptions[port_index].ipxactAbstrDef.version = "1.0";
    port_descriptions[port_index].port_must_bind = 1;
    port_descriptions[port_index].params_count = 3 + 10;
    port_descriptions[port_index].clock = signal_clock;
    port_descriptions[port_index].add_write_phase(tlm::tlm_phase(tlm::BEGIN_REQ), !0, 1);
    port_descriptions[port_index].add_write_phase(tlm::tlm_phase(tlm::BEGIN_RESP), !1, 1);
  

  port_descriptions[cpu_master].default_read_transaction_name = "READ";
  
  port_descriptions[cpu_master].default_write_transaction_name = "WRITE";
  
  port_descriptions[int_0].default_write_transaction_name = "WRITE";
  
  port_descriptions[int_1].default_write_transaction_name = "WRITE";
  

  fix_internal_clock_parameter(clock, "clock");
  set_ports(mb::sysc::sc_time_to_ps(clock), port_count, port_descriptions);

  bool isCpu = false;
  isCpu = true;
  esl::tlm_sim::UserRunningModel* userRunningModel = Papoulis_CreateUserRunningModel(name(),
                                                                                     0,
                                                                                     this,
                                                                                     simulation,
                                                                                     false,
                                                                                     isCpu);
  setUserRunningModel(userRunningModel, isCpu);
  set_nominal_voltage(nominal_voltage);
  registerParameter("clock", "sc_core::sc_time", sdGetParameterAsConstString("clock"));
  registerParameter("signal_clock", "sc_core::sc_time", sdGetParameterAsConstString("signal_clock"));
  registerParameter("axi_clock", "sc_core::sc_time", sdGetParameterAsConstString("axi_clock"));
  registerParameter("nominal_voltage", "double", sdGetParameterAsConstString("nominal_voltage"));
  registerParameter("port_enable", "bool", sdGetParameterAsConstString("port_enable"));
  registerParameter("verbose_parameters", "bool", sdGetParameterAsConstString("verbose_parameters"));
  registerParameter("dmi_enabled", "bool", sdGetParameterAsConstString("dmi_enabled"));
  registerParameter("warning_level", "const char*", sdGetParameterAsConstString("warning_level"));
  registerParameter("cpu_master_outstanding", "unsigned int", sdGetParameterAsConstString("cpu_master_outstanding"));
  registerParameter("cpu_master_read_data_queue_size", "unsigned int", sdGetParameterAsConstString("cpu_master_read_data_queue_size"));
  registerParameter("cpu_master_write_data_queue_size", "unsigned int", sdGetParameterAsConstString("cpu_master_write_data_queue_size"));
  registerParameter("int_0_pipeline_length", "unsigned int", sdGetParameterAsConstString("int_0_pipeline_length"));
  registerParameter("int_1_pipeline_length", "unsigned int", sdGetParameterAsConstString("int_1_pipeline_length"));
  set_sync_all(0); 
  
  
  
  
  

  
  

  


  

  constant_global_power_policy* p = new constant_global_power_policy(userRunningModel);
  
  
  
  set_global_power_policy(p);
}


void hce_cpu_t_base::update_sync_all() {
  set_sync_all(0);
  
}


void hce_cpu_t_base::update_pipeline_parameters(esl::sc_sim::pipeline_policy* handle) {
  if (m_pipeline_vector.size() == 0)
    return;


}


void hce_cpu_t_base::update_sequential_parameters(esl::sc_sim::sequential_policy* handle) {
  if (m_sequential_vector.size() == 0)
    return;

}


void hce_cpu_t_base::update_delay_parameters(esl::sc_sim::delay_policy* handle) {
  if (m_delay_vector.size() == 0)
    return;

}


void hce_cpu_t_base::update_bus_parameters(esl::sc_sim::uniform_bus_policy* handle) {
  if (m_bus_vector.size() == 0)
    return;

}


void hce_cpu_t_base::update_power_parameters(esl::sc_sim::power_policy* handle) {
  if (m_power_vector.size() == 0)
    return;

}


void hce_cpu_t_base::update_state_power_parameters(esl::sc_sim::state_power_policy* handle) {
  if (m_state_power_vector.size() == 0)
    return;

}


void hce_cpu_t_base::update_global_power_parameters(esl::sc_sim::constant_global_power_policy* handle) {
  
  
  return;  
}


bool hce_cpu_t_base::triggerRegistersGotHit(unsigned portIndex, tlm::tlm_generic_payload& trans) {
  mb::utl::Segment<uint64_t> transactionRange(trans.get_address(), trans.get_address() + trans.get_data_length());

  return false;
}


bool hce_cpu_t_base::portHasRegisters(unsigned portIndex) {
  switch (portIndex) {

  }
  return false;
}




/**************************************************************/
/*                                                            */
/*               Copyright (c) Siemens 2021                   */
/*                  All Rights Reserved                       */
/*                                                            */
/*       THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY      */
/*         INFORMATION WHICH IS THE PROPERTY OF SIEMENS       */
/*             CORPORATION OR ITS LICENSORS AND IS            */
/*                 SUBJECT TO LICENSE TERMS.                  */
/*                                                            */
/**************************************************************/

//*<
//* Generated By Model Builder, Mentor Graphics Computer Systems, Inc.
//*
//* This file is write protected.
//* DO NOT MODIFY THIS FILE.
//*
//* This file contains the PVT class for hce_cpu.
//* It connects between the PV and T models.
//* Your top-level design should instantiate this model.
//* 
//* In order to synchronize the activty between the PV and the T models, every 
//* PV transaction is monitored and queued in the T sync ports.
//* Whenever a synchronization point is reached, the T models are executed and 
//* the corresponding T transactions are launched.
//* A synchronization point is reached whenever there is a wait statement on a testbench thread. 
//*
//* Model Builder version: 5.1.0
//* Generated on: Jul. 21, 2022 11:14:15 AM, (user: russk)
//*>

#include "hce_cpu_model.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;



#include "hce_cpu_pv.h"




// Constructor

hce_cpu_pvt::hce_cpu_pvt(sc_module_name module_name)
  : esl::sc_sim::PVTBaseModel(module_name, 1),
    hce_cpu_pvt_param_defaults(this->name()),
    cpu_master("cpu_master"),
    int_0("int_0"),
    int_1("int_1"),
    cpu_master_entry("unvisible_cpu_master_entry"),
  int_0_entry("unvisible_int_0_entry"),
  int_1_entry("unvisible_int_1_entry")
  

  ,m_cpu_master_nb_connector(*this),
    m_int_0_nb_connector(*this),
    m_int_1_nb_connector(*this)
  
    

{
  // cpu_master - not a vector port

  // int_0 - not a vector signal
  // int_1 - not a vector signal


  m_hce_cpu_t = hce_cpu_t_base::create_t("T", 1);
  m_hce_cpu_pv = new hce_cpu_pv("PV");
  bind();
}  


hce_cpu_pvt::hce_cpu_pvt(sc_module_name module_name, sc_core::sc_time clock_init, sc_core::sc_time signal_clock_init, sc_core::sc_time axi_clock_init, double nominal_voltage_init, bool port_enable_init, bool verbose_parameters_init, bool dmi_enabled_init, const char* warning_level_init, unsigned int cpu_master_outstanding_init, unsigned int cpu_master_read_data_queue_size_init, unsigned int cpu_master_write_data_queue_size_init, unsigned int int_0_pipeline_length_init, unsigned int int_1_pipeline_length_init)
  : esl::sc_sim::PVTBaseModel(module_name, 1),
  hce_cpu_pvt_param_defaults(this->name(), clock_init, signal_clock_init, axi_clock_init, nominal_voltage_init, port_enable_init, verbose_parameters_init, dmi_enabled_init, warning_level_init, cpu_master_outstanding_init, cpu_master_read_data_queue_size_init, cpu_master_write_data_queue_size_init, int_0_pipeline_length_init, int_1_pipeline_length_init),
    cpu_master("cpu_master"),
    int_0("int_0"),
    int_1("int_1"),
    cpu_master_entry("unvisible_cpu_master_entry"),
    int_0_entry("unvisible_int_0_entry"),
    int_1_entry("unvisible_int_1_entry")
    

    ,m_cpu_master_nb_connector(*this),
    m_int_0_nb_connector(*this),
    m_int_1_nb_connector(*this)
    
    
{

  // cpu_master - not a vector port
  // int_0 - not a vector signal
  // int_1 - not a vector signal
  


  m_hce_cpu_t = hce_cpu_t_base::create_t("T", 1);
  m_hce_cpu_pv = new hce_cpu_pv("PV");
  bind();
} 


hce_cpu_pvt::hce_cpu_pvt(sc_module_name module_name,  std::vector<std::pair<char*, unsigned int> > &change_parameters)
  : esl::sc_sim::PVTBaseModel(module_name, 1),
  hce_cpu_pvt_param_defaults(this->name(), change_parameters),
    cpu_master("cpu_master"),
    int_0("int_0"),
    int_1("int_1"),
    cpu_master_entry("unvisible_cpu_master_entry"),
    int_0_entry("unvisible_int_0_entry"),
    int_1_entry("unvisible_int_1_entry")
    

    ,m_cpu_master_nb_connector(*this),
    m_int_0_nb_connector(*this),
    m_int_1_nb_connector(*this)
    
{

  // cpu_master - not a vector port
  


  m_hce_cpu_t = hce_cpu_t_base::create_t("T", 1);
  m_hce_cpu_pv = new hce_cpu_pv("PV");
  bind();
} 


hce_cpu_pvt::~hce_cpu_pvt() {
  remove_pending_scenes();
  
  delete m_hce_cpu_t;
  
  delete m_hce_cpu_pv;
}





void hce_cpu_pvt::bind()
{
  /* connect pv to entry ports */
  
  
  getPV()->cpu_master.bind(cpu_master_entry);  
  int_0_entry(getPV()->int_0);
  int_1_entry(getPV()->int_1);

  /* set callbacks on external and entry ports */ 

  int_0.b_transport_cb.set(this, &self_type::b_transport_inside_int_0);

  int_1.b_transport_cb.set(this, &self_type::b_transport_inside_int_1);

  cpu_master_entry.b_transport_cb.set(this, &self_type::b_transport_outside_cpu_master);
  cpu_master_entry.transport_dbg_cb.set(this, &self_type::transport_dbg_outside_cpu_master);
  cpu_master_entry.get_direct_mem_ptr_cb.set(&cpu_master, &cpu_master_type::get_direct_mem_ptr);
  
  
  /* connect t non blocking callbacks */

  cpu_master.nb_transport_bw_cb.set(this, &self_type::receive_nb_transport_cpu_master);
  getT()->set_port_cb(0, &m_cpu_master_nb_connector);
  
  int_0.nb_transport_fw_cb.set(this, &self_type::receive_nb_transport_int_0);
  getT()->set_port_cb(1, &m_int_0_nb_connector);
  
  int_1.nb_transport_fw_cb.set(this, &self_type::receive_nb_transport_int_1);
  getT()->set_port_cb(2, &m_int_1_nb_connector);
  
  cpu_master.invalidate_direct_mem_ptr_cb.set(&cpu_master_entry, &cpu_master_entry_type::invalidate_direct_mem_ptr);
  
  /* check mb_event policies */
  m_hce_cpu_t->check_mb_events();
  
}



void hce_cpu_pvt::b_transport_inside_int_0(tlm::tlm_generic_payload& p, sc_core::sc_time& t)
{
  mb::tlm20::pvt_ext* extension = mb::tlm20::setup_pvt_ext(p);
  if (extension) {
    mb::mb_module* current_model = dynamic_cast<mb::mb_module*>(m_hce_cpu_pv);
    if (current_model)
      current_model->set_current_token(extension->getToken()); 
  }
 
  int_0_entry.write(*(bool*)p.get_data_ptr());

}

void hce_cpu_pvt::b_transport_inside_int_1(tlm::tlm_generic_payload& p, sc_core::sc_time& t)
{
  mb::tlm20::pvt_ext* extension = mb::tlm20::setup_pvt_ext(p);
  if (extension) {
    mb::mb_module* current_model = dynamic_cast<mb::mb_module*>(m_hce_cpu_pv);
    if (current_model)
      current_model->set_current_token(extension->getToken()); 
  }
 
  int_1_entry.write(*(bool*)p.get_data_ptr());

}


void hce_cpu_pvt::b_transport_outside_cpu_master(tlm::tlm_generic_payload& p, sc_core::sc_time& t)
{
  
  cpu_master.b_transport(p, t); 
} 


unsigned int hce_cpu_pvt::transport_dbg_outside_cpu_master(tlm::tlm_generic_payload& p)
{
  

  return cpu_master.transport_dbg(p); 
}



