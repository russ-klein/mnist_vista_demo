
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

#pragma once

#include "model_builder.h"
#include "riscv_model.h"



class riscv_pv : public ::mb::models::riscv::riscv_mp<32, 32>,
                      public riscv_pv_base_parameters {

 public:
  typedef ::mb::models::riscv::riscv_mp<32, 32> base_class;

  mb::tlm20::signal_in_socket<>& n_reset_0;
  mb::tlm20::signal_in_socket<>& irq_0;

 public:
  riscv_pv(sc_module_name module_name) 
    : ::mb::models::riscv::riscv_mp<32, 32>(module_name, 0, 0, 0, 1, 0,
                                                                          0, 0, 0), 
    riscv_pv_base_parameters(this),
    n_reset_0(n_reset[0]),
    irq_0(irq[0])
  {
  }

};


