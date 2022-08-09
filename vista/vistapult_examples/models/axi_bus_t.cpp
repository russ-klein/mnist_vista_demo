
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



#include "axi_bus_t.h"


using namespace std;
using namespace sc_dt;
using namespace sc_core;

axi_bus_t_base* axi_bus_t_base::create_t(const char* name, long simulation, 
                                                     esl::sc_sim::user_model::Arbiter* arbiter)
{
  return new axi_bus_t(name, simulation, arbiter);
}
