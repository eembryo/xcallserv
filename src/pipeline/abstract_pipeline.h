

/*
 * @@@ LICENSE
 * Copyright (C) 2015-2016, LG Electronics, All Right Reserved.
 * No part of this source code may be communicated, distributed, reproduced
 * or transmitted in any form or by any means, electronic or mechanical or
 * otherwise, for any purpose, without the prior written permission of
 * LG Electronics.
 * LICENSE @@@
 *
 * Design/Author : dhilipkumar.raman@lge.com, jinheung.tark@lgepartner.com
 * Date : 02/04/2016
 *
 * <IHU XCallService> Detailed note is as follows.
 *
 *
 */



#ifndef __TEMXCALL_ABSTRACT_PIPELINE_H__
#define __TEMXCALL_ABSTRACT_PIPELINE_H__


#include "xcall_debug.h"
#include <xcallservice_logger.h>

namespace temxcall {
#include <gst/gst.h>
#include <glib.h>
class AbstractPipeline {

	public:
		AbstractPipeline() {};
		~AbstractPipeline() {};
		virtual bool Load() = 0;
		virtual bool Play() = 0;
		virtual bool Unload() = 0;
#ifdef DEBUG_ENABLED
	virtual void setSourceInformation(xcall_debug_input input) = 0;
#endif

};

} //temxcall

#endif //__TEMXCALL_ABSTRACT_PIPELINE_H__

