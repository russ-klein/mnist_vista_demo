
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
//* This file contains the timing class for axi_mem.
//*
//* This is a template file: You may modify this file to implement the 
//* timing behavior of your component.
//* The functions below allows advance users to customize the timing behavior of your model.
//* 
//* Model Builder version: 5.1.0
//* Generated on: Mar. 06, 2022 07:15:07 PM, (user: russk)
//*>


#include "axi_mem_t.h"

#ifdef __axi_mem_t_base_CLASS_EXIST__
#include <iostream>

using namespace std;
using namespace sc_dt;
using namespace sc_core;



axi_mem_t_base* axi_mem_t_base::create_t(const char* name, long simulation) {
  return new axi_mem_t(name, simulation);
}


axi_mem_t::axi_mem_t(sc_module_name _name, long simulation)
  : axi_mem_t_base(_name, simulation) {
  
}


#endif