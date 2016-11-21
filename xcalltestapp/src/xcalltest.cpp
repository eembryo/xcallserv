/*
 * @@@ LICENSE
 * Copyright (C) 2016-2017, LG Electronics, All Right Reserved.
 * No part of this source code may be communicated, distributed, reproduced
 * or transmitted in any form or by any means, electronic or mechanical or
 * otherwise, for any purpose, without the prior written permission of
 * LG Electronics.
 * LICENSE @@@
 *
 # Design/Author : manisha.manisha@lge.com, dhilipkumar.raman@lge.com
 # Date : Oct. 24, 2016
 *
 * XCALL TEST APP Main Implementation
 *
 */

#include "xcalltest.h"
#include <unistd.h>

#define GETTEXT_PACKAGE "gio-ls"
#define N_(s) (s)
#define _(s) (s)

#ifdef CONNECT_DBUS_SYSTEM_BUS
	#define DBUS_TYPE G_BUS_TYPE_SYSTEM
#else
	#define DBUS_TYPE G_BUS_TYPE_SESSION
#endif

char *XCallTest::opt_call_dest = NULL;
gchar *XCallTest::opt_call_object_path = NULL;
gchar *XCallTest::opt_call_method = NULL;
gint XCallTest::opt_call_timeout = -1;

int XCallTest::initializingTimer = 2;
int XCallTest::standbyTimer = 10;
int XCallTest::connectingTimer = 5;
int XCallTest::incomingConnectingTimer = 5;
int XCallTest::disconnectingTimer = 20;

//CALL_TYPE_T XCallTest::callType = CALL_TYPE_NONE;

const GOptionEntry XCallTest::call_entries[] = {
	{"dest",		'd',	0,	G_OPTION_ARG_STRING,	&opt_call_dest,			N_("Destination name to invoke method on"),	NULL},
	{"object-path",	'o',	0,	G_OPTION_ARG_STRING,	&opt_call_object_path,	N_("Object path to invoke method on"),		NULL},
	{"method",		'm',	0,	G_OPTION_ARG_STRING,	&opt_call_method,		N_("Method and interface name"),			NULL},
	{"timeout",		't',	0,	G_OPTION_ARG_INT,		&opt_call_timeout,		N_("Timeout in seconds"),					NULL},
	{NULL}
};

XCallTest::XCallTest() {

}

XCallTest::~XCallTest() {

}

void XCallTest::TestEvent() {
	int sIndex;
	int iIndex;
	int mIndex;
	int callType;

	for(int i=TEST_CALL_TYPE_EMERGENCY_CALL; i<TEST_CALL_TYPE_MAX; i++) {
		cout<<"\t"<<i<<". "<<TEST_CALL_TYPE_MAPPING[i]<<endl;
	}
	cout<<"\t"<<TEST_CALL_TYPE_MAX<<". Return To Main Menu "<<endl;

	cout<< "Select Call Type: ";
	cin>>callType;

	if(callType >= TEST_CALL_TYPE_MAX || callType <= TEST_CALL_TYPE_NONE) {
		return;
	}

	int nEvents = sizeof(EventCaseInfo[callType-1].CallEvent)/sizeof(EventCaseInfo[callType-1].CallEvent[0]);

	int i=0;
	for(i=0; i<nEvents && strcmp(EventCaseInfo[callType-1].CallEvent[i].CallEventName, ""); i++) {
		cout<< "\t"<<i+1 <<". "<<EventCaseInfo[callType-1].CallEvent[i].CallEventName<<endl;
	}

	cout<<"\t"<<i+1<<". Return To Main Menu"<<endl;
	cout<< "Select Event to be Tested : ";
	cin>>iIndex;

	if(iIndex == i + 1) {
		return;
	}


	GVariant *parameters;

	parameters = g_variant_new("(uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu)",
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.ecallStatus.status,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.ecallStatus.callId,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.ecallStatus.voiceStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.ecallStatus.voiceSource,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.ecallStatus.messageStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.ecallStatus.buttonStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.ecallStatus.psapConfirmStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.ecallStatus.sbStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.bcallStatus.status,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.bcallStatus.callId,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.bcallStatus.voiceStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.bcallStatus.voiceSource,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.bcallStatus.messageStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.bcallStatus.buttonStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.bcallStatus.psapConfirmStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.bcallStatus.sbStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.icallStatus.status,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.icallStatus.callId,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.icallStatus.voiceStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.icallStatus.voiceSource,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.icallStatus.messageStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.icallStatus.buttonStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.icallStatus.psapConfirmStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.sbStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.status,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.callId,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.voiceStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.voiceSource,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.messageStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.buttonStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.psapConfirmStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.sdncallStatus.sbStatus,
	EventCaseInfo[callType-1].CallEvent[iIndex-1].RescueStatusData.backupAudioStatus);


	resultData *resultdata = NULL;
	resultdata = SendToDbus("com.lge.xcallservice",
							"/com/lge/xcallservice/testInterface",
							"com.lge.xcallservice.testInterface",
							"SetRescueStatus",
							&parameters);

	if(resultdata->error_t == 0) {
		if(resultdata->result)
			cout<<"Result of "<<"SetRescueStatus"<<":"<<resultdata->result<<endl;
		else
			cout<<"SetRescueStatus"<<":"<<" executed successfully: NO return params"<<endl;
	}
}



resultData *XCallTest::SendToDbus(gchar *opt_call_dest, gchar *opt_call_object_path,
							gchar *interface_name, gchar *method_name, GVariant **parameters) {

	GError *error = NULL;
	GDBusConnection *conn;
	GVariant *result = NULL;
	gchar *s;
	resultData *resultdata = new struct resultData;

	conn = g_bus_get_sync(DBUS_TYPE, NULL, &error);

	if(error) {
		g_printerr(_("Error: %s\n"), error->message);
		g_error_free(error);
		resultdata->error_t = 1;
		goto OUT;
	}
	/*else {
		 g_print("connection is succesfull\n");
	}*/

	if(*parameters != NULL)
		*parameters = g_variant_ref_sink(*parameters);

	result = g_dbus_connection_call_sync(conn,
										opt_call_dest,
										opt_call_object_path,
										interface_name,
										method_name,
										*parameters,
										NULL,
										G_DBUS_CALL_FLAGS_NONE,
										opt_call_timeout > 0 ? opt_call_timeout * 1000 : opt_call_timeout,
										NULL,
										&error);

	if(error) {
		g_printerr(_("Error: %s\n"), error->message);
		g_error_free(error);
		resultdata->error_t = 1;
		goto OUT;
	}

	if(result == NULL) {
		if(error) {
			g_printerr(_("Error: %s\n"), error->message);
			g_error_free(error);
			resultdata->error_t = 1;
			goto OUT;
		}
		goto OUT;
	}
	else {
		s = g_variant_print(result, TRUE);
		resultdata->result = s;
		resultdata->error_t = 0;
	}

	OUT:
	return resultdata;
}

void XCallTest::ChangeTimer()
{
	int time;
	int choice;
	cout<<"Choose the time value to be changed"<<endl;
	cout<<"\t1. Initializing time (in secs)"<<endl<<"\t2. Standby time (in secs)"<<endl;
	cout<<"\t2. Connecting time (in secs)"<<endl<<"\t3. Incoming connecting time (in secs)"<<endl;
	cout<<"\t5. Disconnecting time (in secs)"<<endl;

	cin>>choice;
	cout<<"endter time="<<endl;

	cin>>time;

	switch (choice){
		case 1:
			initializingTimer = time;
			cout<<"Initializing time (in secs)="<<initializingTimer<<endl;
			break;
		case 2:
			standbyTimer = time;
			cout<<"standby time (in secs)="<<standbyTimer<<endl;
			break;
		case 3:
			connectingTimer = time;
			cout<<"Connecting time (in secs)="<<connectingTimer<<endl;
			break;
		case 4:
			incomingConnectingTimer = time;
			cout<<"Incoming connecting time (in secs)="<<incomingConnectingTimer<<endl;
			break;
		case 5:
			disconnectingTimer = time;
			cout<<"Disconnecting time (in secs)="<<disconnectingTimer<<endl;
			break;
	}
}

void XCallTest::TestScenario()
{
	int sIndex;
	int iIndex;
	int mIndex;
	int callType;

	for(int i=TEST_CALL_TYPE_EMERGENCY_CALL; i<TEST_CALL_TYPE_MAX; i++) {
		cout<<"\t"<<i<<". "<<TEST_CALL_TYPE_MAPPING[i]<<endl;
	}
	cout<<"\t"<<TEST_CALL_TYPE_MAX<<". Return To Main Menu "<<endl;

	cout<< "Select Call Type: ";
	cin>>callType;

	if(callType >= TEST_CALL_TYPE_MAX || callType <= TEST_CALL_TYPE_NONE) {
		return;
	}

	int nScenarios = sizeof(ScenarioCaseInfo[callType-1].CallScenario)/sizeof(ScenarioCaseInfo[callType-1].CallScenario[0]);

	int i=0;
	for(i=0; i<nScenarios && strcmp(ScenarioCaseInfo[callType-1].CallScenario[i].CallScenarioName, ""); i++) {
		cout<< "\t"<<i+1 <<". "<<ScenarioCaseInfo[callType-1].CallScenario[i].CallScenarioName<<endl;
	}

	cout<<"\t"<<i+1<<". Return To Main Menu"<<endl;
	cout<< "Select Scenario to be Tested : ";
	cin>>iIndex;

	if(iIndex == i + 1) {
		return;
	}

	int nEvents = ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].eventCount;

	if (!strcmp(ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].CallScenarioName, "Connected->continuos")) {
		ConnectedCall(callType-1, iIndex-1, nEvents);
	} else if (!strcmp(ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].CallScenarioName, "Connnected->Disconnected")) {
		ConnectedAndDisconnectCall(callType-1, iIndex-1, nEvents);
	} else if (!strcmp(ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].CallScenarioName, "Intitializing->Disconnected")) {
		IntializeAndDisconnectCall(callType-1, iIndex-1, nEvents);
	} else if (!strcmp(ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].CallScenarioName, "StandBy->Disconnected")) {
		StandbyAndDisconnectCall(callType-1, iIndex-1, nEvents);
	} else if (!strcmp(ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].CallScenarioName, "Connecting->Disconnected")) {
		ConnectingAndDisconnectcall(callType-1, iIndex-1, nEvents);
	} else if (!strcmp(ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].CallScenarioName, "Incoming->continuos")) {
		IncomingCall(callType-1, iIndex-1, nEvents);
	} else if (!strcmp(ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].CallScenarioName, "Incoming->Disconnected")) {
		IncomingAndDisconnectCall(callType-1, iIndex-1, nEvents);
	} else if (!strcmp(ScenarioCaseInfo[callType-1].CallScenario[iIndex-1].CallScenarioName, "Incomingconnected->Disconnected")) {
		AnsweredAndDisconnectCall(callType-1, iIndex-1, nEvents);
	}


}


void XCallTest::ConnectedCall (int callType, int event, int eventCount) {
	cout<<"ConnectedCall"<<endl;
	int j=0;

	if(callType==2 || callType==3) {//SDN Call or I Call
		j+=2;
		eventCount+=2;
	}

	for (; j<eventCount; j++) {
		switch (j) {
			case 0:
				cout<<"Initializing"<<endl;
				break;
			case 1:
				sleep(initializingTimer);
				cout<<"Preparing or StandBy"<<endl;
				break;
			case 2:
				sleep(standbyTimer);
				cout<<"Connecting"<<endl;
				break;
			case 3:
				sleep(connectingTimer);
				cout<<"Connected"<<endl;
				break;
			default:
				cout<<"Not valid case"<<endl;
				break;
		}
		CreateCallScenarioAndSend(callType, event, j);
	}
}

void XCallTest::ConnectedAndDisconnectCall (int callType, int event, int eventCount) {
	cout<<"ConnectedAndDisconnectCall"<<endl;
	int j=0;

	if(callType==2 || callType==3) {//SDN Call or I Call
		j+=2;
		eventCount+=2;
	}

	for (; j<eventCount; j++) {
		switch (j) {
			case 0:
				cout<<"Initializing"<<endl;
				break;
			case 1:
				sleep(initializingTimer);
				cout<<"Preparing or StandBy"<<endl;
				break;
			case 2:
				sleep(standbyTimer);
				cout<<"Connecting"<<endl;
				break;
			case 3:
				sleep(connectingTimer);
				cout<<"Connected"<<endl;
				break;
			case 4:
				sleep(disconnectingTimer);
				cout<<"Disconnecting"<<endl;
				break;
			default:
				cout<<"Not valid case"<<endl;
				break;
		}
		CreateCallScenarioAndSend(callType, event, j);
	}
}

void XCallTest::IntializeAndDisconnectCall (int callType, int event, int eventCount) {
	cout<<"IntializeAndDisconnectCall"<<endl;
	int j=0;
	for (; j<eventCount; j++) {
		switch (j) {
			case 0:
				cout<<"Initializing"<<endl;
				break;
			case 1:
				sleep(initializingTimer);
				cout<<"Disconnecting"<<endl;
				break;
			default:
				cout<<"Not valid case"<<endl;
				break;
		}
		CreateCallScenarioAndSend(callType, event, j);
	}
}

void XCallTest::StandbyAndDisconnectCall (int callType, int event, int eventCount) {
	cout<<"StandbyAndDisconnectCall"<<endl;
	int j=0;
	for (; j<eventCount; j++) {
		switch (j) {
			case 0:
				cout<<"Initializing"<<endl;
				break;
			case 1:
				sleep(initializingTimer);
				cout<<"Preparing or StandBy"<<endl;
				break;
			case 2:
				sleep(standbyTimer);
				cout<<"Disconnecting"<<endl;
				break;
			default:
				cout<<"Not valid case"<<endl;
				break;
		}
		CreateCallScenarioAndSend(callType, event, j);
	}
}

void XCallTest::ConnectingAndDisconnectcall (int callType, int event, int eventCount) {
	cout<<"ConnectingAndDisconnectcall"<<endl;
	int j=0;

	if(callType==2 || callType==3) {//SDN Call or I Call
		j+=2;
		eventCount+=2;
	}

	for (; j<eventCount; j++) {
		switch (j) {
			case 0:
				cout<<"Initializing"<<endl;
				break;				
			case 1:
				sleep(initializingTimer);
				cout<<"Preparing or StandBy"<<endl;
				break;
			case 2:
				sleep(standbyTimer);
				cout<<"Connecting"<<endl;
				break;
			case 3:
				sleep(connectingTimer);
				cout<<"Disconnecting"<<endl;
				break;
			default:
				cout<<"Not valid case"<<endl;
				break;
		}
		CreateCallScenarioAndSend(callType, event, j);
	}

}

void XCallTest::IncomingCall (int callType, int event, int eventCount) {
	cout<<"IncomingCall"<<endl;
	int j=0;
	for (; j<eventCount; j++) {
		switch (j) {
			case 0:
				cout<<"Incoming"<<endl;
				break;
			case 1:
				sleep(incomingConnectingTimer);
				cout<<"Connected"<<endl;
				break;
			default:
				cout<<"Not valid case"<<endl;
				break;
		}
		CreateCallScenarioAndSend(callType, event, j);
	}
}

void XCallTest::IncomingAndDisconnectCall (int callType, int event, int eventCount) {
	cout<<"IncomingAndDisconnectCall"<<endl;
	int j=0;
	for (; j<eventCount; j++) {
		switch (j) {
			case 0:
				cout<<"Incoming"<<endl;
				break;
			case 1:
				sleep(incomingConnectingTimer);
				cout<<"Disconnecting"<<endl;
				break;
			default:
				cout<<"Not valid case"<<endl;
				break;
		}
		CreateCallScenarioAndSend(callType, event, j);
	}

}

void XCallTest::AnsweredAndDisconnectCall (int callType, int event, int eventCount) {
	cout<<"AnsweredAndDisconnectCall"<<endl;
	int j=0;
	for (; j<eventCount; j++) {
		switch (j) {
			case 0:
				cout<<"Incoming"<<endl;
				break;				
			case 1:
				sleep(incomingConnectingTimer);
				cout<<"Connected"<<endl;
				break;
			case 2:
				sleep(disconnectingTimer);
				cout<<"Disconnecting"<<endl;
				break;
			default:
				cout<<"Not valid case"<<endl;
				break;
		}
		CreateCallScenarioAndSend(callType, event, j);
	}


}

void XCallTest::CreateCallScenarioAndSend (int callType, int event, int dataIndex)
{
	GVariant *parameters;
	parameters = g_variant_new("(uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu)",
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].ecallStatus.status,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].ecallStatus.callId,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].ecallStatus.voiceStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].ecallStatus.voiceSource,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].ecallStatus.messageStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].ecallStatus.buttonStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].ecallStatus.psapConfirmStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].ecallStatus.sbStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].bcallStatus.status,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].bcallStatus.callId,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].bcallStatus.voiceStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].bcallStatus.voiceSource,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].bcallStatus.messageStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].bcallStatus.buttonStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].bcallStatus.psapConfirmStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].bcallStatus.sbStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].icallStatus.status,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].icallStatus.callId,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].icallStatus.voiceStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].icallStatus.voiceSource,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].icallStatus.messageStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].icallStatus.buttonStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].icallStatus.psapConfirmStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.sbStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.status,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.callId,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.voiceStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.voiceSource,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.messageStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.buttonStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.psapConfirmStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].sdncallStatus.sbStatus,
	ScenarioCaseInfo[callType].CallScenario[event].RescueStatusData[dataIndex].backupAudioStatus);


	resultData *resultdata = NULL;
	resultdata = SendToDbus("com.lge.xcallservice",
							"/com/lge/xcallservice/testInterface",
							"com.lge.xcallservice.testInterface",
							"SetRescueStatus",
							&parameters);

	if(resultdata->error_t == 0) {
		if(resultdata->result)
			cout<<"Result of "<<"SetRescueStatus"<<":"<<resultdata->result<<endl;
		else
			cout<<"SetRescueStatus"<<":"<<" executed successfully: NO return params"<<endl;
	}
}

