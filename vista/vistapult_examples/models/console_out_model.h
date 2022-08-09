
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
//* The console_out_pv will be derived from this class.
//*
//* Model Builder version: 5.1.0
//* Generated on: Mar. 10, 2022 01:01:57 PM, (user: russk)
//*>



#pragma once

#include "model_builder.h"

#ifdef MODEL_BUILDER_VERSION_NUMBER
#if 5100 != MODEL_BUILDER_VERSION_NUMBER
#error "This model was generated using Model Builder version: 5.1.0. Please regenerate model."
#endif
#else
#error "Please regenerate model."
#endif




#include "axi_protocol.h"

using namespace ::tlm;

class console_out_pv_base_parameters {
 public :
  console_out_pv_base_parameters(sc_object* object);
  void print_parameters();

 protected:
  sc_object* m_object;

  sc_core::sc_time clock;
  sc_core::sc_time axi_clock;
  double nominal_voltage;
  bool mb_debug;
  sc_core::sc_time mb_debug_start_time;
  sc_core::sc_time mb_debug_end_time;
  const char* mb_debug_address_read;
  const char* mb_debug_address_write;
  bool port_enable;
  bool call_to_default_if;
  bool verbose_parameters;
  bool dmi_enabled;
  const char* warning_level;
  unsigned int slave_pipeline_length;
  unsigned int slave_outstanding;
  unsigned int slave_read_data_queue_size;
  unsigned int slave_write_data_queue_size;
};




class console_out_pv_base;


class console_out_pv_base_mb_compatibility : public mb::mb_module {
  friend class console_out_pv_base;
 public:
  typedef unsigned int mb_address_type;
 protected:
  console_out_pv_base_mb_compatibility(sc_core::sc_module_name& module_name)
    : mb::mb_module(module_name) {}

  ////////////////////////////////////////
  // functions for target port: slave
  ////////////////////////////////////////
  protected:
   virtual bool slave_callback_read(mb_address_type address,
                                                      unsigned char* data,
                                                      unsigned size) {
     return true;
   } 
   virtual bool slave_callback_write(mb_address_type address,
                                                       unsigned char* data,
                                                       unsigned size) {
     return true;
   } 
   virtual unsigned slave_callback_read_dbg(mb_address_type address,
                                                              unsigned char* data,
                                                              unsigned size) {
     return 0;
   } 
   virtual unsigned slave_callback_write_dbg(mb_address_type address,
                                                               unsigned char* data,
                                                               unsigned size) {
     return 0;
   }
   virtual bool slave_get_direct_memory_ptr(mb_address_type address,
                                                              tlm::tlm_dmi& dmiData) {
     return false;
   }
   virtual bool slave_enable() {
     return slave_set_enable(true);
   }
   virtual bool slave_disable() {
     return slave_set_enable(false);
   }
   virtual bool slave_set_enable(bool enable) {
     string port_path = mb::tlm20::remove_pv(sc_core::sc_object::name()) + + ".slave";
     esl::sc_sim::pvt_port_connect* pvt_port = dynamic_cast<esl::sc_sim::pvt_port_connect*>(sc_find_object(port_path.c_str()));
     if(!pvt_port) {
       return false;
     }
     (dynamic_cast<mb::utl::ExternalAccess*>(pvt_port))->external_enable(enable);
     return true;
   }
};


class console_out_pv_base : public console_out_pv_base_mb_compatibility,
                           public console_out_pv_base_parameters
{
  
protected:
  mb::utl::mb_debug_handler *m_mb_debug; 
private:
  typedef console_out_pv_base_mb_compatibility mb_compatibility_class;
  typedef console_out_pv_base_mb_compatibility BASE_TYPE;
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  typedef console_out_pv_base self;
  SC_HAS_PROCESS(console_out_pv_base);
  console_out_pv_base(sc_core::sc_module_name& module_name);
  ~console_out_pv_base();
  virtual void reset_registers();
  virtual void reset_model();
  enum port_enum {slave_idx = 0 };
 private:  
  template <class DATATYPE>
  void allocate_in_memory(mb::mb_register<DATATYPE>* regVec, mb::mb_memory_b& memObj, unsigned int regSize) {
    unsigned u = 0;
    while(u < regSize) {
      regVec[u].allocate_in_memory(&memObj);
      u++;
    }
  }

 protected:

  mb::tlm20::fw_process<tlm::tlm_base_protocol_types> m_slave_fw_process;
  
 public:
  bool get_mb_debug() {
    return m_mb_debug->get_mb_debug();
  }
  void set_mb_debug(bool value) {
    m_mb_debug->set_mb_debug(value);
  }
      

 protected:

  virtual void slave_callback(tlm::tlm_base_protocol_types::tlm_payload_type& trans, sc_core::sc_time& t) {
    bool status;

    if(m_mb_debug->get_mb_debug()) m_mb_debug->issue_mb_debug_messages(trans,"slave");
    
    if (trans.get_byte_enable_ptr() && trans.get_byte_enable_length()) {
      std::stringstream str;
      str << std::showbase << std::hex;
      if (trans.is_write())
        str << "writing to address " << trans.get_address() << " : byte enable pointer defined but not used ";
      else
        str << "reading from address " << trans.get_address() << " : byte enable pointer defined but not used ";
      mb::sysc::complain(str.str().c_str(), this->name());
    }
    payload_for_token = &trans;
    
    if (trans.is_write()) {
      status = slave_callback_write(trans.get_address(), trans.get_data_ptr(), trans.get_data_length());
    } else if (trans.is_read()) {
      status = slave_callback_read(trans.get_address(), trans.get_data_ptr(), trans.get_data_length());
    } else {
      status = false;
    }
    payload_for_token = 0;

    tlm::tlm_response_status trans_status = trans.get_response_status();
    if (trans_status == tlm::TLM_INCOMPLETE_RESPONSE ||
        trans_status == tlm::TLM_OK_RESPONSE)
      trans.set_response_status(status ? TLM_OK_RESPONSE : TLM_GENERIC_ERROR_RESPONSE);
  }

  virtual unsigned slave_callback_dbg(tlm::tlm_base_protocol_types::tlm_payload_type& trans) {
    
    unsigned status = 0;
    if (trans.is_write()) {
      status = slave_callback_write_dbg(trans.get_address(), trans.get_data_ptr(), trans.get_data_length());
    } else if (trans.is_read()) {
      status = slave_callback_read_dbg(trans.get_address(), trans.get_data_ptr(), trans.get_data_length());
    } 

    return status;
  }

  virtual bool slave_get_direct_memory_ptr_callback(tlm::tlm_base_protocol_types::tlm_payload_type& trans,
                                                                      tlm::tlm_dmi& dmiData) {
    if (trans.get_command() == tlm::TLM_IGNORE_COMMAND)
      return false;
    payload_on_stack = &trans;
    bool ret_value = slave_get_direct_memory_ptr(trans.get_address(), dmiData);
    if (ret_value) {
      get_dmi_delay_cb(trans, dmiData, slave_idx);
    }
    payload_on_stack = 0;
    return ret_value;
  }

  virtual void get_dmi_delay_cb(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData, unsigned port_index) {
    sc_time t = sc_core::SC_ZERO_TIME;
    
    esl::sc_sim::pvt_connect::getPVTBaseModel()->get_write_delay_for_dmi(port_index, trans, t);
    dmiData.set_write_latency(t);
    t = sc_core::SC_ZERO_TIME;
    esl::sc_sim::pvt_connect::getPVTBaseModel()->get_read_delay_for_dmi(port_index, trans, t);
    dmiData.set_read_latency(t);
    
  }

  virtual void invalidate_direct_mem_ptr_callback(unsigned master_index, sc_dt::uint64 start_range, sc_dt::uint64 end_range) {
  }

  

  
 protected:
  ////////////////////////////////////////
  // registers write callbacks interface
  ////////////////////////////////////////
  
  virtual void cb_write_char_out(unsigned int newValue) = 0;
  virtual void cb_write_end_sim(unsigned int newValue) = 0;



  

  
 protected:
  virtual void cb_transport_dbg_char_out(tlm::tlm_generic_payload& trans) {}
  virtual void cb_transport_dbg_end_sim(tlm::tlm_generic_payload& trans) {}
  
  

 public:




  tlm::tlm_generic_payload* payload_on_stack;
  tlm::tlm_generic_payload* payload_for_token;



  ////////////////////////////////////////
  // functions for target port: slave
  ////////////////////////////////////////
  protected:
  virtual bool slave_callback_read(mb_address_type address,
                                                      unsigned char* data,
                                                      unsigned size) {
    mb_address_type local_address = address;
     mb_compatibility_class *This = this;
     return This->slave_callback_read(mb_compatibility_class::mb_address_type(local_address),
                                                        data,
                                                        size);
   }
   virtual bool slave_callback_write(mb_address_type address,
                                                       unsigned char* data,
                                                       unsigned size) {
     mb_address_type local_address = address;
     mb_compatibility_class *This = this;
     return This->slave_callback_write(mb_compatibility_class::mb_address_type(local_address),
                                                         data,
                                                         size);
   }

   virtual unsigned slave_callback_read_dbg(mb_address_type address,
                                                              unsigned char* data,
                                                              unsigned size) {
     mb_compatibility_class *This = this;
     return This->slave_callback_read_dbg(mb_compatibility_class::mb_address_type(address),
                                                            data,
                                                            size);
   }
   virtual unsigned slave_callback_write_dbg(mb_address_type address,
                                                               unsigned char* data,
                                                               unsigned size) {
     mb_compatibility_class *This = this;
     return This->slave_callback_write_dbg(mb_compatibility_class::mb_address_type(address),
                                                             data,
                                                             size);
   }
   virtual bool slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
     mb_compatibility_class *This = this;
     return This->slave_get_direct_memory_ptr(mb_compatibility_class::mb_address_type(address), dmiData);
   }
   virtual void slave_invalidate_direct_memory_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range) {
     return slave->invalidate_direct_mem_ptr(start_range, end_range);
   } 


   
  
  
 

 public:
  typedef tlm::tlm_base_protocol_types slave_protocol_types;
  typedef tlm::tlm_base_protocol_types::tlm_payload_type slave_payload_type;

 public:
  // port declarations 

  tlm::tlm_target_socket <32, tlm::tlm_base_protocol_types>  slave;  

 
  
  
 protected:
  void end_of_elaboration();
  

 public:
  mb::mb_token_ptr get_current_token() {
    mb::mb_token_ptr token_ptr = mb::mb_module::get_current_token();
    if (token_ptr)
      return token_ptr;
    if (payload_for_token) {
      mb::tlm20::pvt_ext* extension = mb::tlm20::setup_pvt_ext(*payload_for_token);
      if (extension) {
        mb::mb_module::set_current_token(extension->getToken());
        return extension->getToken();
      }
    }
    return 0;
  }
  
 protected:
  mb::mb_memory<tlm::tlm_base_protocol_types> slave_memory;
  

 protected:
  mb::mb_register<unsigned int> char_out;
  mb::mb_register<unsigned int> char_ready;
  mb::mb_register<unsigned int> end_sim;
};



#include "model_builder.h"

template <typename TRANS = tlm::tlm_generic_payload>
class console_out_RemoteRegisters {

public:
  typedef tlm::tlm_blocking_transport_if<TRANS> forward_if;

public:
  template <class SOCKET>
  console_out_RemoteRegisters(SOCKET& s, uint64_t baseAddress) :
    m_char_out(s[0], baseAddress, ((0x00) / 4), ( (0) + (((0x00) % 4) << 3)), ( (31) + (((0x00) % 4) << 3))),
    m_char_ready(s[0], baseAddress, ((0x18) / 4), ( (0) + (((0x18) % 4) << 3)), ( (31) + (((0x18) % 4) << 3))),
    m_end_sim(s[0], baseAddress, ((0xFFF0) / 4), ( (0) + (((0xFFF0) % 4) << 3)), ( (31) + (((0xFFF0) % 4) << 3))),
    m_dummy(0) {}
    
public:
  mb::mb_remote_register<unsigned int, TRANS> m_char_out;
  mb::mb_remote_register<unsigned int, TRANS> m_char_ready;
  mb::mb_remote_register<unsigned int, TRANS> m_end_sim;
private:
  int m_dummy;
};

/* for backware compatibility */
template <typename TRANS = tlm::tlm_generic_payload>
class console_out_pv_RemoteRegisters : public console_out_RemoteRegisters<TRANS> {
public:
  template <class SOCKET>
  console_out_pv_RemoteRegisters(SOCKET& s, uint64_t baseAddress)
    : console_out_RemoteRegisters<TRANS>(s, baseAddress) {
  }
};



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
//* The console_out_t will be derived from this class.
//*
//* Model Builder version: 5.1.0
//* Generated on: Mar. 10, 2022 01:01:57 PM, (user: russk)
//*>


#pragma once

#include "model_builder.h"
#include "axi_protocol.h"


#define __console_out_t_base_CLASS_EXIST__


class console_out_t_base : public papoulis::SystemCBaseModel {
public:
  static console_out_t_base* create_t(const char* _name, long simulation); 
public:
  console_out_t_base(sc_core::sc_module_name& module_name, long simulation);
 
  enum port_enum {slave = 0};

protected:
  // The following callbacks are called whenever there is a transaction start or end in the port

  virtual void accept_axi_READ
    (long port_index,
     sc_dt::int64 time,
     long& burst_size,
     sc_dt::uint64& TR_ID,
     sc_dt::uint64 ARADDR,
     sc_dt::uint64 RDATA,
     sc_dt::uint64& ARSIZE,
     sc_dt::uint64 block_size,
     sc_dt::uint64& ARBURST,
     sc_dt::uint64& ARLEN,
     sc_dt::uint64& ARLOCK) {};
  virtual void end_axi_READ
    (long port_index,
     sc_dt::uint64 time,
     long& burst_size,
     sc_dt::uint64& TR_ID,
     sc_dt::uint64 ARADDR,
     sc_dt::uint64 RDATA,
     sc_dt::uint64& ARSIZE,
     sc_dt::uint64 block_size,
     sc_dt::uint64& ARBURST,
     sc_dt::uint64& ARLEN,
     sc_dt::uint64& ARLOCK) {};

  virtual void accept_axi_WRITE
    (long port_index,
     sc_dt::int64 time,
     long& burst_size,
     sc_dt::uint64& TR_ID,
     sc_dt::uint64 AWADDR,
     sc_dt::uint64 WDATA,
     sc_dt::uint64& AWSIZE,
     sc_dt::uint64 block_size,
     sc_dt::uint64& AWBURST,
     sc_dt::uint64& AWLEN,
     sc_dt::uint64& AWLOCK) {};
  virtual void end_axi_WRITE
    (long port_index,
     sc_dt::uint64 time,
     long& burst_size,
     sc_dt::uint64& TR_ID,
     sc_dt::uint64 AWADDR,
     sc_dt::uint64 WDATA,
     sc_dt::uint64& AWSIZE,
     sc_dt::uint64 block_size,
     sc_dt::uint64& AWBURST,
     sc_dt::uint64& AWLEN,
     sc_dt::uint64& AWLOCK) {};


public:
  virtual bool portHasRegisters(unsigned portIndex);
  virtual bool triggerRegistersGotHit(unsigned portIndex, tlm::tlm_generic_payload& trans);

  virtual const char* get_library_name() {return "models";}
  virtual const char* get_model_vendor() {return "Mentor.com";}
  virtual const char* get_model_version() {return "1.0";}

  virtual unsigned getPortCountForRegister(unsigned regIndex);
  virtual void getPortNamesForRegister(unsigned regIndex, const char **names);
protected:
  /* schedule functions */
public:
  /* called when "params.m_phase" is sent through the "port_index" port */
  virtual void sent_phase_cb(unsigned port_index,
                             esl::sc_sim::mb_cb_params& params) {
    
  }
                             
  /* called when "params.m_phase" is received by the "port_index" port */
  virtual void received_phase_cb(unsigned port_index,
                                 esl::sc_sim::mb_cb_params& params) {
    
  }

protected:
  friend class console_out_model;
  
protected:
  // parameters
  sc_core::sc_time clock;
  sc_core::sc_time axi_clock;
  double nominal_voltage;
  bool mb_debug;
  sc_core::sc_time mb_debug_start_time;
  sc_core::sc_time mb_debug_end_time;
  const char* mb_debug_address_read;
  const char* mb_debug_address_write;
  bool port_enable;
  bool call_to_default_if;
  bool verbose_parameters;
  bool dmi_enabled;
  const char* warning_level;
  unsigned int slave_pipeline_length;
  unsigned int slave_outstanding;
  unsigned int slave_read_data_queue_size;
  unsigned int slave_write_data_queue_size;

protected:
  long m_simulation;

 
  
public:
  enum register_enum {char_out_idx, char_ready_idx, end_sim_idx };
protected:
  mb::mb_t_register<unsigned int> char_out;
  mb::mb_t_register<unsigned int> char_ready;
  mb::mb_t_register<unsigned int> end_sim; 
  
  

  static const unsigned port_count = 1;
  papoulis::SystemCBaseModel::PortDescription port_descriptions[port_count];
  
  

protected:
  std::vector<esl::sc_sim::pipeline_policy*> m_pipeline_vector;
  std::vector<esl::sc_sim::sequential_policy*> m_sequential_vector;
  std::vector<esl::sc_sim::delay_policy*> m_delay_vector;
  std::vector<esl::sc_sim::uniform_bus_policy*> m_bus_vector;
  std::vector<esl::sc_sim::power_policy*> m_power_vector;
  std::vector<esl::sc_sim::state_power_policy*> m_state_power_vector;
public:
  virtual void update_sync_all();
  virtual void update_pipeline_parameters(esl::sc_sim::pipeline_policy* handle);
  virtual void update_sequential_parameters(esl::sc_sim::sequential_policy* handle);
  virtual void update_delay_parameters(esl::sc_sim::delay_policy* handle);
  virtual void update_bus_parameters(esl::sc_sim::uniform_bus_policy* handle);
  virtual void update_power_parameters(esl::sc_sim::power_policy* handle);
  virtual void update_global_power_parameters(esl::sc_sim::constant_global_power_policy* handle);
  virtual void update_state_power_parameters(esl::sc_sim::state_power_policy* handle);
protected: /* InterfaceFunctions */
  virtual TransactionCallbackFunctionPointer getTransactionCallback(unsigned callbackIndex);
  config::real80 get_state_power();
protected:

  void start_transaction_axi_READ
    (esl::include::TRequest* request,
     unsigned port_index,
     sc_dt::uint64 startTime,
     sc_dt::uint64 endTime,
     sc_dt::uint64* parameters,
     bool hasBeenError);
  void end_transaction_axi_READ
    (esl::include::TRequest* request,
     unsigned port_index,
     sc_dt::uint64 startTime,
     sc_dt::uint64 endTime,
     sc_dt::uint64* parameters,
     bool hasBeenError);
  void start_transaction_axi_WRITE
    (esl::include::TRequest* request,
     unsigned port_index,
     sc_dt::uint64 startTime,
     sc_dt::uint64 endTime,
     sc_dt::uint64* parameters,
     bool hasBeenError);
  void end_transaction_axi_WRITE
    (esl::include::TRequest* request,
     unsigned port_index,
     sc_dt::uint64 startTime,
     sc_dt::uint64 endTime,
     sc_dt::uint64* parameters,
     bool hasBeenError);
};

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
//* This file contains the PVT class for console_out.
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
//* Generated on: Mar. 10, 2022 01:01:57 PM, (user: russk)
//*>


#pragma once

#include "model_builder.h"




 


// forward declaration for pv class

class console_out_pv;



using namespace std;

class console_out_pvt_param_defaults {
  
public:
  console_out_pvt_param_defaults(const char* hier_name) {

    sc_core::sc_time clock;
    sc_core::sc_time axi_clock;
    double nominal_voltage;
    bool mb_debug;
    sc_core::sc_time mb_debug_start_time;
    sc_core::sc_time mb_debug_end_time;
    const char* mb_debug_address_read;
    const char* mb_debug_address_write;
    bool port_enable;
    bool call_to_default_if;
    bool verbose_parameters;
    bool dmi_enabled;
    const char* warning_level;
    unsigned int slave_pipeline_length;
    unsigned int slave_outstanding;
    unsigned int slave_read_data_queue_size;
    unsigned int slave_write_data_queue_size;
    clock = ::mb::sysc::sdInitParameter<sc_core::sc_time>("clock", sc_core::sc_time(10, sc_core::SC_NS), hier_name ,"console_out");
    axi_clock = ::mb::sysc::sdInitParameter<sc_core::sc_time>("axi_clock", clock, hier_name ,"console_out");
    nominal_voltage = ::mb::sysc::sdInitParameter<double>("nominal_voltage", 1, hier_name ,"console_out");
    mb_debug = ::mb::sysc::sdInitParameter<bool>("mb_debug", false, hier_name ,"console_out");
    mb_debug_start_time = ::mb::sysc::sdInitParameter<sc_core::sc_time>("mb_debug_start_time", sc_core::sc_time(0, sc_core::SC_NS), hier_name ,"console_out");
    mb_debug_end_time = ::mb::sysc::sdInitParameter<sc_core::sc_time>("mb_debug_end_time", sc_core::sc_time(0, sc_core::SC_NS), hier_name ,"console_out");
    mb_debug_address_read = ::mb::sysc::sdInitParameter<const char*>("mb_debug_address_read", "0x10:0x0", hier_name ,"console_out");
    mb_debug_address_write = ::mb::sysc::sdInitParameter<const char*>("mb_debug_address_write", "0x10:0x0", hier_name ,"console_out");
    port_enable = ::mb::sysc::sdInitParameter<bool>("port_enable", true, hier_name ,"console_out");
    call_to_default_if = ::mb::sysc::sdInitParameter<bool>("call_to_default_if", false, hier_name ,"console_out");
    verbose_parameters = ::mb::sysc::sdInitParameter<bool>("verbose_parameters", true, hier_name ,"console_out");
    dmi_enabled = ::mb::sysc::sdInitParameter<bool>("dmi_enabled", true, hier_name ,"console_out");
    warning_level = ::mb::sysc::sdInitParameter<const char*>("warning_level", "WARNING", hier_name ,"console_out");
    slave_pipeline_length = ::mb::sysc::sdInitParameter<unsigned int>("slave_pipeline_length", 2, hier_name ,"console_out");
    slave_outstanding = ::mb::sysc::sdInitParameter<unsigned int>("slave_outstanding", 1, hier_name ,"console_out");
    slave_read_data_queue_size = ::mb::sysc::sdInitParameter<unsigned int>("slave_read_data_queue_size", 0, hier_name ,"console_out");
    slave_write_data_queue_size = ::mb::sysc::sdInitParameter<unsigned int>("slave_write_data_queue_size", 0, hier_name ,"console_out");
    ::mb::sysc::sdPropagateParameters();
  }

  console_out_pvt_param_defaults(const char* hier_name, sc_core::sc_time clock_init, sc_core::sc_time axi_clock_init, double nominal_voltage_init, bool mb_debug_init, sc_core::sc_time mb_debug_start_time_init, sc_core::sc_time mb_debug_end_time_init, const char* mb_debug_address_read_init, const char* mb_debug_address_write_init, bool port_enable_init, bool call_to_default_if_init, bool verbose_parameters_init, bool dmi_enabled_init, const char* warning_level_init, unsigned int slave_pipeline_length_init, unsigned int slave_outstanding_init, unsigned int slave_read_data_queue_size_init, unsigned int slave_write_data_queue_size_init) {

    sc_core::sc_time clock;
    sc_core::sc_time axi_clock;
    double nominal_voltage;
    bool mb_debug;
    sc_core::sc_time mb_debug_start_time;
    sc_core::sc_time mb_debug_end_time;
    const char* mb_debug_address_read;
    const char* mb_debug_address_write;
    bool port_enable;
    bool call_to_default_if;
    bool verbose_parameters;
    bool dmi_enabled;
    const char* warning_level;
    unsigned int slave_pipeline_length;
    unsigned int slave_outstanding;
    unsigned int slave_read_data_queue_size;
    unsigned int slave_write_data_queue_size;
    clock = ::mb::sysc::sdInitParameter<sc_core::sc_time>("clock", clock_init, hier_name ,"console_out");
    axi_clock = ::mb::sysc::sdInitParameter<sc_core::sc_time>("axi_clock", axi_clock_init, hier_name ,"console_out");
    nominal_voltage = ::mb::sysc::sdInitParameter<double>("nominal_voltage", nominal_voltage_init, hier_name ,"console_out");
    mb_debug = ::mb::sysc::sdInitParameter<bool>("mb_debug", mb_debug_init, hier_name ,"console_out");
    mb_debug_start_time = ::mb::sysc::sdInitParameter<sc_core::sc_time>("mb_debug_start_time", mb_debug_start_time_init, hier_name ,"console_out");
    mb_debug_end_time = ::mb::sysc::sdInitParameter<sc_core::sc_time>("mb_debug_end_time", mb_debug_end_time_init, hier_name ,"console_out");
    mb_debug_address_read = ::mb::sysc::sdInitParameter<const char*>("mb_debug_address_read", mb_debug_address_read_init, hier_name ,"console_out");
    mb_debug_address_write = ::mb::sysc::sdInitParameter<const char*>("mb_debug_address_write", mb_debug_address_write_init, hier_name ,"console_out");
    port_enable = ::mb::sysc::sdInitParameter<bool>("port_enable", port_enable_init, hier_name ,"console_out");
    call_to_default_if = ::mb::sysc::sdInitParameter<bool>("call_to_default_if", call_to_default_if_init, hier_name ,"console_out");
    verbose_parameters = ::mb::sysc::sdInitParameter<bool>("verbose_parameters", verbose_parameters_init, hier_name ,"console_out");
    dmi_enabled = ::mb::sysc::sdInitParameter<bool>("dmi_enabled", dmi_enabled_init, hier_name ,"console_out");
    warning_level = ::mb::sysc::sdInitParameter<const char*>("warning_level", warning_level_init, hier_name ,"console_out");
    slave_pipeline_length = ::mb::sysc::sdInitParameter<unsigned int>("slave_pipeline_length", slave_pipeline_length_init, hier_name ,"console_out");
    slave_outstanding = ::mb::sysc::sdInitParameter<unsigned int>("slave_outstanding", slave_outstanding_init, hier_name ,"console_out");
    slave_read_data_queue_size = ::mb::sysc::sdInitParameter<unsigned int>("slave_read_data_queue_size", slave_read_data_queue_size_init, hier_name ,"console_out");
    slave_write_data_queue_size = ::mb::sysc::sdInitParameter<unsigned int>("slave_write_data_queue_size", slave_write_data_queue_size_init, hier_name ,"console_out");

    ::mb::sysc::sdPropagateParameters();
    }

  console_out_pvt_param_defaults(const char* hier_name, std::vector<std::pair<char*, unsigned int> > &change_parameters){

    sc_core::sc_time clock;
    sc_core::sc_time axi_clock;
    double nominal_voltage;
    bool mb_debug;
    sc_core::sc_time mb_debug_start_time;
    sc_core::sc_time mb_debug_end_time;
    const char* mb_debug_address_read;
    const char* mb_debug_address_write;
    bool port_enable;
    bool call_to_default_if;
    bool verbose_parameters;
    bool dmi_enabled;
    const char* warning_level;
    unsigned int slave_pipeline_length;
    unsigned int slave_outstanding;
    unsigned int slave_read_data_queue_size;
    unsigned int slave_write_data_queue_size;
    for (unsigned i =0; i<change_parameters.size(); i++){
      ::mb::sysc::sdInitParameter<unsigned int>(change_parameters[i].first, change_parameters[i].second, hier_name ,"console_out");
    }

    clock = ::mb::sysc::sdInitParameter<sc_core::sc_time>("clock", sc_core::sc_time(10, sc_core::SC_NS), hier_name ,"console_out");
    axi_clock = ::mb::sysc::sdInitParameter<sc_core::sc_time>("axi_clock", clock, hier_name ,"console_out");
    nominal_voltage = ::mb::sysc::sdInitParameter<double>("nominal_voltage", 1, hier_name ,"console_out");
    mb_debug = ::mb::sysc::sdInitParameter<bool>("mb_debug", false, hier_name ,"console_out");
    mb_debug_start_time = ::mb::sysc::sdInitParameter<sc_core::sc_time>("mb_debug_start_time", sc_core::sc_time(0, sc_core::SC_NS), hier_name ,"console_out");
    mb_debug_end_time = ::mb::sysc::sdInitParameter<sc_core::sc_time>("mb_debug_end_time", sc_core::sc_time(0, sc_core::SC_NS), hier_name ,"console_out");
    mb_debug_address_read = ::mb::sysc::sdInitParameter<const char*>("mb_debug_address_read", "0x10:0x0", hier_name ,"console_out");
    mb_debug_address_write = ::mb::sysc::sdInitParameter<const char*>("mb_debug_address_write", "0x10:0x0", hier_name ,"console_out");
    port_enable = ::mb::sysc::sdInitParameter<bool>("port_enable", true, hier_name ,"console_out");
    call_to_default_if = ::mb::sysc::sdInitParameter<bool>("call_to_default_if", false, hier_name ,"console_out");
    verbose_parameters = ::mb::sysc::sdInitParameter<bool>("verbose_parameters", true, hier_name ,"console_out");
    dmi_enabled = ::mb::sysc::sdInitParameter<bool>("dmi_enabled", true, hier_name ,"console_out");
    warning_level = ::mb::sysc::sdInitParameter<const char*>("warning_level", "WARNING", hier_name ,"console_out");
    slave_pipeline_length = ::mb::sysc::sdInitParameter<unsigned int>("slave_pipeline_length", 2, hier_name ,"console_out");
    slave_outstanding = ::mb::sysc::sdInitParameter<unsigned int>("slave_outstanding", 1, hier_name ,"console_out");
    slave_read_data_queue_size = ::mb::sysc::sdInitParameter<unsigned int>("slave_read_data_queue_size", 0, hier_name ,"console_out");
    slave_write_data_queue_size = ::mb::sysc::sdInitParameter<unsigned int>("slave_write_data_queue_size", 0, hier_name ,"console_out");  

    ::mb::sysc::sdPropagateParameters();
  }
  
  //void set_clock (

};


class console_out_pvt : public esl::sc_sim::PVTBaseModel, 
                          public mb::utl::cb_owner,
                          private console_out_pvt_param_defaults {

 public:
  typedef console_out_pvt self_type;

 public: 
  // Constructor
  console_out_pvt(sc_core::sc_module_name module_name); 
  console_out_pvt(sc_core::sc_module_name module_name, sc_core::sc_time clock_init, sc_core::sc_time axi_clock_init, double nominal_voltage_init, bool mb_debug_init, sc_core::sc_time mb_debug_start_time_init, sc_core::sc_time mb_debug_end_time_init, const char* mb_debug_address_read_init, const char* mb_debug_address_write_init, bool port_enable_init, bool call_to_default_if_init, bool verbose_parameters_init, bool dmi_enabled_init, const char* warning_level_init, unsigned int slave_pipeline_length_init, unsigned int slave_outstanding_init, unsigned int slave_read_data_queue_size_init, unsigned int slave_write_data_queue_size_init); 
  console_out_pvt(sc_core::sc_module_name module_name, std::vector<std::pair<char*, unsigned int> > &change_parameters);
  ~console_out_pvt(); 

 
 public:
 
    //access the T instance
  inline console_out_t_base* getT() const {
    return m_console_out_t;
  }

  
  //access the PV instance
  inline console_out_pv* getPV() const {
    return m_console_out_pv;
  }

  virtual const SystemCBaseModel* getSystemCBaseModel() const {
    
    return getT();
    
    
  }
  virtual SystemCBaseModel* getSystemCBaseModel() {
    
    return getT();
    
    
  }
  

 private:
  void bind();
  
 

 private:
  
  
  //T instance
  console_out_t_base* m_console_out_t;
  
  
  //PV instance
  console_out_pv* m_console_out_pv;

 public:
  // External ports

  typedef esl::sc_sim::pvt_target_socket<32, axi_protocol_types, 1, sc_core::SC_ONE_OR_MORE_BOUND> slave_type;
  slave_type slave;

 private:
  // PV connection ports

  typedef mb::tlm20::initiator_socket_cb<32> slave_entry_type;
  slave_entry_type slave_entry;      


 private:



  struct slave_nb_connector : public tlm::tlm_bw_nonblocking_transport_if<>, public ::mb::tlm20::socket_tracer_holder {
    console_out_pvt& m_owner;
    
    slave_nb_connector(console_out_pvt& owner) : m_owner(owner) {
    }
    virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans, 
                                               tlm::tlm_phase& phase, 
                                               sc_core::sc_time& t) {
      return m_owner.slave.nb_transport_bw((axi_protocol_types::tlm_payload_type&)trans, phase, t);
    }
    virtual ::mb::tlm20::socket_tracer *get_socket_tracer() {
      return &m_owner.slave;
    }
  };
  friend struct slave_nb_connector;
  slave_nb_connector m_slave_nb_connector;

  

  tlm::tlm_sync_enum receive_nb_transport_slave(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase& phase,
                                                    sc_core::sc_time& t) {
    return getT()->receive_nb_transport(0, trans, phase, t);
  }


};



