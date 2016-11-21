/*
 * Generated by gdbus-codegen 2.32.4. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __COMMONPHONE_H__
#define __COMMONPHONE_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for com.lge.temil.CommonPhone.CallHandling */

#define TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING (com_lge_temil_common_phone_call_handling_get_type ())
#define COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING, ComLgeTemilCommonPhoneCallHandling))
#define IS_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING))
#define COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING, ComLgeTemilCommonPhoneCallHandlingIface))

struct _ComLgeTemilCommonPhoneCallHandling;
typedef struct _ComLgeTemilCommonPhoneCallHandling ComLgeTemilCommonPhoneCallHandling;
typedef struct _ComLgeTemilCommonPhoneCallHandlingIface ComLgeTemilCommonPhoneCallHandlingIface;

struct _ComLgeTemilCommonPhoneCallHandlingIface
{
  GTypeInterface parent_iface;

  gboolean (*handle_set_request) (
    ComLgeTemilCommonPhoneCallHandling *object,
    GDBusMethodInvocation *invocation,
    guint arg_action,
    guint arg_callId);

};

GType com_lge_temil_common_phone_call_handling_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *com_lge_temil_common_phone_call_handling_interface_info (void);
guint com_lge_temil_common_phone_call_handling_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void com_lge_temil_common_phone_call_handling_complete_set_request (
    ComLgeTemilCommonPhoneCallHandling *object,
    GDBusMethodInvocation *invocation);



/* D-Bus method calls: */
void com_lge_temil_common_phone_call_handling_call_set_request (
    ComLgeTemilCommonPhoneCallHandling *proxy,
    guint arg_action,
    guint arg_callId,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_temil_common_phone_call_handling_call_set_request_finish (
    ComLgeTemilCommonPhoneCallHandling *proxy,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_temil_common_phone_call_handling_call_set_request_sync (
    ComLgeTemilCommonPhoneCallHandling *proxy,
    guint arg_action,
    guint arg_callId,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY (com_lge_temil_common_phone_call_handling_proxy_get_type ())
#define COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY, ComLgeTemilCommonPhoneCallHandlingProxy))
#define COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY, ComLgeTemilCommonPhoneCallHandlingProxyClass))
#define COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY, ComLgeTemilCommonPhoneCallHandlingProxyClass))
#define IS_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY))
#define IS_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_PROXY))

typedef struct _ComLgeTemilCommonPhoneCallHandlingProxy ComLgeTemilCommonPhoneCallHandlingProxy;
typedef struct _ComLgeTemilCommonPhoneCallHandlingProxyClass ComLgeTemilCommonPhoneCallHandlingProxyClass;
typedef struct _ComLgeTemilCommonPhoneCallHandlingProxyPrivate ComLgeTemilCommonPhoneCallHandlingProxyPrivate;

struct _ComLgeTemilCommonPhoneCallHandlingProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  ComLgeTemilCommonPhoneCallHandlingProxyPrivate *priv;
};

struct _ComLgeTemilCommonPhoneCallHandlingProxyClass
{
  GDBusProxyClass parent_class;
};

GType com_lge_temil_common_phone_call_handling_proxy_get_type (void) G_GNUC_CONST;

void com_lge_temil_common_phone_call_handling_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeTemilCommonPhoneCallHandling *com_lge_temil_common_phone_call_handling_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeTemilCommonPhoneCallHandling *com_lge_temil_common_phone_call_handling_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void com_lge_temil_common_phone_call_handling_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeTemilCommonPhoneCallHandling *com_lge_temil_common_phone_call_handling_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeTemilCommonPhoneCallHandling *com_lge_temil_common_phone_call_handling_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON (com_lge_temil_common_phone_call_handling_skeleton_get_type ())
#define COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON, ComLgeTemilCommonPhoneCallHandlingSkeleton))
#define COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON, ComLgeTemilCommonPhoneCallHandlingSkeletonClass))
#define COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON, ComLgeTemilCommonPhoneCallHandlingSkeletonClass))
#define IS_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON))
#define IS_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_TEMIL_COMMON_PHONE_CALL_HANDLING_SKELETON))

typedef struct _ComLgeTemilCommonPhoneCallHandlingSkeleton ComLgeTemilCommonPhoneCallHandlingSkeleton;
typedef struct _ComLgeTemilCommonPhoneCallHandlingSkeletonClass ComLgeTemilCommonPhoneCallHandlingSkeletonClass;
typedef struct _ComLgeTemilCommonPhoneCallHandlingSkeletonPrivate ComLgeTemilCommonPhoneCallHandlingSkeletonPrivate;

struct _ComLgeTemilCommonPhoneCallHandlingSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  ComLgeTemilCommonPhoneCallHandlingSkeletonPrivate *priv;
};

struct _ComLgeTemilCommonPhoneCallHandlingSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType com_lge_temil_common_phone_call_handling_skeleton_get_type (void) G_GNUC_CONST;

ComLgeTemilCommonPhoneCallHandling *com_lge_temil_common_phone_call_handling_skeleton_new (void);


G_END_DECLS

#endif /* __COMMONPHONE_H__ */
