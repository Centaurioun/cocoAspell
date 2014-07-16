// ============================================================================
//  aspell_extras.cpp
// ============================================================================
//
//	cocoAspell2
//
//  Created by Anton Leuski on 2/12/05.
//  Copyright (c) 2005-2008 Anton Leuski. All rights reserved.
// ============================================================================

#include "aspell_extras.h"

#include "fstream.hpp"
#include "config.hpp"
#include "error.hpp"
#include "posib_err.hpp"
#include "string.hpp"
#include "speller.hpp"

#include "stack_ptr.hpp"
#include "convert.hpp"
#include "tokenizer.hpp"
#include "document_checker.hpp"

namespace acommon {

static int aspell_config_read_in_file(Config * ths, const char * file_name)
{
	PosibErr<void>	ret	= ths->read_in_file(file_name);
	ths->err_.reset(ret.release_err());
	if (ths->err_ != 0) return 0;
	return 1;
}

static int aspell_config_write_out_file(Config * ths, const char * file_name)
{
    FStream out;
	PosibErr<void>	ret	= out.open(file_name, "w");
	ths->err_.reset(ret.release_err());
	if (ths->err_ != 0) return 0;
    ths->write_to_stream(out, true);
	return 1;
}

static int aspell_config_merge(Config * ths, const Config * other)
{
	PosibErr<void>	ret	= ths->merge(*other);
	ths->err_.reset(ret.release_err());
	if (ths->err_ != 0) return 0;
	return 1;
}

}

extern "C" int aspell_config_read_in_file(struct AspellConfig * ths, const char * file_name)
{
	return acommon::aspell_config_read_in_file(reinterpret_cast<acommon::Config*>(ths), file_name);
}

extern "C" int aspell_config_write_out_file(struct AspellConfig * ths, const char * file_name)
{
	return acommon::aspell_config_write_out_file(reinterpret_cast<acommon::Config*>(ths), file_name);
}

extern "C" int aspell_config_merge(struct AspellConfig * ths, const struct AspellConfig * other)
{
	return acommon::aspell_config_merge(reinterpret_cast<acommon::Config*>(ths), reinterpret_cast<const acommon::Config*>(other));
}