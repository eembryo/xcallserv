
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

#include "voicecall_pipeline.h"
#include <string.h>
#include <glib.h>

namespace temxcall {

/**
 * ================================================================================
 * @fn : VoicecallPipeline
 * @brief : This is constructor function for VoicecallPipeline class
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Initializes the class variables
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
VoicecallPipeline::VoicecallPipeline() {


	pipeline = NULL;

	// receiving elements
	udpSrc = rtpBin = rtpDepay = audioDec = audioConvert = audioReSample = audioSink = NULL;

	// sending element
	sourceEle = audioConvertSend = audioEnc = rtpPay = udpSink = NULL;

	bus = NULL;
	bus_watch_id=0;

	mainLoop = NULL;
	data = {0,};

}

/**
 * ================================================================================
 * @fn : ~VoicecallPipeline
 * @brief : This is destructor function for VoicecallPipeline class
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
VoicecallPipeline::~VoicecallPipeline() {

}

/**
 * ================================================================================
 * @fn : InitReceiverPipeline
 * @brief : This function loads the Gstreamer pipeline
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Initializes necessary elements for receiving & processing audio data
 * - connects the elements appropriately
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool VoicecallPipeline::InitReceiverPipeline()
{
	XCALLLOGI("VoicecallPipeline::InitReceiverPipeline start");

	udpSrc = gst_element_factory_make("udpsrc", "udpSrc");
	GstCaps *caps = nullptr;

	if (!this->input.encScheme.compare("PCMA")) {
		rtpDepay = gst_element_factory_make("rtppcmadepay", "rtpPcmaDepay");
		audioDec = gst_element_factory_make("alawdec", "alawDec");
		XCALLLOGD("VoicecallPipeline::InitReceiverPipeline PCMA");
		caps = gst_caps_new_simple ("application/x-rtp",
									 "media", G_TYPE_STRING, "audio",
									 "clock-rate",  G_TYPE_INT, 8000,
									 "encoding-name", G_TYPE_STRING, "PCMA",
									  NULL);
	} else if (!this->input.encScheme.compare("PCMU")) {
		rtpDepay = gst_element_factory_make("rtppcmudepay", "rtpPcmuDepay");
		audioDec = gst_element_factory_make("mulawdec", "mulawDec");
		XCALLLOGD("VoicecallPipeline::InitReceiverPipeline PCMU");
		caps = gst_caps_new_simple ("application/x-rtp",
									 "media", G_TYPE_STRING, "audio",
									 "clock-rate",  G_TYPE_INT, 8000,
									 "encoding-name", G_TYPE_STRING, "PCMU",
									  NULL);
	} else /*if (!this->input.encScheme.compare("SPEEX"))*/{
		rtpDepay = gst_element_factory_make("rtpspeexdepay", "rtpSpeexDepay");
		audioDec = gst_element_factory_make("speexdec", "speexDec");
		XCALLLOGD("VoicecallPipeline::InitReceiverPipeline SPEEX");
		caps = gst_caps_new_simple ("application/x-rtp",
									 "media", G_TYPE_STRING, "audio",
									 "clock-rate",  G_TYPE_INT, 44100,
									 "encoding-name", G_TYPE_STRING, "SPEEX",
									  NULL);
	}

	audioConvert = gst_element_factory_make("audioconvert", "audioConvert");
	audioReSample = gst_element_factory_make("audioresample", "audioReSample");

#if GEELY_HARDWARE
	XCALLLOGD("VoicecallPipeline::alsasink enabled  now is used");
	audioSink = gst_element_factory_make("alsasink", "alsaSink");
	if (audioSink) {
		g_object_set(G_OBJECT(audioSink), "device", "plug:dmix_48000",
										  "sync", false,
										  NULL);
	}
#else
	XCALLLOGD("VoicecallPipeline::autoaudiosink is used");
	audioSink = gst_element_factory_make("autoaudiosink", "autoAudioSink");
#endif

#if RECEIVE_FILESINK_ENABLED
	const gchar *filepath = "VoiceAudioreceiveddata.wav";
	fileSink = gst_element_factory_make("filesink", "fileSink");
	g_object_set(GST_OBJECT(fileSink), "location", filepath, NULL);
	wavEnc = gst_element_factory_make("wavenc", "wavEnc");
#endif

	if (!udpSrc || !rtpBin || !rtpDepay || !audioDec || !audioConvert || !audioReSample || !audioSink) {
		XCALLLOGE("InitReceiverPipeline: One element could not be created. Exiting.\n");
		return false;
	}

	// probe addtion for receiver source blocking
	GstPad * blockpad = gst_element_get_static_pad (udpSrc, "src");
	gst_pad_add_probe (blockpad, GST_PAD_PROBE_TYPE_BLOCK_DOWNSTREAM, pad_probe_cb, &data, NULL);

	XCALLLOGD("InitReceiverPipeline reception port %u", this->input.srcPort1);
	g_object_set (G_OBJECT (udpSrc), "port", this->input.srcPort1, NULL);
	g_object_set(G_OBJECT (udpSrc), "caps", caps, NULL);
	gst_bin_add(GST_BIN(pipeline), udpSrc);

	XCALLLOGD("InitReceiverPipeline successfull\n");
	return true;
}

/**
 * ================================================================================
 * @fn : InitReceiverPipeline
 * @brief : This function loads the Gstreamer pipeline
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Initializes necessary elements for processing & sending audio data
 * - connects the elements appropriately
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool VoicecallPipeline::InitSenderPipeline()
{
	XCALLLOGI("VoicecallPipeline::InitSenderPipeline start\n");
	GstPad * pad;
	gchar *name;

#if GEELY_HARDWARE
	XCALLLOGD("VoicecallPipeline::alsasrc is used\n");
	sourceEle = gst_element_factory_make("alsasrc", "alsaSrc");
	if (sourceEle){
		g_object_set(G_OBJECT(sourceEle), "device", "hw:3,0", NULL);
	}
#else
	XCALLLOGD("VoicecallPipeline::autoaudiosrc is used\n");
	sourceEle = gst_element_factory_make("autoaudiosrc", "autoAudioSrc");
#endif

	rtpBin = gst_element_factory_make("rtpbin", "rtpBin");
	if (rtpBin)
		g_object_set(G_OBJECT(rtpBin), "latency", 50, NULL);

	audioConvertSend = gst_element_factory_make("audioconvert", "audioConvertSend");

	if (!this->input.encScheme.compare("PCMA")) {
		audioEnc = gst_element_factory_make("alawenc", "alawEnc");
		rtpPay = gst_element_factory_make("rtppcmapay", "rtpPcmaPay");
		XCALLLOGD("VoicecallPipeline::InitSenderPipeline PCMA\n");
	} else if (!this->input.encScheme.compare("PCMU")) {
		audioEnc = gst_element_factory_make("mulawenc", "mulawEnc");
		rtpPay = gst_element_factory_make("rtppcmupay", "rtpPcmuPay");
		XCALLLOGD("VoicecallPipeline::InitSenderPipeline PCMU\n");
	} else /*if (!this->input.encScheme.compare("SPEEX"))*/{
		audioEnc = gst_element_factory_make("speexenc", "speexEnc");
		rtpPay = gst_element_factory_make("rtpspeexpay", "rtpSpeexPay");
		XCALLLOGD("VoicecallPipeline::InitSenderPipeline SPEEX\n");
	}


	udpSink = gst_element_factory_make("udpsink", "udpSink");



	if (!sourceEle || !rtpBin || !audioConvertSend || !audioEnc || !rtpPay || !udpSink) {
		XCALLLOGE("InitSenderPipeline: One element could not be created. Exiting.\n");
		return false;
	}


	gst_bin_add_many(GST_BIN(pipeline), sourceEle, audioConvertSend, audioEnc, rtpPay, rtpBin, udpSink, NULL);

	/* link */  // speekDecoder needs to be added on needed
	if (!gst_element_link_many (sourceEle, audioConvertSend, audioEnc, rtpPay, NULL)) {
		XCALLLOGW("Failed to link elements!");
		return false;
	}

	XCALLLOGD("InitReceiverPipeline sending port %s %u\n", this->input.destIP.c_str(), this->input.destPort1);
	g_object_set (G_OBJECT (udpSink), "host", this->input.destIP.c_str(), NULL);
	g_object_set (G_OBJECT (udpSink), "port", this->input.destPort1, NULL);

	g_signal_connect(rtpBin,"pad-added", G_CALLBACK(on_pad_added_2), &data);

	pad = gst_element_get_request_pad (rtpBin, "send_rtp_sink_%u");
	name = gst_pad_get_name (pad);
	XCALLLOGD("A rtp bin sink pad of %s is created\n", name);

	gst_element_link_pads (rtpPay, "src", rtpBin, name);
	g_free (name);
	gst_object_unref (GST_OBJECT (pad));

	XCALLLOGI("InitSenderPipeline successfull\n");

	return true;
}

/**
 * ================================================================================
 * @fn : Load
 * @brief : This function loads the Gstreamer pipeline
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Initialize a main loop
 * - creates a pipline object
 * - creates the sender pipline elements and receiver pipeline elements
 * - requests for Gstreamer bus
 * - sets the pipeline status as GST_STATE_READY
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool VoicecallPipeline::Load()
{
	XCALLLOGD("VoicecallPipeline::Load start\n");

	gst_init(0, 0);
	mainLoop = g_main_loop_new(NULL, FALSE);

	pipeline = gst_pipeline_new("voicecall-pipeline");

	data.thisPtr = this;

	if (!pipeline) {
		XCALLLOGE("load: One element could not be created. Exiting\n");
		return false;
	}

	if (!InitSenderPipeline()) {
		XCALLLOGE("InitSenderPipeline failed Exiting\n");
		return false;
	}

	if (!InitReceiverPipeline()) {
		XCALLLOGE("InitReceiverPipeline failed Exiting.\n");
		return false;
	}

	bus = gst_pipeline_get_bus(GST_PIPELINE (pipeline));

	bus_watch_id = gst_bus_add_watch(bus, bus_call_back, &data);
	gst_element_set_state(pipeline, GST_STATE_READY);

	XCALLLOGD("VoicecallPipeline::Load end\n");
	return true;

}

/**
 * ================================================================================
 * @fn : Play
 * @brief : This function starts playing the Gstreamer pipeline
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - sets the pipeline status as GST_STATE_PLAYING
 * - start a main loop
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool VoicecallPipeline::Play()
{
	XCALLLOGD("VoicecallPipeline::Play Start\n");

	GstStateChangeReturn ret = GST_STATE_CHANGE_FAILURE;

	ret = gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);
	XCALLLOGI("VoicecallPipeline Now playing...\n");

	GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(pipeline),GST_DEBUG_GRAPH_SHOW_ALL,"myplayer");

	g_main_loop_run (mainLoop);

	if (ret == GST_STATE_CHANGE_FAILURE) {
		XCALLLOGE("Unable to set the pipeline to the playing state.\n");
		gst_object_unref (pipeline);
		return false;
	}

	XCALLLOGD("VoicecallPipeline::Play end\n");

	return true;
}

/**
 * ================================================================================
 * @fn : Unload
 * @brief : This function unloads the Gstreamer pipeline
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - sets the Gstreamer state to GST_STATE_NULL
 * - removes the pipleine object
 * - stops the main loop
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool VoicecallPipeline::Unload()
{
	XCALLLOGD("VoicecallPipeline::unload function started \n");

	/* Out of the main loop, clean up nicely */
	gst_element_set_state(pipeline, GST_STATE_NULL);

	gst_object_unref (GST_OBJECT (pipeline));
	g_source_remove (bus_watch_id);
	g_main_loop_unref (mainLoop);
	return true;
}

/**
 * ================================================================================
 * @fn : on_pad_added_1
 * @brief : call back function on dynamic pad addition of gstreamer elements
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - connects two gstreamer elements in dynamic pad added event
 * @param[in] element  : Gstreamer element object
 * @param[in] pad      :  newly added pad details
 * @param[in] userData : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
void VoicecallPipeline::on_pad_added_1 (GstElement *rtpBin, GstPad *pad, gpointer userData)
{

	XCALLLOGD("VoicecallPipeline::on_pad_added_1 start\n");

	CallBackData * data = (CallBackData *) userData;
	gchar *name;
	name = gst_pad_get_name(pad);
	XCALLLOGD("VoicecallPipeline::on_pad_added_1 new pad %s was created\n", name);

	if (strstr(name, "recv_rtp_src_")) {
		GstPad *sinkpad;
		sinkpad = gst_element_get_static_pad (data->thisPtr->rtpDepay, "sink");
		gst_pad_link (pad, sinkpad);
		XCALLLOGI("VoicecallPipeline::on_pad_added_1 rtpBin rtpDepay is connected\n");
		gst_object_unref (sinkpad);
		gst_element_sync_state_with_parent(data->thisPtr->rtpDepay);
		gst_element_sync_state_with_parent(data->thisPtr->rtpBin);
	}
	g_free(name);

	XCALLLOGD("VoicecallPipeline::on_pad_added_1 end\n");
}

/**
 * ================================================================================
 * @fn : on_pad_added_2
 * @brief : call back function on dynamic pad addition of gstreamer elements
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - connects two gstreamer elements in dynamic pad added event
 * @param[in] element  : Gstreamer element object
 * @param[in] pad1     :  newly added pad details
 * @param[in] userData : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
void VoicecallPipeline::on_pad_added_2 (GstElement *element, GstPad *pad1, gpointer userData)
{
	XCALLLOGD("VoicecallPipeline::on_pad_added_2 start\n");

	gchar *name;
	CallBackData * data = (CallBackData *) userData;

	name = gst_pad_get_name(pad1);
	XCALLLOGD("VoicecallPipeline::on_pad_added_2  %s  created\n", name);

	/*we can now link the pads of source and sink elements*/

	XCALLLOGD("VoicecallPipeline::on_pad_added_2 Dynamic pad created, linking the rtp bin / udpSink\n");
	if (strcmp(name, "send_rtp_src_0") == 0) {
		GstPad *sinkpad;
		sinkpad = gst_element_get_static_pad (data->thisPtr->udpSink, "sink");
		gst_pad_link (pad1, sinkpad);
		gst_object_unref (sinkpad);
		XCALLLOGI("VoicecallPipeline::on_pad_added_2  %s  linking the rtp bin / udpSink is done \n", name);
	}
	g_free(name);

	gst_element_sync_state_with_parent(element);
	gst_element_sync_state_with_parent(data->thisPtr->udpSink);

	XCALLLOGD("VoicecallPipeline::on_pad_added_2 end\n");
}

/**
 * ================================================================================
 * @fn : gstBusCallbackHandle
 * @brief : call back function for error message handling
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - parses the error information
 * - Handles necessary action as per the error inforamtion
 * @param[in] bus     : Gstreamer asynchronous message bus subsystem object
 * @param[in] msg     :  objects to signal the application of pipeline events
 * @param[in] usrData : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
gboolean VoicecallPipeline::bus_call_back (GstBus *bus, GstMessage *msg, gpointer usrData)
{

	XCALLLOGD("VoicecallPipeline::bus_call_back start %d\n", GST_MESSAGE_TYPE (msg));
	CallBackData *data = (CallBackData *)usrData;
	switch (GST_MESSAGE_TYPE (msg)) {
		case GST_MESSAGE_EOS:
				gst_element_set_state (data->thisPtr->pipeline, GST_STATE_READY);
				g_main_loop_quit (data->thisPtr->mainLoop);
				break;
		case GST_MESSAGE_ERROR: {
				gchar *debug;
				GError *error;
				gst_message_parse_error (msg, &error, &debug);
				g_free (debug);
				XCALLLOGE("Error: %s\n", error->message);
				g_error_free (error);
				gst_element_set_state (data->thisPtr->pipeline, GST_STATE_READY);
				g_main_loop_quit (data->thisPtr->mainLoop);
				}
				break;
		case GST_MESSAGE_CLOCK_LOST:
				/* Get a new clock */
				gst_element_set_state (data->thisPtr->pipeline, GST_STATE_PAUSED);
				gst_element_set_state (data->thisPtr->pipeline, GST_STATE_PLAYING);
				break;
		default:
			break;
	}

	XCALLLOGD("VoicecallPipeline::bus_call_back end\n");

	return true;
}

/**
 * ================================================================================
 * @fn : pad_probe_cb
 * @brief : call back function for on data received in pad
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - parses the error information
 * - Handles necessary action as per the error inforamtion
 * @param[in] pad      : gstreamer pad on which data flow started
 * @param[in] info     : addtional pad information
 * @param[in] userData : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : enum value <0-4> GstPadProbeReturn
 * ================================================================================
 */
GstPadProbeReturn VoicecallPipeline::pad_probe_cb (GstPad * pad, GstPadProbeInfo * info, gpointer userData)
{
	CallBackData * data = (CallBackData *) userData;

	GstPad * sinkPad;
	gchar *name;
	XCALLLOGD("VoicecallPipeline::pad_probe_cb info.type=%u,  id = %lu\n ", info->type, info->id);

#if RECEIVE_FILESINK_ENABLED

	gst_bin_add_many(GST_BIN(data->thisPtr->pipeline), data->thisPtr->rtpDepay, data->thisPtr->audioDec, data->thisPtr->audioConvert, data->thisPtr->audioReSample, data->thisPtr->wavEnc, data->thisPtr->fileSink, NULL);

#else

	gst_bin_add_many(GST_BIN(data->thisPtr->pipeline), data->thisPtr->rtpDepay, data->thisPtr->audioDec, data->thisPtr->audioConvert, data->thisPtr->audioReSample, data->thisPtr->audioSink, NULL);

#endif

	g_signal_connect(data->thisPtr->rtpBin,"pad-added", G_CALLBACK(on_pad_added_1), data);
	sinkPad = gst_element_get_request_pad (data->thisPtr->rtpBin, "recv_rtp_sink_%u");
	name = gst_pad_get_name (sinkPad);
	XCALLLOGD("VoicecallPipeline::pad_probe_cb  A rtpBin %s is created\n", name);
	gst_element_link_pads (data->thisPtr->udpSrc, "src", data->thisPtr->rtpBin, name);

	g_free (name);
	gst_object_unref (GST_OBJECT (sinkPad));

#if RECEIVE_FILESINK_ENABLED

	if (!gst_element_link_many (data->thisPtr->rtpDepay, data->thisPtr->audioDec,data->thisPtr->audioConvert, data->thisPtr->audioReSample, data->thisPtr->wavEnc, data->thisPtr->fileSink, NULL)) {
		XCALLLOGW("VoicecallPipeline::pad_probe_cb Failed to link elements!");
	}

#else

	/* link */  // speekDecoder needs to be added on needed
	if (!gst_element_link_many (data->thisPtr->rtpDepay, data->thisPtr->audioDec,data->thisPtr->audioConvert, data->thisPtr->audioReSample, data->thisPtr->audioSink, NULL)) {
		XCALLLOGW("VoicecallPipeline::pad_probe_cb Failed to link elements!");
	}

#endif

	gst_pad_remove_probe (pad, GST_PAD_PROBE_INFO_ID (info));

	XCALLLOGD("VoicecallPipeline::pad_probe_cb end\n");
	return GST_PAD_PROBE_OK;
}

/**
 * ================================================================================
 * @fn : setSourceInformation
 * @brief : Fucntion to provide the IP, port, encoding scheme details to Gstreamer pipeline
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - stores the IP, port, encoding scheme values in member variables of pipeline
 * @param[in] xcall_debug_input   : Structure contains IP, Port, encoding scheme details
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
#ifdef DEBUG_ENABLED
void VoicecallPipeline::setSourceInformation(xcall_debug_input input)
{
	this->input = input;
	XCALLLOGD("ip details are source: %s %u & Destination: %s %u", this->input.destIP.c_str(), this->input.destPort1, this->input.srcIP.c_str(), this->input.srcPort1);
}
#endif

} //temxcall

