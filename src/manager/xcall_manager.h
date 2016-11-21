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

#ifndef __TEMXCALL_XCALL_MANAGER_H__
#define __TEMXCALL_XCALL_MANAGER_H__

#include <glib.h>

#ifdef TIME_MEASURE
#include <time.h>
#endif

#include <xcall_export.h>
#include <PlayerFactory.h>

#include <xcall_service_server.h>
#include <xcall_service_client.h>
#include <xcallservice_logger.h>

#ifdef DEBUG_ENABLED
#include "xcall_debug.h"
#endif

typedef struct {
	gpointer object;
	gpointer invocation;
	gpointer skeleton;
	gpointer proxy;
	gpointer callbackData;
} CbUserDataStruct;

namespace temxcall {

class XCallServiceServer;
class XCallServiceClient;

class XcallManager {

public :
	XcallManager();
	~XcallManager();

	bool createPlayer(const char *callinfo);
	void removePlayer();
	void getPlayer(const char * playerName);

	bool startCall(const char *callinfo);
	bool conntectedCall();
	bool endCall();

#ifdef DEBUG_ENABLED
	void setSourceInformation(xcall_debug_input input);
#endif

	//g_main_loop
	bool mainServiceStart();
	bool mainServiceStop();

	void initValue();
	void resetPreviousCallSatus();
	bool registerServices(XCallServiceServer *pServer, XCallServiceClient *pClient );

	bool UpdatePremiumAudioDeviceStatus(CALL_DIRECTION_T direction);
	bool SetPremiumAudioSPKStatus(bool spkStatus);
	bool SetPremiumAudioMICStatus(bool micStatus);
	bool GetPremiumAudioSPKStatus(guint *spkStatus);
	bool GetPremiumAudioMICStatus(guint *micStatus);

	bool SetPremiumAudioInfo(bool spkStatus, bool micStatus);
	bool GetPremiumAudioInfo(guint *spkStatus, guint *micStatus);

	bool updateCallInfo(CallStatusInfo_t &callInfo);
	bool updateVoiceStatus(CallStatus_t &CallStatus, CallStatusInfo_t &updatedCallInfo, bool isSdnCall);

	bool notifyRescueStatusEvent(GVariant *arg_eCallStatus,
								GVariant *arg_bCallStatus,
								GVariant *arg_iCallStatus,
								GVariant *arg_sdnStatus,
								guint arg_backupAudioStatuss);
	void ServiceActivationSetRequest (guint arg_service, guint arg_action,
										GAsyncReadyCallback callback, gpointer user_data);
	void ServiceActivationSetResponseCb(GError * err, gpointer user_data);

	void CallHandlingSetRequest (guint arg_service, guint8 arg_action,
										GAsyncReadyCallback callback, gpointer user_data);
	void CallHandlingSetRequestResponseCb(GError * err, gpointer user_data);

	void SOSStatusResponseCb(GError * err, guint SosStatus, gpointer user_data);
	bool notifySOSStatusEvent(guint SosStatus);
	bool GetCarConfigInfoRequest(guint dataIndex);

	bool unitTest(char *testName, char *param1, char *param2);

	bool callStatusChanged(CallStatus_t *prevStatus, CallStatus_t* newStatus);

#ifdef TIME_MEASURE
	void setStartTime(clock_t time);
	void measureElapseTime(void);
#endif

	//void sendResponse(uint32_t opCode, const void *payload,  void *user_data);
private:

	AbstractPlayer *player;
	PLAYER_TYPE_T curPlayerType;

	GMainLoop *mainLoop;

	XCallServiceServer *svcServer;
	XCallServiceClient *svcClient;

	CallStatusInfo_t curCallInfo;

	CallStatus_t mPreviousCallStatus [4];

	guint16 audioMainConnctionID;

	guint isICallBtnPressed;

	SOS_STATUS_T mSosStatus;

#ifdef TIME_MEASURE
	clock_t baseTime;
#endif

#ifdef DEBUG_ENABLED
	xcall_debug_input input;
#endif

};

}   //namespace temxcall

#endif /* __TEMXCALL_XCALL_MANAGER_H__ */
