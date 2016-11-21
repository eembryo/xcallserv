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

#include <cstring>

#include "xcall_manager.h"

//#define USE_RINGTONE  //when ringtone is required.

namespace temxcall {

std::map<int, std::string> CALL_TYPE_MAPPING = {
		{CALL_TYPE_EMERGENCY_CALL,"emergency"},
		{CALL_TYPE_BREAKDOWN_CALL,"breakdown"},
		{CALL_TYPE_INFORMATION_CALL,"information"},
		{CALL_TYPE_SDN_CALL,"sdn"}
};

std::map<int, std::string> CALL_STATUS_MAPPING = {
		{CALL_STATUS_NONE,				"Unknown"},
		{CALL_STATUS_INITIALIZING,		"Initializing"},
		{CALL_STATUS_STANDBY,			"StandBy"},
		{CALL_STATUS_CALLING,			"Connecting"},
		{CALL_STATUS_INCOMING,			"Incoming"},
		{CALL_STATUS_CONNECTED,			"Connected"},
		{CALL_STATUS_ENDCALL,			"Disconnected"}
};

/**
 * ================================================================================
 * @fn : XcallManager
 * @brief : This is constructor function for XcallManager class
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Initializes the member variables
 * - Initialized a main loop
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
XcallManager::XcallManager()
{
	//for initializing
	initValue();
	resetPreviousCallSatus();

	player = NULL;
	svcServer = NULL;
	svcClient = NULL;

	//create G Main Loop
	mainLoop = g_main_loop_new(NULL,false);

	curPlayerType = PLAYER_TYPE_NONE;

	mSosStatus = SOS_STATUS_UNKNOWN;

	//flag ... whether icall button is pressed or not
	isICallBtnPressed=0;
}

/**
 * ================================================================================
 * @fn : ~XcallManager
 * @brief : This is destructor function for XcallManager class
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
XcallManager::~XcallManager()
{
	if(mainLoop)
		g_main_loop_unref(mainLoop);

	XCALLLOGI("Destructor");
}

/**
 * ================================================================================
 * @fn : initValue
 * @brief : Initialize function for member variables
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Initializes callId, callType, callStatus, PlayerType, PlayerStatus
 *   Speaker status, Mic status
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
void XcallManager::initValue()
{
	curCallInfo.callId = -1;
	curCallInfo.callType = CALL_TYPE_NONE ;
	curCallInfo.callStatus = CALL_STATUS_NONE;
	curCallInfo.playerType = PLAYER_TYPE_NONE;
	curCallInfo.playerStatus = PLAYER_STATUS_NONE;

	//as a default, premium audio use OK.
	curCallInfo.audioStatus.spkStatus = PREMIUM_AUDIO_STATUS_OK;
	curCallInfo.audioStatus.micStatus = PREMIUM_AUDIO_STATUS_OK;

	//interface with audio manager
	audioMainConnctionID = 0;

}

/**
 * ================================================================================
 * @fn : resetPreviousCallSatus
 * @brief : reset function for call status
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - resets all the previous call information stored
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
void XcallManager::resetPreviousCallSatus()
{
	XCALLLOGD("Previous call status are cleared and reset");
	for (int i=0; i<4; i++) {
		mPreviousCallStatus[i].status = StatusNotActive;
		mPreviousCallStatus[i].callId = i+1;
		mPreviousCallStatus[i].voiceStatus = VoiceStatusNoConnection;
		mPreviousCallStatus[i].voiceSource = SourceStatusUnidentified;
		mPreviousCallStatus[i].messageStatus = MessageStatusNotSent;
		mPreviousCallStatus[i].buttonStatus = ButtonAllReleased;
		mPreviousCallStatus[i].psapConfirmStatus = PSAPStatusConfirmNotRequired;
		mPreviousCallStatus[i].sbStatus = StandbyStatusNotActive;
	}
	mPreviousCallStatus[3].callId = 0; // i call case
}

/**
 * ================================================================================
 * @fn : getPlayer
 * @brief : Creates the player instance
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Creates the player instance
 * @param[in] playerName : registered player name string for instantiation
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
void XcallManager::getPlayer(const char *playerName)
{
	//AbstractPlayer *player = sPlayerBaseFactory::GetInstance().CreateObject("VoiceCallPlayer");
	if (playerName)
		player = sPlayerBaseFactory::GetInstance().CreateObject(playerName);
}

/**
 * ================================================================================
 * @fn : removePlayer
 * @brief : Dummy function
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
void XcallManager::removePlayer()
{

}

/**
 * ================================================================================
 * @fn : createPlayer
 * @brief : Function decides the player name by call status information
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - parses the call status information
 * - requests player creation with appropriate name
 * @param[in] callinfo : call status information
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ===================================================================================
 */
bool XcallManager::createPlayer(const char *callinfo)
{
	bool ret=false;

	if ((!strcmp(callinfo,"Incoming")) || (!strcmp(callinfo,"Connecting"))) {

#ifdef USE_RINGTONE
		XCALLLOGD("RingtonePlayer");

		//TODO : Ringtone will be added
		//player = sPlayerBaseFactory::GetInstance().CreateObject("RingtonePlayer");
		getPlayer("RingtonePlayer");
		curPlayerType = PLAYER_TYPE_RINGTONE;

		XCALLLOGD("RingtonePlayer is created");
#else
		XCALLLOGI("VoicecallPlayer");

		//player = sPlayerBaseFactory::GetInstance().CreateObject("VoicecallPlayer");
		getPlayer("VoicecallPlayer");
		curPlayerType = PLAYER_TYPE_VOICECALL;

		XCALLLOGD("VoicecallPlayer is created");
#endif

	} else if (!strcmp(callinfo,"Connected")) {
		if (curPlayerType != PLAYER_TYPE_VOICECALL) {
			//player = sPlayerBaseFactory::GetInstance().CreateObject("VoicecallPlayer");
			getPlayer("VoicecallPlayer");
			curPlayerType = PLAYER_TYPE_VOICECALL;
		}
		XCALLLOGI("VoiceCallPlayer is created");
	} else {
		if (!strcmp(callinfo,"unittest-spk")) {
			XCALLLOGD("UnitTest-SPK is created");
			//player = sPlayerBaseFactory::GetInstance().CreateObject("UnitTest-SPK");
			getPlayer("UnitTest-SPK");
			curPlayerType =PLAYER_TYPE_UNITTEST;
		} else if(!strcmp(callinfo,"unittest-mic")) {
			XCALLLOGD("UnitTest-MIC is created");
			//player = sPlayerBaseFactory::GetInstance().CreateObject("UnitTest-MIC");
			getPlayer("UnitTest-MIC");
			curPlayerType =PLAYER_TYPE_UNITTEST;
		} else if(!strcmp(callinfo,"unittest-rtp")) {
			XCALLLOGD("UnitTest-RTP is created");
			//player = sPlayerBaseFactory::GetInstance().CreateObject("UnitTest-RTP");
			getPlayer("UnitTest-RTP");
			curPlayerType =PLAYER_TYPE_UNITTEST;
		} else {
			XCALLLOGE("ERR -- Not Match [%s]",callinfo);
		}
	}

	return ret;
}

/**
 * ================================================================================
 * @fn : startCall
 * @brief : updates player, call information as per the start call event
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - checks any player is already in playing status and removes it
 * - requests new player instance
 * @param[in] callinfo : call status information
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ===================================================================================
 */
bool XcallManager::startCall(const char *callinfo)
{
	bool ret = true;


	//check player Status
	if(curCallInfo.playerStatus == PLAYER_STATUS_PLAY)
	{
		XCALLLOGI(">>> [[NOTICE]] <<< create New Player without Stop of previous Player ");
		player->Unload();
		removePlayer();
		curCallInfo.playerStatus = PLAYER_STATUS_STOP;
	}

	//create player
#if 0

	XCALLLOGD("createPlayer with [%s]",callinfo);
	svcClient->clientCalling();

	curCallInfo.callStatus == CALL_STATUS_CALLING;
	curCallInfo.callType = CALL_TYPE_EMERGENCY_CALL;
	curCallInfo.callId = 0;

	std::string callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];

	svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId,curCallInfo.callType,"Calling");
#else
	XCALLLOGI("createPlayer with [%s] ", callinfo);
	createPlayer(callinfo);

#ifdef DEBUG_ENABLED
	XCALLLOGD("[XcallManager] startCall | player->source information is called");
	player->setSourceInformation(this->input);
#endif

	player->Load();
	curCallInfo.playerStatus = PLAYER_STATUS_PLAY;

	XCALLLOGI("[PlayerStatus:%d] call player->load",curCallInfo.playerStatus);
#endif

	XCALLLOGD("createPlayer");

	return ret;
}

/**
 * ================================================================================
 * @fn : conntectedCall
 * @brief : updates player, call information as per the connected call event
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - checks any player is already in playing status and removes it
 * - requests new player instance
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ===================================================================================
 */
bool XcallManager::conntectedCall()
{
	bool ret = true;
	XCALLLOGD("start");
#if 0
		svcClient->clientConnected();

		curCallInfo.callStatus == CALL_STATUS_CONNECTED;
		curCallInfo.callType = CALL_TYPE_EMERGENCY_CALL;
		curCallInfo.callId = 0;

		std::string callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];

		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId,curCallInfo.callType,callStatusInformation.c_str());
#else

	if (curPlayerType == PLAYER_TYPE_RINGTONE) {
		//unload & remove ringtone player
		player->Unload();
		removePlayer();

		//create voicecall player
		createPlayer("Connected");
		player->Play();

	} else if(curPlayerType == PLAYER_TYPE_VOICECALL) {
		player->Play();
	} else {

		if(curPlayerType == PLAYER_TYPE_UNITTEST) {
			player->Play();
		} else {
			XCALLLOGE("ERR -- NO player is available to play");
		}
	}
#endif
	return ret;
}

/**
 * ================================================================================
 * @fn : endCall
 * @brief : updates player, call information as per the endCall event
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - unloads the player instance and removes it
 * - updates the member variables
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::endCall()
{
	bool ret = true;

#ifdef ENABLE_UNITTEST_ASK_MMUS_API

	g_print("endCall is called \n");
	svcClient->getDeviceStatusFromMMUS();
#else
#if 0
		svcClient->clientEnd();

		curCallInfo.callStatus == CALL_STATUS_ENDCALL;
		curCallInfo.callType = CALL_TYPE_EMERGENCY_CALL;
		curCallInfo.callId = 0;

		std::string callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];

		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId,curCallInfo.callType,callStatusInformation.c_str());
#else
	if ((curCallInfo.playerStatus != PLAYER_STATUS_STOP) && (curCallInfo.playerStatus != PLAYER_STATUS_NONE)) {
		XCALLLOGI("[PlayerStatus:%d] call player->unload",curCallInfo.playerStatus);
		player->Unload();
	}else {
		XCALLLOGI("[PlayerStatus:%d] ignore player->unload",curCallInfo.playerStatus);
	}

	curPlayerType = PLAYER_TYPE_NONE;
	curCallInfo.playerStatus = PLAYER_STATUS_STOP;
#endif
#endif
	return ret;
}

/**
 * ================================================================================
 * @fn : mainServiceStart
 * @brief : Starts the main loop
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Starts the main loop
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
//g_main_loop
bool XcallManager::mainServiceStart()
{
	bool ret=true;

	XCALLLOGI("start");

#ifdef TIME_MEASURE
	XCALLLOGI("[TIME] before GMainLoop\n");
	measureElapseTime();
#endif

	g_main_loop_run(mainLoop);

	return ret;
}

/**
 * ================================================================================
 * @fn : mainServiceStop
 * @brief : stops the main loop
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - stops the main loop
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::mainServiceStop()
{
	bool ret=true;

	g_main_loop_quit(mainLoop);

	return ret;
}

/**
 * ================================================================================
 * @fn : registerServices
 * @brief : register the server and client handlers
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - stores the server and client handlers in memeber variables
 * @param[in] pServer   : handler of XCallServiceServer object
 * @param[in] pClient   : handler of XCallServiceClient object
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::registerServices(XCallServiceServer *pServer, XCallServiceClient *pClient )
{
	bool ret=true;

	svcServer = pServer;
	svcClient = pClient;

	XCALLLOGI("(svcServer)%p | (svcClient)%p | (mgr)%p",svcServer,svcClient,this);

	// TO DO: Enable/modify the below function when the TEM2 status ready implementation is done
	//svcClient->SOSStatusHandlingRequest(nullptr, nullptr);

	// TO DO: Enable/modify the below function when vehicle daemon ready sync sequence is adapted
	//GetCarConfigInfoRequest(CARCONFIG_ASSTSRV);
	//GetCarConfigInfoRequest(CARCONFIG_TELEMODULE);

	return ret;
}

/**
 * ================================================================================
 * @fn : notifyRescueStatusEvent
 * @brief : Call State handler function
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Parses the information from Rescue status event for each type of call
 * - Identifies the which call type
 * @param[in] arg_eCallStatus       : Emergency call status information in glib object
 * @param[in] arg_bCallStatus       : Breakdown call status information in glib object
 * @param[in] arg_iCallStatus       : Information call status information in glib object
 * @param[in] arg_sdnStatus         : SDN call status information in glib object
 * @param[in] arg_backupAudioStatus : Backup audio device status in glib object
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ===================================================================================
 */
bool XcallManager::notifyRescueStatusEvent(GVariant *arg_eCallStatus,
											GVariant *arg_bCallStatus,
											GVariant *arg_iCallStatus,
											GVariant *arg_sdnStatus,
											guint arg_backupAudioStatus)
{

	bool ret = false;
	CallStatusInfo_t updatedCallInfo = {0,};

	CallStatus_t eCallStatus;
	CallStatus_t bCallStatus;
	CallStatus_t iCallStatus;
	CallStatus_t sdnCallStatus;
	guint backupAudioStatus = 0;
	bool isSdnCall = false;

	/*
		RescueStatus ::= ENUMERATED { disabled (0), notActive (1), serviceNotAvailable (2), active (3), terminated (4) }
		raStatus RescueStatus,
		eaStatus RescueStatus,
		sdnStatus RescueStatus,
	*/
	//1st, check rescuestatus for calltype

	g_variant_get(arg_eCallStatus, "(uuuuuuuu)", &eCallStatus.status, &eCallStatus.callId, &eCallStatus.voiceStatus, &eCallStatus.voiceSource,
												&eCallStatus.messageStatus, &eCallStatus.buttonStatus, &eCallStatus.psapConfirmStatus, &eCallStatus.sbStatus);

	g_variant_get(arg_bCallStatus, "(uuuuuuuu)", &bCallStatus.status, &bCallStatus.callId, &bCallStatus.voiceStatus, &bCallStatus.voiceSource,
												&bCallStatus.messageStatus, &bCallStatus.buttonStatus, &bCallStatus.psapConfirmStatus, &bCallStatus.sbStatus);

	g_variant_get(arg_iCallStatus, "(uuuuuuuu)", &iCallStatus.status, &iCallStatus.callId, &iCallStatus.voiceStatus, &iCallStatus.voiceSource,
												&iCallStatus.messageStatus, &iCallStatus.buttonStatus, &iCallStatus.psapConfirmStatus, &iCallStatus.sbStatus);

	g_variant_get(arg_sdnStatus, "(uuuuuuuu)", &sdnCallStatus.status, &sdnCallStatus.callId, &sdnCallStatus.voiceStatus, &sdnCallStatus.voiceSource,
												&sdnCallStatus.messageStatus, &sdnCallStatus.buttonStatus, &sdnCallStatus.psapConfirmStatus, &sdnCallStatus.sbStatus);
	backupAudioStatus = arg_backupAudioStatus;


	XCALLLOGI("E-Call: %d, %d, %d, %d, %d, %d, %d, %d \n", eCallStatus.status, eCallStatus.callId, eCallStatus.voiceStatus, eCallStatus.voiceSource,
			eCallStatus.messageStatus, eCallStatus.buttonStatus, eCallStatus.psapConfirmStatus, eCallStatus.sbStatus);

	XCALLLOGI("B-Call: %d, %d, %d, %d, %d, %d, %d, %d\n", bCallStatus.status, bCallStatus.callId, bCallStatus.voiceStatus, bCallStatus.voiceSource,
			bCallStatus.messageStatus, bCallStatus.buttonStatus, bCallStatus.psapConfirmStatus, bCallStatus.sbStatus);
	XCALLLOGI("I-Call: %d, %d, %d, %d, %d, %d, %d, %d\n", iCallStatus.status, iCallStatus.callId, iCallStatus.voiceStatus, iCallStatus.voiceSource,
			iCallStatus.messageStatus, iCallStatus.buttonStatus, iCallStatus.psapConfirmStatus, iCallStatus.sbStatus);
	XCALLLOGI("SND-Call: %d, %d, %d, %d, %d, %d, %d, %d\n", sdnCallStatus.status, sdnCallStatus.callId, sdnCallStatus.voiceStatus, sdnCallStatus.voiceSource,
			sdnCallStatus.messageStatus, sdnCallStatus.buttonStatus, sdnCallStatus.psapConfirmStatus, sdnCallStatus.sbStatus);
	XCALLLOGI("Backup audio status = %d \n", backupAudioStatus);

	XCALLLOGI(" >>> Current : %d %d %d %d ",curCallInfo.callType,curCallInfo.callStatus,curCallInfo.playerType,curCallInfo.playerStatus);

	if (bCallStatus.status == StatusDisabled && eCallStatus.status == StatusDisabled && sdnCallStatus.status == StatusDisabled && iCallStatus.status == StatusDisabled) {
		if (curCallInfo.callStatus != CALL_STATUS_NONE) {
			svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, "Disconnected");

			//release  mainConnectionID from Audio Manager
			if(audioMainConnctionID >0) {
				ret = svcClient->releaseAudioMangerResource(audioMainConnctionID);
				if (ret) {
					XCALLLOGI("release mainConnectionID(%d) from Audio Manager", audioMainConnctionID);
				} else {
					XCALLLOGE("ERROR mainConnectionID(%d) release fail", audioMainConnctionID);
				}
				audioMainConnctionID =0;
			}
			endCall();
		}

		XCALLLOGI("*********************MODEM IS RESTARTED clear the states***********************\n");
		initValue();
		resetPreviousCallSatus();
	} else if (callStatusChanged(&mPreviousCallStatus[0] , &eCallStatus)) {
		XCALLLOGI("------------------ E CALL STATUS CHANGED ------------------\n");
		memcpy(&mPreviousCallStatus[0], &eCallStatus, sizeof(CallStatus_t));
		if (eCallStatus.status == StatusActive || eCallStatus.sbStatus == StandbyStatusActive || eCallStatus.sbStatus == StandbyStatusCancel || eCallStatus.buttonStatus == ButtonPressed ||
																((curCallInfo.callType  == CALL_TYPE_EMERGENCY_CALL) && (curCallInfo.callStatus == CALL_STATUS_INITIALIZING) && (eCallStatus.buttonStatus == ButtonReleased))) {
			// E-Call
			XCALLLOGI("calltype - E-Call @@\n");
			updatedCallInfo.callType = CALL_TYPE_EMERGENCY_CALL;
			updatedCallInfo.callId = eCallStatus.callId;
			ret = updateVoiceStatus(eCallStatus, updatedCallInfo, isSdnCall);
		}

	} else if (callStatusChanged(&mPreviousCallStatus[1] , &bCallStatus)) {
		XCALLLOGI("------------------ B CALL STATUS CHANGED ------------------\n");
		memcpy(&mPreviousCallStatus[1], &bCallStatus, sizeof(CallStatus_t));
		if (bCallStatus.status == StatusActive || bCallStatus.sbStatus == StandbyStatusActive || bCallStatus.sbStatus == StandbyStatusCancel || bCallStatus.buttonStatus == ButtonPressed ||
															((curCallInfo.callType  == CALL_TYPE_BREAKDOWN_CALL) && (curCallInfo.callStatus == CALL_STATUS_INITIALIZING) && (bCallStatus.buttonStatus == ButtonReleased))) {

		#if 1	//workaround
			//get wrong ip command during Ecall, make the below for filtering
			if ((curCallInfo.callType  == CALL_TYPE_EMERGENCY_CALL) && (bCallStatus.status == StatusTerminated )) {

				XCALLLOGI("ERROR : wrong IP Command --- Current(E-Call) but got Bcall cmd from TEM2 (ignore this) \n");
				ret = false;
			} else {
				//B-Call
				XCALLLOGI("calltype - B-Call @@@\n");
				updatedCallInfo.callType = CALL_TYPE_BREAKDOWN_CALL;
				updatedCallInfo.callId = bCallStatus.callId;
				ret = updateVoiceStatus(bCallStatus, updatedCallInfo, isSdnCall);
			}
		#else
			//B-Call
			XCALLLOGI("calltype - B-Call\n");
			updatedCallInfo.callType = CALL_TYPE_BREAKDOWN_CALL;
			updatedCallInfo.callId = bCallStatus.callId;
			ret = updateVoiceStatus(bCallStatus, updatedCallInfo, isSdnCall);
		#endif
		}else if ((curCallInfo.callStatus== CALL_STATUS_STANDBY) && (bCallStatus.status==StatusTerminated) && (bCallStatus.voiceStatus==VoiceStatusEndedCall)) {
			// B-Call -- call switch -> Bcall end condition
			XCALLLOGI("calltype - B-Call(call switch : bcall end condition) \n");

			updatedCallInfo.callType = CALL_TYPE_BREAKDOWN_CALL;
			updatedCallInfo.callId = bCallStatus.callId;
		//	ret = updateVoiceStatus(iCallStatus, updatedCallInfo, isSdnCall);
			updatedCallInfo.callStatus = CALL_STATUS_ENDCALL;

			//check premiumAudio flag
			if((curCallInfo.audioStatus.spkStatus == PREMIUM_AUDIO_STATUS_OK) && (curCallInfo.audioStatus.micStatus == PREMIUM_AUDIO_STATUS_OK)){

				XCALLLOGI("(CallSwitch)release Premium Audio");
				endCall();

		//		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
				//release  mainConnectionID from Audio Manager
				ret = svcClient->releaseAudioMangerResource(audioMainConnctionID);
				if (ret) {
					XCALLLOGI("(CallSwitch)release mainConnectionID(%d) from Audio Manager", audioMainConnctionID);
				} else {
					XCALLLOGE("(CallSwitch)ERROR mainConnectionID(%d) release fail", audioMainConnctionID);
				}
				audioMainConnctionID =0;
			} else {
				XCALLLOGI("(CallSwitch)use Tem sid Backup Audio");
		//		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
			}
			initValue();

		}
	} else if (callStatusChanged(&mPreviousCallStatus[3] , &sdnCallStatus)) {
		XCALLLOGI("------------------ SDN CALL STATUS CHANGED ------------------\n");
		memcpy(&mPreviousCallStatus[3], &sdnCallStatus, sizeof(CallStatus_t));
		if (sdnCallStatus.status == StatusActive || sdnCallStatus.sbStatus == StandbyStatusActive || sdnCallStatus.sbStatus == StandbyStatusCancel || sdnCallStatus.buttonStatus == ButtonPressed ||
																			((curCallInfo.callType == CALL_TYPE_SDN_CALL) && (curCallInfo.callStatus == CALL_STATUS_INITIALIZING) && (sdnCallStatus.buttonStatus == ButtonReleased))) {
				// SDN-Call
				// SDN Call is same with e-call
				XCALLLOGI("calltype - SDN-Call \n");
				updatedCallInfo.callType = CALL_TYPE_SDN_CALL;
				updatedCallInfo.callId = sdnCallStatus.callId;
				isSdnCall = true;
				ret = updateVoiceStatus(sdnCallStatus, updatedCallInfo, isSdnCall);
		}
	} else if (callStatusChanged(&mPreviousCallStatus[2] , &iCallStatus)) {
		XCALLLOGI("------------------ I CALL STATUS CHANGED ------------------\n");
		memcpy(&mPreviousCallStatus[2], &iCallStatus, sizeof(CallStatus_t));
		if (iCallStatus.status == StatusServiceNotAvailable) {
				// I-Call
				XCALLLOGI("calltype - I-Call Not available\n");
				svcServer->NotifyErrorInformation("GDBus.Error:org.freedesktop.DBus.Error.Failed: Service not available");
		} else if (iCallStatus.status == StatusActive) {
			// I-Call
			XCALLLOGI("calltype - I-Call\n");
			updatedCallInfo.callType = CALL_TYPE_INFORMATION_CALL;
			updatedCallInfo.callId = iCallStatus.callId;
			ret = updateVoiceStatus(iCallStatus, updatedCallInfo, isSdnCall);
		} else if ((iCallStatus.status==StatusTerminated) && (iCallStatus.voiceStatus==VoiceStatusEndedCall)) {
			// I-Call -- call switch -> icall end condition
			XCALLLOGI("calltype - I-Call(call switch : icall end condition) \n");

			updatedCallInfo.callType = CALL_TYPE_INFORMATION_CALL;
			updatedCallInfo.callId = iCallStatus.callId;
		//	ret = updateVoiceStatus(iCallStatus, updatedCallInfo, isSdnCall);
			updatedCallInfo.callStatus = CALL_STATUS_ENDCALL;

			//check premiumAudio flag
			if((curCallInfo.audioStatus.spkStatus == PREMIUM_AUDIO_STATUS_OK) && (curCallInfo.audioStatus.micStatus == PREMIUM_AUDIO_STATUS_OK)){

				XCALLLOGI("(CallSwitch)release Premium Audio");
				endCall();

		//		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
				//release  mainConnectionID from Audio Manager
				ret = svcClient->releaseAudioMangerResource(audioMainConnctionID);
				if (ret) {
					XCALLLOGI("(CallSwitch)release mainConnectionID(%d) from Audio Manager", audioMainConnctionID);
				} else {
					XCALLLOGE("(CallSwitch)ERROR mainConnectionID(%d) release fail", audioMainConnctionID);
				}
				audioMainConnctionID =0;
			} else {
				XCALLLOGI("(CallSwitch)use Tem sid Backup Audio");
		//		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
			}
			initValue();

		}
	} else {

		//clear button flag.
		isICallBtnPressed=0;

		XCALLLOGE("ERROR No calls changed");
		return ret;
	}

	if (ret) {
		ret = updateCallInfo(updatedCallInfo);
	}

	//clear button flag.
	isICallBtnPressed=0;

	XCALLLOGI(" >>> Next : %d %d %d %d (iCall btn flag=%d) ",curCallInfo.callType,curCallInfo.callStatus,curCallInfo.playerType,curCallInfo.playerStatus,isICallBtnPressed);

	return ret;

}

/**
 * ================================================================================
 * @fn : updateVoiceStatus
 * @brief : Function decides the call status from various information of call
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Parses the particular call information and decides the call status
 * - Updates the call status to local call status information variable
 * @param[in] CallStatusInfo  : Call status information
 * @param[in] updatedCallInfo : Locally stored call status information
 * @param[in] isSdnCall       : status variable about sdn call
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ===================================================================================
 */
bool XcallManager::updateVoiceStatus(CallStatus_t &CallStatusInfo, CallStatusInfo_t &updatedCallInfo, bool isSdnCall)
{
	XCALLLOGI("updateVoiceStatus start\n");

	if (CallStatusInfo.buttonStatus == ButtonPressed && CallStatusInfo.sbStatus == StandbyStatusNotActive && CallStatusInfo.voiceStatus == VoiceStatusNoConnection) {
		// Initializing state
		XCALLLOGI("callStatus - Initial\n");
		updatedCallInfo.callStatus = CALL_STATUS_INITIALIZING;
	} else if (CallStatusInfo.buttonStatus == ButtonReleased && CallStatusInfo.sbStatus == StandbyStatusNotActive && CallStatusInfo.voiceStatus == VoiceStatusNoConnection) {
		// Initializing state -> call end
		// If condition is work around for avoiding StandBy to Initial cancel
		if (curCallInfo.callStatus == CALL_STATUS_INITIALIZING) {
			XCALLLOGI("callStatus - Initial - Cancel \n");
			updatedCallInfo.callStatus = CALL_STATUS_ENDCALL;
		} else {
			XCALLLOGI("ERROR : no related callStatus - ignore this Command \n");
			return false;
		}
	} else if (!isSdnCall && CallStatusInfo.sbStatus == StandbyStatusActive && CallStatusInfo.voiceStatus == VoiceStatusNoConnection) {
		// StandBy mode state
		XCALLLOGI("callStatus - Standby \n");
		updatedCallInfo.callStatus = CALL_STATUS_STANDBY;
	} else if (!isSdnCall && CallStatusInfo.sbStatus == StandbyStatusCancel && CallStatusInfo.voiceStatus == VoiceStatusNoConnection) {
		// StandBy mode cancel
		XCALLLOGI("callStatus - Standby - Cancel \n");
		updatedCallInfo.callStatus = CALL_STATUS_ENDCALL;
	} else {
		switch (CallStatusInfo.voiceStatus) {
			case VoiceStatusConnectingCSC: //connectingCSC(1)
			case VoiceStatusConnectingPSAP: //connectingPSAP(2)
				{
					XCALLLOGI("callStatus - Calling\n");
					updatedCallInfo.callStatus = CALL_STATUS_CALLING;
				}
				break;
			case VoiceStatusConnectedCSC:	//connectedCSC (3)
			case VoiceStatusConnectedPSAP:	//connectedPSAP (4)
			case VoiceStatusConnectedCall:	//connectedCall (6)
			case VoiceStatusConnectedIncoming:	//connectedIncoming (7)
				{
					XCALLLOGI("callStatus - Connected\n");
					updatedCallInfo.callStatus = CALL_STATUS_CONNECTED;
				}
				break;
			case VoiceStatusIncomingCall: // incomingCall (5)
				{
					XCALLLOGI("callStatus - Incoming\n");
					updatedCallInfo.callStatus = CALL_STATUS_INCOMING;
				}
				break;
			case VoiceStatusNoConnection: //noConnection (0)
				{
					XCALLLOGI("callStatus - NoConnection\n");
					updatedCallInfo.callStatus = CALL_STATUS_NONE;
				}
				break;
			case VoiceStatusEndedCall: //endedcall (8)
				{
					XCALLLOGI("callStatus - VoiceStatusEndedCall\n");
					updatedCallInfo.callStatus = CALL_STATUS_ENDCALL;
				}
				break;
			default :
				{
					XCALLLOGE("ERROR callStatus - No Match\n");
					updatedCallInfo.callStatus = CALL_STATUS_NONE;
				}
				break;
		}
	}

	XCALLLOGI("updateVoiceStatus %d end \n", updatedCallInfo.callStatus);
	return true;
}

/**
 * ================================================================================
 * @fn : updateCallInfo
 * @brief : Function that maintains the call state sequence and notifications
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Check the call state sequence by previous status and current status
 * - Emit the call status information on valid status changes
 * - Request audio manager for audio resources
 * - Request for voice pipeline for corresponding status
 * @param[in] CallStatusInfo  : Call status information
 * @param[in] updatedCallInfo : Locally stored call status information
 * @param[in] isSdnCall       : status variable about sdn call
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ===================================================================================
 */
bool XcallManager::updateCallInfo(CallStatusInfo_t &callInfo)
{
	bool ret = true;
	std::string callStatusInformation;

	XCALLLOGI("curCallInfo.callStatus = %d , new callInfo.callStatus = %d\n", curCallInfo.callStatus, callInfo.callStatus);
	//1st, check calltype
	if (curCallInfo.callType != callInfo.callType) {
		curCallInfo.callType = callInfo.callType;
	}

	//2nd, check status
	if ( ((curCallInfo.callStatus == CALL_STATUS_NONE || curCallInfo.callStatus == CALL_STATUS_STANDBY || curCallInfo.callStatus == CALL_STATUS_INITIALIZING) && (callInfo.callStatus == CALL_STATUS_INCOMING))
		|| ((curCallInfo.callStatus == CALL_STATUS_NONE || curCallInfo.callStatus == CALL_STATUS_STANDBY || curCallInfo.callStatus == CALL_STATUS_INITIALIZING) && (callInfo.callStatus == CALL_STATUS_CALLING))) {

		//prev : end --> current : incoming or outgoing  :: update to calling or incoming
		curCallInfo.callStatus = callInfo.callStatus;

		//register callId, this callId will be used on callhandling API through callapp.
		curCallInfo.callId = callInfo.callId;

		//TODO : need to check CEVT requirement (no req. until now)
		//
		//		   play ringtone in here
		//		(if there is any req. from CEVT about ringtone play)
#if 1
		callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];
		XCALLLOGI(" -> INCOMING or CALLING %d\n", curCallInfo.callStatus);

		//check premiumAudio flag
		if ((curCallInfo.audioStatus.spkStatus == PREMIUM_AUDIO_STATUS_OK) && (curCallInfo.audioStatus.micStatus == PREMIUM_AUDIO_STATUS_OK)){

			XCALLLOGI("[Status:%s]use Premium Audio",callStatusInformation.c_str());

			//acquire mainConnectionID from Audio Manager
			ret = svcClient->acquireAudioMangerResource(&audioMainConnctionID, curCallInfo.callType);

			if (ret) {
				XCALLLOGI("get mainConnectionID(%d) from Audio Manager", audioMainConnctionID);
				startCall(callStatusInformation.c_str());
				svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
				conntectedCall();
			} else {
				XCALLLOGE("ERROR mainConnectionID(%d) is invalid", audioMainConnctionID);
			}
		} else {
			XCALLLOGI("[Status:%s]use Tem side Backup Audio",callStatusInformation.c_str());
			svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
		}
#else
		callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];
		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
#endif
	} else if ( ((curCallInfo.callStatus == CALL_STATUS_INCOMING) && (callInfo.callStatus == CALL_STATUS_CONNECTED))
		|| ((curCallInfo.callStatus == CALL_STATUS_CALLING) && (callInfo.callStatus == CALL_STATUS_CONNECTED))) {

		//prev : incoming or outgoing --> current : connected  :: update to connected
		curCallInfo.callStatus = callInfo.callStatus;
		curCallInfo.callId = callInfo.callId;

		callStatusInformation = CALL_STATUS_MAPPING[CALL_STATUS_CONNECTED];
		XCALLLOGI(" -> CONNECTED %d\n", curCallInfo.callStatus);

#if 1
		//check premiumAudio flag
		if ((curCallInfo.audioStatus.spkStatus == PREMIUM_AUDIO_STATUS_OK) && (curCallInfo.audioStatus.micStatus == PREMIUM_AUDIO_STATUS_OK)){
			XCALLLOGI("[Status:%s]use Premium Audio",callStatusInformation.c_str());
		}else {
			XCALLLOGI("[Status:%s]use Tem side Backup Audio",callStatusInformation.c_str());
		}
		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
#else

		//check premiumAudio flag
		if ((curCallInfo.audioStatus.spkStatus == PREMIUM_AUDIO_STATUS_OK) && (curCallInfo.audioStatus.micStatus == PREMIUM_AUDIO_STATUS_OK)){


			XCALLLOGI("use Premium Audio");


			//acquire mainConnectionID from Audio Manager
			ret = svcClient->acquireAudioMangerResource(&audioMainConnctionID);

			if (ret) {

				XCALLLOGI("get mainConnectionID(%d) from Audio Manager", audioMainConnctionID);
				startCall(callStatusInformation.c_str());
				svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
				conntectedCall();
			} else {
				XCALLLOGE("ERROR mainConnectionID(%d) is invalid", audioMainConnctionID);
			}

		} else {
			XCALLLOGI("use Tem side Backup Audio");
			svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
		}
#endif
	} else if( ((curCallInfo.callStatus == CALL_STATUS_CONNECTED || curCallInfo.callStatus == CALL_STATUS_INCOMING ||curCallInfo.callStatus == CALL_STATUS_CALLING)
				&& (callInfo.callStatus == CALL_STATUS_ENDCALL))) {

		//prev : connected --> current : end   :: update to end
		curCallInfo.callStatus = callInfo.callStatus;
		curCallInfo.callId = callInfo.callId;
		callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];
		XCALLLOGI("CONNECTED or INCOMING or CALLING --> CALL_STATUS_ENDCALL  %d\n", curCallInfo.callStatus);
		//check premiumAudio flag
		if((curCallInfo.audioStatus.spkStatus == PREMIUM_AUDIO_STATUS_OK) && (curCallInfo.audioStatus.micStatus == PREMIUM_AUDIO_STATUS_OK)){

			XCALLLOGI("release Premium Audio");
			endCall();

			svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
			//release  mainConnectionID from Audio Manager
			ret = svcClient->releaseAudioMangerResource(audioMainConnctionID);
			if (ret) {
				XCALLLOGI("release mainConnectionID(%d) from Audio Manager", audioMainConnctionID);
			} else {
				XCALLLOGE("ERROR mainConnectionID(%d) release fail", audioMainConnctionID);
			}
			audioMainConnctionID =0;
		} else {
			XCALLLOGI("use Tem sid Backup Audio");
			svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());

			endCall();
		}
		initValue();

	} else if (((curCallInfo.callStatus == CALL_STATUS_STANDBY || curCallInfo.callStatus == CALL_STATUS_INITIALIZING)
				&& (callInfo.callStatus == CALL_STATUS_ENDCALL))) {
		curCallInfo.callStatus = callInfo.callStatus;
		curCallInfo.callId = callInfo.callId;
		XCALLLOGI("STANDBY or INITIALIZING --> CALL_STATUS_ENDCALL  %d\n", curCallInfo.callStatus);
		callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];
		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
		initValue();
	} else if ((curCallInfo.callStatus != CALL_STATUS_STANDBY) && (callInfo.callStatus == CALL_STATUS_STANDBY)) {
		curCallInfo.callStatus = callInfo.callStatus;
		curCallInfo.callId = callInfo.callId;
		XCALLLOGI("CALL_STATUS_STANDBY %d\n", curCallInfo.callStatus);
		callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];
		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
	} else if ((callInfo.callStatus == CALL_STATUS_INITIALIZING)) {
		curCallInfo.callStatus = callInfo.callStatus;
		curCallInfo.callId = callInfo.callId;
		XCALLLOGI("CALL_STATUS_INITIALIZING %d\n", curCallInfo.callStatus);
		callStatusInformation = CALL_STATUS_MAPPING[curCallInfo.callStatus];
		svcServer->NotifyCallStatusQueryEvent(curCallInfo.callId, curCallInfo.callType, callStatusInformation.c_str());
	} else {
		XCALLLOGE("ERROR check prev & current callStatus .... No Match [%d -> %d] \n",curCallInfo.callStatus,callInfo.callStatus);
		ret = false;
	}

	return ret;

}

/**
 * ================================================================================
 * @fn : ServiceActivationSetRequest
 * @brief : Request function for service activation API
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Forward the service activation request to Client component
 * @param[in] arg_service <2 = InformationCall> : accept or decline call
 * @param[in] arg_action <1=Off 2-On>           : service activation on or off
 * @param[in] callback                          : asynchronous call back function
 * @param[in] user_data                         : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
void XcallManager::ServiceActivationSetRequest (guint arg_service, guint arg_action,
									GAsyncReadyCallback callback, gpointer user_data)
{
	XCALLLOGI("arg_service=%d arg_action=%d", arg_service, arg_action);

	svcClient->ServiceActivationSetRequest(arg_service, arg_action,
											callback,
											user_data);

	//set flag to 1 .... for checking icall button press
	isICallBtnPressed = 1;
}

/**
 * ================================================================================
 * @fn : ServiceActivationSetResponseCb
 * @brief : Response function called on result of the ServiceActivation
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Forwards the service activation API results received to Server component
 * @param[in] err           : error information object
 * @param[in] user_data     : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
void XcallManager::ServiceActivationSetResponseCb (GError * err, gpointer user_data)
{

	XCALLLOGI("ServiceActivationSetResponse \n");
	svcServer->ServiceActivationSetResponseCb(err, user_data);

}

/**
 * ================================================================================
 * @fn : CallHandlingSetRequest
 * @brief : Request function for Call handling API
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Forward the service activation request to Client component
 * @param[in] arg_action <0 = acceptCall, 1 = hangupCall> : accept or decline call
 * @param[in] arg_callId <1-4>                            : ongoing call id
 * @param[in] callback                                    : asynchronous call back function
 * @param[in] user_data                                   : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
void XcallManager::CallHandlingSetRequest (guint arg_action, guint8 arg_callId,
									GAsyncReadyCallback callback, gpointer user_data)
{

	XCALLLOGI("arg_action=%d arg_callId=%d", arg_action, arg_callId);
	svcClient->CallHandlingSetRequest(arg_action, arg_callId,
											callback,
											user_data);

}

/**
 * ================================================================================
 * @fn : CallHandlingSetRequestResponseCb
 * @brief : Response function called on result of the Call Handling
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Forwards the service activation API results received to Server component
 * @param[in] err           : error information object
 * @param[in] user_data     : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
void XcallManager::CallHandlingSetRequestResponseCb (GError * err, gpointer user_data)
{

	XCALLLOGI("CallHandlingSetRequestResponse \n");
	svcServer->CallHandlingSetRequestResponseCb (err, user_data);

}

/**
 * ================================================================================
 * @fn : SOSStatusResponseCb
 * @brief : Response function called on result of the SOS status information
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Check the SOS status information
 * - Notifes the error information on specific SOS status
 * @param[in] err       : error information object
 * @param[in] SosStatus : SOS status information object
 * @param[in] user_data : call back user data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ================================================================================
 */
void XcallManager::SOSStatusResponseCb (GError * err, guint SosStatus, gpointer user_data)
{

	XCALLLOGI("SOSStatusResponseCb %d \n", SosStatus);
	SOS_STATUS_T upatedStatus = static_cast<SOS_STATUS_T>(SosStatus);
	if (mSosStatus != upatedStatus) {
		mSosStatus = upatedStatus;
		switch (mSosStatus) {
			case SOS_STATUS_LIMITED:
			case SOS_STATUS_NOT_AVAILABLE:
				XCALLLOGI("SOS service NOT AVAILABLE\n");
				svcServer->NotifyErrorInformation("GDBus.Error:org.freedesktop.DBus.Error.Failed: No response");
				break;
			case SOS_STATUS_AVAILABLE:
				XCALLLOGI("SOS service AVAILABLE\n");
				break;
			case SOS_STATUS_UNKNOWN:
			default:
				XCALLLOGI("SOS service Invalid\n");
				break;
		}
	}

}

/**
 * ================================================================================
 * @fn : notifySOSStatusEvent
 * @brief : Handler function called on SOS status information event received
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Check the SOS status information
 * - Notifes the error information on specific SOS status
 * @param[in] SosStatus : SOS status information object
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::notifySOSStatusEvent(guint SosStatus)
{
	XCALLLOGI("SOSStatusResponseCb %d \n", SosStatus);
	SOS_STATUS_T upatedStatus = static_cast<SOS_STATUS_T>(SosStatus);
	if (mSosStatus != upatedStatus) {
		mSosStatus = upatedStatus;
		switch (mSosStatus) {
		case SOS_STATUS_LIMITED:
		case SOS_STATUS_NOT_AVAILABLE:
			XCALLLOGI("SOS service NOT AVAILABLE\n");
			svcServer->NotifyErrorInformation("GDBus.Error:org.freedesktop.DBus.Error.Failed: No response");
			break;
		case SOS_STATUS_AVAILABLE:
			XCALLLOGI("SOS service AVAILABLE\n");
			break;
		case SOS_STATUS_UNKNOWN:
		default:
			XCALLLOGI("SOS service Invalid\n");
			break;
		}
	}
	return true;
}


bool XcallManager::UpdatePremiumAudioDeviceStatus(CALL_DIRECTION_T direction)
{
	bool ret = true;
	XCALLLOGI("UpdatePremiumAudioDeviceStatus() is called \n");


	if(direction == DBUS_CALL_DIRECTION_TO_MMUS) {
		svcClient->getDeviceStatusFromMMUS();
	}else if(direction == DBUS_CALL_DIRECTION_TO_TEMIL) {

		guint spkStatus=0;
		guint micStatus=0;

		GetPremiumAudioSPKStatus(&spkStatus);
		GetPremiumAudioMICStatus(&micStatus);

		svcServer->NotifyPremiumAudioEvent(spkStatus,micStatus);
	}

	return ret;
}

/**
 * ================================================================================
 * @fn : SetPremiumAudioSPKStatus
 * @brief : Utility function for updating the premium audio speaker status
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Updates the member variable related to speaker status
 * @param[in] spkStatus : Premium audio speaker status
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::SetPremiumAudioSPKStatus(bool spkStatus)
{
	bool ret = true;

	//TODO : check how we will get hw status information from micom manager
	//            now jsut use bool temporarilly

	if(spkStatus) {
		curCallInfo.audioStatus.spkStatus = PREMIUM_AUDIO_STATUS_OK;
	}else {
		curCallInfo.audioStatus.spkStatus = PREMIUM_AUDIO_STATUS_NOT_OK;
	}
	XCALLLOGI("Set(SPK)PremiumAudio[spk(%d), mic(%d)]", curCallInfo.audioStatus.spkStatus ,curCallInfo.audioStatus.micStatus);
	return ret;
}

/**
 * ================================================================================
 * @fn : SetPremiumAudioMICStatus
 * @brief : Utility function for updating the premium audio mic status
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Updates the member variable related to mic status
 * @param[in] micStatus : Premium audio mic status
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::SetPremiumAudioMICStatus(bool micStatus)
{
	bool ret = true;

	if(micStatus) {
		curCallInfo.audioStatus.micStatus = PREMIUM_AUDIO_STATUS_OK;
	}else {
		curCallInfo.audioStatus.micStatus = PREMIUM_AUDIO_STATUS_NOT_OK;
	}

	XCALLLOGI("Set(MIC)PremiumAudio[spk(%d), mic(%d)]", curCallInfo.audioStatus.spkStatus ,curCallInfo.audioStatus.micStatus);
	return ret;
}

/**
 * ================================================================================
 * @fn : GetPremiumAudioSPKStatus
 * @brief : Utility function for getting the premium audio speaker status
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Get speaker status from member variables
 * @param[in] spkStatus : Premium audio speaker status
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::GetPremiumAudioSPKStatus(guint *spkStatus)
{
	bool ret = true;

	if(curCallInfo.audioStatus.spkStatus == PREMIUM_AUDIO_STATUS_OK) {
		*spkStatus = PREMIUM_AUDIO_STATUS_OK;
	} else {
		*spkStatus = PREMIUM_AUDIO_STATUS_NOT_OK;
	}

	XCALLLOGI("Get(SPK)PremiumAudio[spk(%d)]",*spkStatus);
	return ret;
}

/**
 * ================================================================================
 * @fn : GetPremiumAudioMICStatus
 * @brief : Utility function for getting the premium audio mic status
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Get mic status from member variables
 * @param[in] micStatus : Premium audio mic status
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::GetPremiumAudioMICStatus(guint *micStatus)
{
	bool ret = true;

	if(curCallInfo.audioStatus.micStatus == PREMIUM_AUDIO_STATUS_OK) {
		*micStatus = PREMIUM_AUDIO_STATUS_OK;
	} else {
		*micStatus = PREMIUM_AUDIO_STATUS_NOT_OK;
	}

	XCALLLOGI("Get(MIC)PremiumAudio[mic(%d)]",*micStatus);
	return ret;
}

/**
 * ================================================================================
 * @fn : unitTest
 * @brief : unit test case function
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - unit test function as per the test name with parameters
 * @param[in] testName : unit test case name
 * @param[in] param1   : data to be used for unit test case
 * @param[in] param2   : data to be used for unit test case
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
bool XcallManager::unitTest(char *testName, char *param1, char *param2)
{
	bool ret =true;

	if(!strcmp(testName,"PremiumAudio")) {
		guint spkStatus=atoi(param1);
		guint micStatus=atoi(param2);
		guint prevSpkstatus =0;
		guint prevMicstatus =0;

		GetPremiumAudioMICStatus(&prevMicstatus);
		GetPremiumAudioSPKStatus(&prevSpkstatus);

		XCALLLOGI("unitTest(PremiumAudio)| spk[%d] mic[%d] ",spkStatus,micStatus);

		if((spkStatus==0 || spkStatus==1) && (micStatus==0 || micStatus==1)) {

			XCALLLOGI("unitTest | change status value spk[%d -> %d] mic[%d -> %d]",prevSpkstatus,spkStatus,prevMicstatus,micStatus);
			SetPremiumAudioSPKStatus(spkStatus);
			SetPremiumAudioMICStatus(micStatus);

			//현재 상태가 calling와 connected 인경우만 event 발생
			if((curCallInfo.callStatus == CALL_STATUS_CALLING) ||
				(curCallInfo.callStatus == CALL_STATUS_INCOMING) ||
				(curCallInfo.callStatus == CALL_STATUS_CONNECTED)){

				XCALLLOGI("unitTest | call NotifyPremiumAudioEvent");
				svcServer->NotifyPremiumAudioEvent(spkStatus,micStatus);
			}

		}else if((spkStatus==2) && (micStatus==2)) {
			XCALLLOGI("unitTest | call getDeviceStatusFromMMUS[Ask System Last Status] to MMUS");
			svcClient->getDeviceStatusFromMMUS();
		}

	}else {
		XCALLLOGI("unitTest | wrong testName = %s",testName);
		ret = false;
	}

	return ret;
}

/**
 * ================================================================================
 * @fn : GetCarConfigInfoRequest
 * @brief : Request function for car config information with particular index value
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Forward the service activation request to Client component
 * @param[in] dataIndex   : index value to be read from car config info data
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
bool XcallManager::GetCarConfigInfoRequest(guint dataIndex)
{
	XCALLLOGI("GetCarConfigInfoRequest(%d)\n",dataIndex);
	svcClient->GetCarConfigInfoRequest(dataIndex, nullptr, nullptr);
	return true;
}

/**
 * ================================================================================
 * @fn : setSourceInformation
 * @brief : Fucntion to provide the IP, port, encoding scheme details to Gstreamer pipeline
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - forwards the data to player instance
 * @param[in] xcall_debug_input   : Structure contains IP, Port, encoding scheme details
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : None
 * ===================================================================================
 */
#ifdef DEBUG_ENABLED
void XcallManager::setSourceInformation(xcall_debug_input input) {
	XCALLLOGD("start");
	this->input = input;
}
#endif

/**
 * ================================================================================
 * @fn : callStatusChanged
 * @brief : Utility function for checking the call status changed or not
 * @section function_flow Function flow (Pseudo-code or Decision Table)
 * - Compare the previous call status and current call status
 * - return the true if call status changed else false
 * @param[in] prevStatus : previous call status
 * @param[in] newStatus  : new call status
 * @section global_variable Global Variables : None
 * @section dependencies Dependencies
 * - None
 * @return : boolean value returns function result to caller
 * ================================================================================
 */
bool XcallManager::callStatusChanged(CallStatus_t *prevStatus, CallStatus_t* newStatus) {
	XCALLLOGI("prevStatus: [%d %d %d %d]\n",prevStatus->status, prevStatus->voiceStatus, prevStatus->buttonStatus, prevStatus->sbStatus);
	XCALLLOGI("newStatus: [%d %d %d %d]\n",newStatus->status, newStatus->voiceStatus, newStatus->buttonStatus, newStatus->sbStatus);
	if (	(prevStatus->status != newStatus->status) || (prevStatus->voiceStatus != newStatus->voiceStatus)
			|| (prevStatus->buttonStatus != newStatus->buttonStatus) || (prevStatus->sbStatus != newStatus->sbStatus)) {
		return true;
	} else {

		//check whether same call is valid or not
		if((newStatus->callId == XCALL_ID_ICALL) && (newStatus->status == StatusServiceNotAvailable) && (isICallBtnPressed==1)) {
			XCALLLOGI("I-Call ServiceNotavailable ---> need to display popup \n");
			return true;
		} else {
			return false;
		}

	}

}

#ifdef TIME_MEASURE
void XcallManager::setStartTime(clock_t time)
{
	baseTime = time;
	XCALLLOGI("[TIME]setStartTime(tick) = [%f][%f] \n",(double)time, (double)baseTime);
}

void XcallManager::measureElapseTime(void)
{
	clock_t toc = clock();
	double elapsedTime = (double)(toc - baseTime);

	XCALLLOGI("[TIME]elapseTime(tick|s) = [%f][%f] \n",elapsedTime, (elapsedTime/CLOCKS_PER_SEC));

}
#endif


} //temxcall

