

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

#ifndef __TEMXCALL_VOICECALL_PIPELINE_H__
#define __TEMXCALL_VOICECALL_PIPELINE_H__

#include <memory>

#include "abstract_pipeline.h"


namespace temxcall {

class VoicecallPipeline;

typedef struct _CallBackData {
	VoicecallPipeline *thisPtr;
} CallBackData;

class VoicecallPipeline : public AbstractPipeline  {

public:
	VoicecallPipeline();
	~VoicecallPipeline();

	virtual bool Load();
	virtual bool Play();
	virtual bool Unload();
#ifdef DEBUG_ENABLED
	virtual void setSourceInformation(xcall_debug_input input);
#endif

	static void on_pad_added_1 (GstElement *element, GstPad *pad, gpointer userData);
	static void on_pad_added_2 (GstElement *element, GstPad *pad, gpointer userData);
	static gboolean bus_call_back (GstBus *bus, GstMessage *msg, gpointer userData);
	static GstPadProbeReturn pad_probe_cb (GstPad * pad, GstPadProbeInfo * info, gpointer userData);
protected:
//  std::shared_ptr<
	bool InitReceiverPipeline ();
	bool InitSenderPipeline();

private:
	GstElement *pipeline;

	// receiving elements
	GstElement *udpSrc;
	GstElement *rtpBin;
	GstElement *rtpDepay;
	GstElement *audioDec;
	GstElement *audioConvert;
	GstElement *audioReSample;
	GstElement *audioSink;

#if RECEIVE_FILESINK_ENABLED
	GstElement *fileSink;
	GstElement *wavEnc;
#endif

	// sending element
	GstElement *sourceEle;
	GstElement *audioConvertSend;
	GstElement *audioEnc;
	GstElement *rtpPay;
	GstElement *udpSink;

	GstBus *bus;

	guint bus_watch_id;

	GMainLoop *mainLoop;
	CallBackData data;

	xcall_debug_input input;

};

}	//temxcall

#endif //__TEMXCALL_VOICECALL_PIPELINE_H__

