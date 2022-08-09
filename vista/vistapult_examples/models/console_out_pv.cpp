
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
//* This file contains the PV class for console_out.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 5.1.0
//* Generated on: Mar. 09, 2022 11:10:44 AM, (user: russk)
//* Automatically merged on: Mar. 10, 2022 01:01:57 PM, (user: russk)
//*>



#include "console_out_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor

console_out_pv::console_out_pv(sc_module_name module_name)
  : console_out_pv_base(module_name) {
  string_ptr = string;  // initialize buffer pointer
}   

/////////////////////////////////////////////////////////////////////////////////
// Use these functions to define the behavior of your model when there is a 
// write event on one of the registers as defined in the Model Builder form.
// These functions are called before the write callbacks on the port.
///////////////////////////////////////////////////////////////////////////////// 

// Write callback for char_out register.
// The newValue has been already assigned to the char_out register.

void console_out_pv::cb_write_char_out(unsigned int newValue) {
  handle_char(newValue);  
}
 

// Write callback for end_sim register.
// The newValue has been already assigned to the end_sim register.

void console_out_pv::cb_write_end_sim(unsigned int newValue) {
  if (newValue == 0x6070BED) {
    cout << "Simulation termination requested " << endl;
    sc_stop();
  }  
}
    

// Read callback for slave port.
// Returns true when successful.

bool console_out_pv::slave_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}

// Write callback for slave port.
// Returns true when successful.

bool console_out_pv::slave_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
} 





unsigned console_out_pv::slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned console_out_pv::slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool console_out_pv::slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 

void console_out_pv::cb_transport_dbg_char_out(tlm::tlm_generic_payload& trans) {}

void console_out_pv::cb_transport_dbg_end_sim(tlm::tlm_generic_payload& trans) {}



// in order to minimize merging conflicts, we recommend to add your functions after this comment


void console_out_pv::handle_char(unsigned char c)
{
  // call from cb_write_char_out

  *string_ptr++ = c;

  if (c == 10) {
    *(string_ptr-1) = 0; // null terminate the string, overwrite linefeed
    *(string_ptr-2) = 0;
    cout << "CONSOLE>> " << string << endl;
    string_ptr = string;
  }

  if (string_ptr - string >= 80) {
    *string_ptr = 0; // null terminate string
    cout << "CONSOLE>> " << string;
    string_ptr = string;
  }
}