
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
//* This file contains the timing class for matchlib_dma.
//*
//* This is a template file: You may modify this file to implement the 
//* timing behavior of your component.
//* The functions below allows advance users to customize the timing behavior of your model.
//* 
//* Model Builder version: 5.1.0
//* Generated on: Mar. 11, 2022 09:04:17 AM, (user: russk)
//*>


#pragma once
#include "matchlib_dma_model.h"
#include "model_builder.h"
#ifdef __matchlib_dma_t_base_CLASS_EXIST__

class matchlib_dma_t : public matchlib_dma_t_base {

public:
  typedef matchlib_dma_t self_type;

public:  
  matchlib_dma_t(sc_core::sc_module_name module_name, long simulation);

  /* policies callbacks */

  // The following callback is called for a target port. Note that the wait_states, power and 
  // influence_time are already computed using a learned policy (if any) or your defined
  // delay and/or power policy.
  // If under certain conditions you want to overwrite the above values, you have to overload
  // this callback in your derived class.
  
  virtual void evaluate_delay_policy(mb::mb_delay_request& request) {}

  // The following callback is called for an initiator port. Note that the latency, power and 
  // influence_time are already computed using a learned policy (if any) or your defined
  // split and/or power policy.
  // If under certain conditions you want to overwrite the above values, you have to overload
  // this callback in your derived class.

  virtual void evaluate_split_policy(mb::mb_split_request& request) {}
  
  // The following function is called whenever a pipeline policy is detected on
  // the current initiator port transaction. If you want to overwrite the latency parameter, you
  // have to overload these functions in your derived class
  virtual void evaluate_pipeline_policy(mb::mb_request& cause_request, mb::mb_effect_request& effect_request) {}

  // The following function is called whenever a sequential policy is detected on
  // the current initiator port transaction. If you want to overwrite the latency parameter, you
  // have to overload these functions in your derived class
  virtual void evaluate_sequential_policy(mb::mb_request& cause_request, mb::mb_effect_request& effect_request) {}

  // This is called whenever a variable/register involved in a state power policy is written
  // You can use setPowerInMw interface of the mb_effect_request class, to set the appropriate power value
  virtual void evaluate_state_power_policy(mb::mb_effect_request& request) {}

  /* called when "params.m_phase" is sent through the "port_index" port */
  virtual void sent_phase_cb(unsigned port_index,
                             esl::sc_sim::mb_cb_params& params) {}
                             
  /* called when "params.m_phase" is received by the "port_index" port */
  virtual void received_phase_cb(unsigned port_index,
                                 esl::sc_sim::mb_cb_params& params) {}

};
#endif
