// Copyright 2009-2014 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2014, Sandia Corporation
// All rights reserved.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.


#include <sst_config.h>
#include <sst/core/serialization.h>
#include <sst/core/element.h>

#include "mirandaCPU.h"
#include "generators/singlestream.h"
#include "generators/randomgen.h"
#include "generators/streambench.h"
#include "generators/revsinglestream.h"

using namespace SST;
using namespace SST::Miranda;

static Module* load_SingleStreamGenerator(Component* owner, Params& params) {
	return new SingleStreamGenerator(owner, params);
}

static Module* load_RevSingleStreamGenerator(Component* owner, Params& params) {
	return new ReverseSingleStreamGenerator(owner, params);
}

static Module* load_RandomGenerator(Component* owner, Params& params) {
	return new RandomGenerator(owner, params);
}

static Module* load_STREAMGenerator(Component* owner, Params& params) {
	return new STREAMBenchGenerator(owner, params);
}

static Component* load_MirandaBaseCPU(ComponentId_t id, Params& params) {
	return new RequestGenCPU(id, params);
}

static const ElementInfoParam singleStreamGen_params[] = {
    { "verbose",          "Sets the verbosity output of the generator", "0" },
    { "count",            "Count for number of items being requested", "1024" },
    { "length",           "Length of requests", "8" },
    { "max_address",      "Maximum address allowed for generation", "16384" },
    { "startat",          "Sets the start address for generation", "0" },
    { NULL, NULL, NULL }
};

static const ElementInfoParam revSingleStreamGen_params[] = {
    { "start_at",         "Sets the start *index* for this generator", "2048" },
    { "stop_at",          "Sets the stop *index* for this generator, stop < start", "0" },
    { "verbose",          "Sets the verbosity of the output", "0" },
    { "datawidth",        "Sets the width of the memory operation", "8" },
    { "stride",           "Sets the stride, since this is a reverse stream this is subtracted per iteration, def=1", "1" },
    { NULL, NULL, NULL }
};

static const ElementInfoParam randomGen_params[] = {
    { "verbose",          "Sets the verbosity output of the generator", "0" },
    { "count",            "Count for number of items being requested", "1024" },
    { "length",           "Length of requests", "8" },
    { "max_address",      "Maximum address allowed for generation", "16384" },
    { NULL, NULL, NULL }
};

static const ElementInfoParam streamBench_params[] = {
    { "verbose",          "Sets the verbosity output of the generator", "0" },
    { "n",                "Sets the number of elements in the STREAM arrays", "10000" },
    { "operandwidth",     "Sets the length of the request, default=8 (i.e. one double)", "8" },
    { "start_a",          "Sets the start address of the array a", "0" },
    { "start_b",          "Sets the start address of the array b", "1024" },
    { "start_c",          "Sets the start address of the array c", "2048" },
    { NULL, NULL, NULL }
};

static const ElementInfoModule modules[] = {
	{
		"SingleStreamGenerator",
		"Creates a single stream of accesses to/from memory",
		NULL,
		NULL,
		load_SingleStreamGenerator,
		singleStreamGen_params,
		"SST::Miranda::RequestGenerator"
	},
	{
		"ReverseSingleStreamGenerator",
		"Creates a single reverse ordering stream of accesses to/from memory",
		NULL,
		NULL,
		load_RevSingleStreamGenerator,
		revSingleStreamGen_params,
		"SST::Miranda::RequestGenerator"
	},
	{
		"STREAMBenchGenerator",
		"Creates a representation of the STREAM benchmark",
		NULL,
		NULL,
		load_STREAMGenerator,
		streamBench_params,
		"SST::Miranda::RequestGenerator"
	},
	{
		"RandomGenerator",
		"Creates a single random stream of accesses to/from memory",
		NULL,
		NULL,
		load_RandomGenerator,
		randomGen_params,
		"SST::Miranda::RequestGenerator"
	},
	{ NULL, NULL, NULL, NULL, NULL, NULL }
};

static const ElementInfoParam basecpu_params[] = {
     { "cache_line_size",  "The size of the cache line that this prefetcher is attached to, default is 64-bytes", "64" },
     { "maxmemreqpending", "Set the maximum number of requests allowed to be pending", "16" },
     { "verbose", 		"Sets the verbosity of output produced by the CPU", 	"0" },
     { "printStats",       "Prints statistics output", "0" },
     { "generator",        "The generator to be loaded for address creation", "miranda.SingleStreamGenerator" },
     { "clock",            "Clock for the base CPU", "2GHz" },
     { "memoryinterface",  "Sets the memory interface module to use", "memHierarchy.memInterface" },
     { NULL, NULL, NULL }
};

static const ElementInfoPort basecpu_ports[] = {
    	{ "cache_link",      "Link to Memory Controller", NULL },
    	{ NULL, NULL, NULL }
};

static const ElementInfoComponent components[] = {
	{
		"BaseCPU",
		"Creates a base Miranda CPU ready to load an address generator",
		NULL,
		load_MirandaBaseCPU,
		basecpu_params,
		basecpu_ports,
		COMPONENT_CATEGORY_PROCESSOR
	},
	{ NULL, NULL, NULL, NULL, NULL, NULL, 0 }
};

extern "C" {
    ElementLibraryInfo miranda_eli = {
        "Miranda",
        "Address generator compatible with SST MemHierarchy",
        components,
        NULL,
        NULL,
        modules,
        NULL,
        NULL
    };
}