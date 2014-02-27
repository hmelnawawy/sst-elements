// Copyright 2013 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2013, Sandia Corporation
// All rights reserved.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef COMPONENTS_FIREFLY_FUNCSM_BARRIER_H
#define COMPONENTS_FIREFLY_FUNCSM_BARRIER_H

#include "funcSM/collectiveTree.h"

namespace SST {
namespace Firefly {

class BarrierFuncSM :  public CollectiveTreeFuncSM 
{
  public:
    BarrierFuncSM( SST::Params& params ) : CollectiveTreeFuncSM( params ) {}

    virtual void handleStartEvent( SST::Event* e, Retval& retval ) {
        BarrierStartEvent* event = static_cast<BarrierStartEvent*>( e );

        CollectiveStartEvent* tmp = new CollectiveStartEvent( NULL, NULL, 0,
                Hermes::CHAR, Hermes::MAX, 0, Hermes::GroupWorld, true );

        delete event;

        CollectiveTreeFuncSM::handleStartEvent(
                        static_cast<SST::Event*>( tmp ), retval );
    }

    virtual void handleEnterEvent( Retval& retval ) {
        CollectiveTreeFuncSM::handleEnterEvent( retval );
    }

    virtual std::string protocolName() { return "LongMsgProtocol"; }
};

}
}

#endif
