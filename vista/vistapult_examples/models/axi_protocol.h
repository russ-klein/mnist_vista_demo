
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


/* Generated by Model Builder  */

#pragma once
#ifndef __axi_h__
#define __axi_h__

#include "model_builder.h"
class axi_blocking_if : public virtual sc_core::sc_interface
{
public:
  virtual void READ(sc_dt::uint64 delay, long TR_ID, long ARADDR, long* RDATA, long& burstSize, long ARSIZE, long block_size, long ARBURST, long ARLEN, long ARLOCK) = 0;
  virtual void WRITE(sc_dt::uint64 delay, long TR_ID, long AWADDR, const long* WDATA, long& burstSize, long AWSIZE, long block_size, long AWBURST, long AWLEN, long AWLOCK) = 0;
  virtual sc_dt::uint64 getClock() = 0;
};

class axi_non_blocking_if : public virtual sc_core::sc_interface
{
public:
  virtual void nb_READ(sc_dt::uint64 delay, long TR_ID, long ARADDR, long* RDATA, long& burstSize, long ARSIZE, long block_size, long ARBURST, long ARLEN, long ARLOCK) = 0;
  virtual void nb_WRITE(sc_dt::uint64 delay, long TR_ID, long AWADDR, const long* WDATA, long& burstSize, long AWSIZE, long block_size, long AWBURST, long AWLEN, long AWLOCK) = 0;
  virtual const PapoulisEvent& endTransaction() = 0;
  virtual const PapoulisEvent& endAllTransactions() = 0;
  virtual bool canInitiateTransaction() = 0;
  virtual sc_dt::uint64 getClock() = 0;
};

struct axi_protocol_types{
  typedef tlm::tlm_generic_payload tlm_payload_type;
  typedef tlm::tlm_phase tlm_phase_type;
};
#endif
