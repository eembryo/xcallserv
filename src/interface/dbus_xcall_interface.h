/*
 * Generated by gdbus-codegen 2.32.4. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __DBUS_XCALL_INTERFACE_H__
#define __DBUS_XCALL_INTERFACE_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for com.lge.xcallservice.testInterface */

#define TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE (com_lge_xcallservice_test_interface_get_type ())
#define COM_LGE_XCALLSERVICE_TEST_INTERFACE(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE, ComLgeXcallserviceTestInterface))
#define IS_COM_LGE_XCALLSERVICE_TEST_INTERFACE(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE))
#define COM_LGE_XCALLSERVICE_TEST_INTERFACE_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE, ComLgeXcallserviceTestInterfaceIface))

struct _ComLgeXcallserviceTestInterface;
typedef struct _ComLgeXcallserviceTestInterface ComLgeXcallserviceTestInterface;
typedef struct _ComLgeXcallserviceTestInterfaceIface ComLgeXcallserviceTestInterfaceIface;

struct _ComLgeXcallserviceTestInterfaceIface
{
  GTypeInterface parent_iface;

  gboolean (*handle_calling) (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_callInfo,
    const gchar *arg_callName);

  gboolean (*handle_connected) (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_end) (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_send_err_info_notification) (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    guint arg_errId,
    const gchar *arg_errMsg);

  gboolean (*handle_set_rescue_status) (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    guint arg_eRescueStatus,
    guint arg_eXCallID,
    guint arg_eVoiceStatus,
    guint arg_eSourceStatus,
    guint arg_eMessageStatus,
    guint arg_eButtonStatus,
    guint arg_ePSAPStatus,
    guint arg_eStandbyStatus,
    guint arg_bRescueStatus,
    guint arg_bXCallID,
    guint arg_bVoiceStatus,
    guint arg_bSourceStatus,
    guint arg_bMessageStatus,
    guint arg_bButtonStatus,
    guint arg_bPSAPStatus,
    guint arg_bStandbyStatus,
    guint arg_iRescueStatus,
    guint arg_iXCallID,
    guint arg_iVoiceStatus,
    guint arg_iSourceStatus,
    guint arg_iMessageStatus,
    guint arg_iButtonStatus,
    guint arg_iPSAPStatus,
    guint arg_iStandbyStatus,
    guint arg_sRescueStatus,
    guint arg_sXCallID,
    guint arg_sVoiceStatus,
    guint arg_sSourceStatus,
    guint arg_sMessageStatus,
    guint arg_sButtonStatus,
    guint arg_sPSAPStatus,
    guint arg_sStandbyStatus,
    guint arg_backupAudioStatus);

  gboolean (*handle_unittest) (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_testName,
    const gchar *arg_param1,
    const gchar *arg_param2);

};

GType com_lge_xcallservice_test_interface_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *com_lge_xcallservice_test_interface_interface_info (void);
guint com_lge_xcallservice_test_interface_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void com_lge_xcallservice_test_interface_complete_calling (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    gboolean result);

void com_lge_xcallservice_test_interface_complete_connected (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    gboolean result);

void com_lge_xcallservice_test_interface_complete_end (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    gboolean result);

void com_lge_xcallservice_test_interface_complete_unittest (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    gboolean result);

void com_lge_xcallservice_test_interface_complete_send_err_info_notification (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    gboolean result);

void com_lge_xcallservice_test_interface_complete_set_rescue_status (
    ComLgeXcallserviceTestInterface *object,
    GDBusMethodInvocation *invocation,
    gboolean result);



/* D-Bus method calls: */
void com_lge_xcallservice_test_interface_call_calling (
    ComLgeXcallserviceTestInterface *proxy,
    const gchar *arg_callInfo,
    const gchar *arg_callName,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_test_interface_call_calling_finish (
    ComLgeXcallserviceTestInterface *proxy,
    gboolean *out_result,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_test_interface_call_calling_sync (
    ComLgeXcallserviceTestInterface *proxy,
    const gchar *arg_callInfo,
    const gchar *arg_callName,
    gboolean *out_result,
    GCancellable *cancellable,
    GError **error);

void com_lge_xcallservice_test_interface_call_connected (
    ComLgeXcallserviceTestInterface *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_test_interface_call_connected_finish (
    ComLgeXcallserviceTestInterface *proxy,
    gboolean *out_result,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_test_interface_call_connected_sync (
    ComLgeXcallserviceTestInterface *proxy,
    gboolean *out_result,
    GCancellable *cancellable,
    GError **error);

void com_lge_xcallservice_test_interface_call_end (
    ComLgeXcallserviceTestInterface *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_test_interface_call_end_finish (
    ComLgeXcallserviceTestInterface *proxy,
    gboolean *out_result,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_test_interface_call_end_sync (
    ComLgeXcallserviceTestInterface *proxy,
    gboolean *out_result,
    GCancellable *cancellable,
    GError **error);

void com_lge_xcallservice_test_interface_call_unittest (
    ComLgeXcallserviceTestInterface *proxy,
    const gchar *arg_testName,
    const gchar *arg_param1,
    const gchar *arg_param2,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_test_interface_call_unittest_finish (
    ComLgeXcallserviceTestInterface *proxy,
    gboolean *out_result,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_test_interface_call_unittest_sync (
    ComLgeXcallserviceTestInterface *proxy,
    const gchar *arg_testName,
    const gchar *arg_param1,
    const gchar *arg_param2,
    gboolean *out_result,
    GCancellable *cancellable,
    GError **error);

void com_lge_xcallservice_test_interface_call_send_err_info_notification (
    ComLgeXcallserviceTestInterface *proxy,
    guint arg_errId,
    const gchar *arg_errMsg,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_test_interface_call_send_err_info_notification_finish (
    ComLgeXcallserviceTestInterface *proxy,
    gboolean *out_result,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_test_interface_call_send_err_info_notification_sync (
    ComLgeXcallserviceTestInterface *proxy,
    guint arg_errId,
    const gchar *arg_errMsg,
    gboolean *out_result,
    GCancellable *cancellable,
    GError **error);

void com_lge_xcallservice_test_interface_call_set_rescue_status (
    ComLgeXcallserviceTestInterface *proxy,
    guint arg_eRescueStatus,
    guint arg_eXCallID,
    guint arg_eVoiceStatus,
    guint arg_eSourceStatus,
    guint arg_eMessageStatus,
    guint arg_eButtonStatus,
    guint arg_ePSAPStatus,
    guint arg_eStandbyStatus,
    guint arg_bRescueStatus,
    guint arg_bXCallID,
    guint arg_bVoiceStatus,
    guint arg_bSourceStatus,
    guint arg_bMessageStatus,
    guint arg_bButtonStatus,
    guint arg_bPSAPStatus,
    guint arg_bStandbyStatus,
    guint arg_iRescueStatus,
    guint arg_iXCallID,
    guint arg_iVoiceStatus,
    guint arg_iSourceStatus,
    guint arg_iMessageStatus,
    guint arg_iButtonStatus,
    guint arg_iPSAPStatus,
    guint arg_iStandbyStatus,
    guint arg_sRescueStatus,
    guint arg_sXCallID,
    guint arg_sVoiceStatus,
    guint arg_sSourceStatus,
    guint arg_sMessageStatus,
    guint arg_sButtonStatus,
    guint arg_sPSAPStatus,
    guint arg_sStandbyStatus,
    guint arg_backupAudioStatus,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_test_interface_call_set_rescue_status_finish (
    ComLgeXcallserviceTestInterface *proxy,
    gboolean *out_result,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_test_interface_call_set_rescue_status_sync (
    ComLgeXcallserviceTestInterface *proxy,
    guint arg_eRescueStatus,
    guint arg_eXCallID,
    guint arg_eVoiceStatus,
    guint arg_eSourceStatus,
    guint arg_eMessageStatus,
    guint arg_eButtonStatus,
    guint arg_ePSAPStatus,
    guint arg_eStandbyStatus,
    guint arg_bRescueStatus,
    guint arg_bXCallID,
    guint arg_bVoiceStatus,
    guint arg_bSourceStatus,
    guint arg_bMessageStatus,
    guint arg_bButtonStatus,
    guint arg_bPSAPStatus,
    guint arg_bStandbyStatus,
    guint arg_iRescueStatus,
    guint arg_iXCallID,
    guint arg_iVoiceStatus,
    guint arg_iSourceStatus,
    guint arg_iMessageStatus,
    guint arg_iButtonStatus,
    guint arg_iPSAPStatus,
    guint arg_iStandbyStatus,
    guint arg_sRescueStatus,
    guint arg_sXCallID,
    guint arg_sVoiceStatus,
    guint arg_sSourceStatus,
    guint arg_sMessageStatus,
    guint arg_sButtonStatus,
    guint arg_sPSAPStatus,
    guint arg_sStandbyStatus,
    guint arg_backupAudioStatus,
    gboolean *out_result,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY (com_lge_xcallservice_test_interface_proxy_get_type ())
#define COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY, ComLgeXcallserviceTestInterfaceProxy))
#define COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY, ComLgeXcallserviceTestInterfaceProxyClass))
#define COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY, ComLgeXcallserviceTestInterfaceProxyClass))
#define IS_COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY))
#define IS_COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_PROXY))

typedef struct _ComLgeXcallserviceTestInterfaceProxy ComLgeXcallserviceTestInterfaceProxy;
typedef struct _ComLgeXcallserviceTestInterfaceProxyClass ComLgeXcallserviceTestInterfaceProxyClass;
typedef struct _ComLgeXcallserviceTestInterfaceProxyPrivate ComLgeXcallserviceTestInterfaceProxyPrivate;

struct _ComLgeXcallserviceTestInterfaceProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  ComLgeXcallserviceTestInterfaceProxyPrivate *priv;
};

struct _ComLgeXcallserviceTestInterfaceProxyClass
{
  GDBusProxyClass parent_class;
};

GType com_lge_xcallservice_test_interface_proxy_get_type (void) G_GNUC_CONST;

void com_lge_xcallservice_test_interface_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeXcallserviceTestInterface *com_lge_xcallservice_test_interface_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeXcallserviceTestInterface *com_lge_xcallservice_test_interface_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void com_lge_xcallservice_test_interface_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeXcallserviceTestInterface *com_lge_xcallservice_test_interface_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeXcallserviceTestInterface *com_lge_xcallservice_test_interface_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON (com_lge_xcallservice_test_interface_skeleton_get_type ())
#define COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON, ComLgeXcallserviceTestInterfaceSkeleton))
#define COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON, ComLgeXcallserviceTestInterfaceSkeletonClass))
#define COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON, ComLgeXcallserviceTestInterfaceSkeletonClass))
#define IS_COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON))
#define IS_COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_XCALLSERVICE_TEST_INTERFACE_SKELETON))

typedef struct _ComLgeXcallserviceTestInterfaceSkeleton ComLgeXcallserviceTestInterfaceSkeleton;
typedef struct _ComLgeXcallserviceTestInterfaceSkeletonClass ComLgeXcallserviceTestInterfaceSkeletonClass;
typedef struct _ComLgeXcallserviceTestInterfaceSkeletonPrivate ComLgeXcallserviceTestInterfaceSkeletonPrivate;

struct _ComLgeXcallserviceTestInterfaceSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  ComLgeXcallserviceTestInterfaceSkeletonPrivate *priv;
};

struct _ComLgeXcallserviceTestInterfaceSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType com_lge_xcallservice_test_interface_skeleton_get_type (void) G_GNUC_CONST;

ComLgeXcallserviceTestInterface *com_lge_xcallservice_test_interface_skeleton_new (void);


/* ------------------------------------------------------------------------ */
/* Declarations for com.lge.xcallservice.CallFeature */

#define TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE (com_lge_xcallservice_call_feature_get_type ())
#define COM_LGE_XCALLSERVICE_CALL_FEATURE(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE, ComLgeXcallserviceCallFeature))
#define IS_COM_LGE_XCALLSERVICE_CALL_FEATURE(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE))
#define COM_LGE_XCALLSERVICE_CALL_FEATURE_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE, ComLgeXcallserviceCallFeatureIface))

struct _ComLgeXcallserviceCallFeature;
typedef struct _ComLgeXcallserviceCallFeature ComLgeXcallserviceCallFeature;
typedef struct _ComLgeXcallserviceCallFeatureIface ComLgeXcallserviceCallFeatureIface;

struct _ComLgeXcallserviceCallFeatureIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_call_handling_set_request) (
    ComLgeXcallserviceCallFeature *object,
    GDBusMethodInvocation *invocation,
    guint arg_action,
    guint arg_callId);

  gboolean (*handle_service_activation_set_request) (
    ComLgeXcallserviceCallFeature *object,
    GDBusMethodInvocation *invocation,
    guint arg_service,
    guint arg_action);

  void (*call_status_query) (
    ComLgeXcallserviceCallFeature *object,
    guint arg_callId,
    guint arg_callType,
    const gchar *arg_pState);

  void (*notify_err_info) (
    ComLgeXcallserviceCallFeature *object,
    guint arg_errId,
    const gchar *arg_errMsg);

};

GType com_lge_xcallservice_call_feature_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *com_lge_xcallservice_call_feature_interface_info (void);
guint com_lge_xcallservice_call_feature_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void com_lge_xcallservice_call_feature_complete_call_handling_set_request (
    ComLgeXcallserviceCallFeature *object,
    GDBusMethodInvocation *invocation);

void com_lge_xcallservice_call_feature_complete_service_activation_set_request (
    ComLgeXcallserviceCallFeature *object,
    GDBusMethodInvocation *invocation);



/* D-Bus signal emissions functions: */
void com_lge_xcallservice_call_feature_emit_call_status_query (
    ComLgeXcallserviceCallFeature *object,
    guint arg_callId,
    guint arg_callType,
    const gchar *arg_pState);

void com_lge_xcallservice_call_feature_emit_notify_err_info (
    ComLgeXcallserviceCallFeature *object,
    guint arg_errId,
    const gchar *arg_errMsg);



/* D-Bus method calls: */
void com_lge_xcallservice_call_feature_call_call_handling_set_request (
    ComLgeXcallserviceCallFeature *proxy,
    guint arg_action,
    guint arg_callId,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_call_feature_call_call_handling_set_request_finish (
    ComLgeXcallserviceCallFeature *proxy,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_call_feature_call_call_handling_set_request_sync (
    ComLgeXcallserviceCallFeature *proxy,
    guint arg_action,
    guint arg_callId,
    GCancellable *cancellable,
    GError **error);

void com_lge_xcallservice_call_feature_call_service_activation_set_request (
    ComLgeXcallserviceCallFeature *proxy,
    guint arg_service,
    guint arg_action,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_call_feature_call_service_activation_set_request_finish (
    ComLgeXcallserviceCallFeature *proxy,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_call_feature_call_service_activation_set_request_sync (
    ComLgeXcallserviceCallFeature *proxy,
    guint arg_service,
    guint arg_action,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY (com_lge_xcallservice_call_feature_proxy_get_type ())
#define COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY, ComLgeXcallserviceCallFeatureProxy))
#define COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY, ComLgeXcallserviceCallFeatureProxyClass))
#define COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY, ComLgeXcallserviceCallFeatureProxyClass))
#define IS_COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY))
#define IS_COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_PROXY))

typedef struct _ComLgeXcallserviceCallFeatureProxy ComLgeXcallserviceCallFeatureProxy;
typedef struct _ComLgeXcallserviceCallFeatureProxyClass ComLgeXcallserviceCallFeatureProxyClass;
typedef struct _ComLgeXcallserviceCallFeatureProxyPrivate ComLgeXcallserviceCallFeatureProxyPrivate;

struct _ComLgeXcallserviceCallFeatureProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  ComLgeXcallserviceCallFeatureProxyPrivate *priv;
};

struct _ComLgeXcallserviceCallFeatureProxyClass
{
  GDBusProxyClass parent_class;
};

GType com_lge_xcallservice_call_feature_proxy_get_type (void) G_GNUC_CONST;

void com_lge_xcallservice_call_feature_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeXcallserviceCallFeature *com_lge_xcallservice_call_feature_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeXcallserviceCallFeature *com_lge_xcallservice_call_feature_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void com_lge_xcallservice_call_feature_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeXcallserviceCallFeature *com_lge_xcallservice_call_feature_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeXcallserviceCallFeature *com_lge_xcallservice_call_feature_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON (com_lge_xcallservice_call_feature_skeleton_get_type ())
#define COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON, ComLgeXcallserviceCallFeatureSkeleton))
#define COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON, ComLgeXcallserviceCallFeatureSkeletonClass))
#define COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON, ComLgeXcallserviceCallFeatureSkeletonClass))
#define IS_COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON))
#define IS_COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_XCALLSERVICE_CALL_FEATURE_SKELETON))

typedef struct _ComLgeXcallserviceCallFeatureSkeleton ComLgeXcallserviceCallFeatureSkeleton;
typedef struct _ComLgeXcallserviceCallFeatureSkeletonClass ComLgeXcallserviceCallFeatureSkeletonClass;
typedef struct _ComLgeXcallserviceCallFeatureSkeletonPrivate ComLgeXcallserviceCallFeatureSkeletonPrivate;

struct _ComLgeXcallserviceCallFeatureSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  ComLgeXcallserviceCallFeatureSkeletonPrivate *priv;
};

struct _ComLgeXcallserviceCallFeatureSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType com_lge_xcallservice_call_feature_skeleton_get_type (void) G_GNUC_CONST;

ComLgeXcallserviceCallFeature *com_lge_xcallservice_call_feature_skeleton_new (void);


/* ------------------------------------------------------------------------ */
/* Declarations for com.lge.xcallservice.PremiumAudio */

#define TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO (com_lge_xcallservice_premium_audio_get_type ())
#define COM_LGE_XCALLSERVICE_PREMIUM_AUDIO(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO, ComLgeXcallservicePremiumAudio))
#define IS_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO))
#define COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO, ComLgeXcallservicePremiumAudioIface))

struct _ComLgeXcallservicePremiumAudio;
typedef struct _ComLgeXcallservicePremiumAudio ComLgeXcallservicePremiumAudio;
typedef struct _ComLgeXcallservicePremiumAudioIface ComLgeXcallservicePremiumAudioIface;

struct _ComLgeXcallservicePremiumAudioIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_request) (
    ComLgeXcallservicePremiumAudio *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_set_request) (
    ComLgeXcallservicePremiumAudio *object,
    GDBusMethodInvocation *invocation,
    gboolean arg_isRequested);

  void (*notification) (
    ComLgeXcallservicePremiumAudio *object,
    GVariant *arg_premiumAudioStatus);

};

GType com_lge_xcallservice_premium_audio_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *com_lge_xcallservice_premium_audio_interface_info (void);
guint com_lge_xcallservice_premium_audio_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void com_lge_xcallservice_premium_audio_complete_set_request (
    ComLgeXcallservicePremiumAudio *object,
    GDBusMethodInvocation *invocation,
    GVariant *premiumAudioStatus);

void com_lge_xcallservice_premium_audio_complete_request (
    ComLgeXcallservicePremiumAudio *object,
    GDBusMethodInvocation *invocation,
    GVariant *premiumAudioStatus);



/* D-Bus signal emissions functions: */
void com_lge_xcallservice_premium_audio_emit_notification (
    ComLgeXcallservicePremiumAudio *object,
    GVariant *arg_premiumAudioStatus);



/* D-Bus method calls: */
void com_lge_xcallservice_premium_audio_call_set_request (
    ComLgeXcallservicePremiumAudio *proxy,
    gboolean arg_isRequested,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_premium_audio_call_set_request_finish (
    ComLgeXcallservicePremiumAudio *proxy,
    GVariant **out_premiumAudioStatus,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_premium_audio_call_set_request_sync (
    ComLgeXcallservicePremiumAudio *proxy,
    gboolean arg_isRequested,
    GVariant **out_premiumAudioStatus,
    GCancellable *cancellable,
    GError **error);

void com_lge_xcallservice_premium_audio_call_request (
    ComLgeXcallservicePremiumAudio *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_xcallservice_premium_audio_call_request_finish (
    ComLgeXcallservicePremiumAudio *proxy,
    GVariant **out_premiumAudioStatus,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_xcallservice_premium_audio_call_request_sync (
    ComLgeXcallservicePremiumAudio *proxy,
    GVariant **out_premiumAudioStatus,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY (com_lge_xcallservice_premium_audio_proxy_get_type ())
#define COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY, ComLgeXcallservicePremiumAudioProxy))
#define COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY, ComLgeXcallservicePremiumAudioProxyClass))
#define COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY, ComLgeXcallservicePremiumAudioProxyClass))
#define IS_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY))
#define IS_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_PROXY))

typedef struct _ComLgeXcallservicePremiumAudioProxy ComLgeXcallservicePremiumAudioProxy;
typedef struct _ComLgeXcallservicePremiumAudioProxyClass ComLgeXcallservicePremiumAudioProxyClass;
typedef struct _ComLgeXcallservicePremiumAudioProxyPrivate ComLgeXcallservicePremiumAudioProxyPrivate;

struct _ComLgeXcallservicePremiumAudioProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  ComLgeXcallservicePremiumAudioProxyPrivate *priv;
};

struct _ComLgeXcallservicePremiumAudioProxyClass
{
  GDBusProxyClass parent_class;
};

GType com_lge_xcallservice_premium_audio_proxy_get_type (void) G_GNUC_CONST;

void com_lge_xcallservice_premium_audio_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeXcallservicePremiumAudio *com_lge_xcallservice_premium_audio_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeXcallservicePremiumAudio *com_lge_xcallservice_premium_audio_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void com_lge_xcallservice_premium_audio_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeXcallservicePremiumAudio *com_lge_xcallservice_premium_audio_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeXcallservicePremiumAudio *com_lge_xcallservice_premium_audio_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON (com_lge_xcallservice_premium_audio_skeleton_get_type ())
#define COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON, ComLgeXcallservicePremiumAudioSkeleton))
#define COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON, ComLgeXcallservicePremiumAudioSkeletonClass))
#define COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON, ComLgeXcallservicePremiumAudioSkeletonClass))
#define IS_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON))
#define IS_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_XCALLSERVICE_PREMIUM_AUDIO_SKELETON))

typedef struct _ComLgeXcallservicePremiumAudioSkeleton ComLgeXcallservicePremiumAudioSkeleton;
typedef struct _ComLgeXcallservicePremiumAudioSkeletonClass ComLgeXcallservicePremiumAudioSkeletonClass;
typedef struct _ComLgeXcallservicePremiumAudioSkeletonPrivate ComLgeXcallservicePremiumAudioSkeletonPrivate;

struct _ComLgeXcallservicePremiumAudioSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  ComLgeXcallservicePremiumAudioSkeletonPrivate *priv;
};

struct _ComLgeXcallservicePremiumAudioSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType com_lge_xcallservice_premium_audio_skeleton_get_type (void) G_GNUC_CONST;

ComLgeXcallservicePremiumAudio *com_lge_xcallservice_premium_audio_skeleton_new (void);


G_END_DECLS

#endif /* __DBUS_XCALL_INTERFACE_H__ */