
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
#include "axi_mem_model.h"

class axi_mem_pv : public axi_mem_base1_pv {
public:
  axi_mem_pv(sc_module_name module_name)
    : axi_mem_base1_pv(module_name),
      m_memory_data_address("memory_data_address") {
    m_memory_data_address.setValue((long long unsigned int)m_memory_if.get_m_data_chunks_address());
   }

  mb::mb_variable<long long unsigned int> m_memory_data_address;
};
