/*
 * Generated by gdbus-codegen 2.32.4. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __DBUS_CARCONFIGPROVIDER_INTERFACE_H__
#define __DBUS_CARCONFIGPROVIDER_INTERFACE_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for com.lge.geely.CarConfigProviderInterface */

#define TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE (com_lge_geely_car_config_provider_interface_get_type ())
#define COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE, ComLgeGeelyCarConfigProviderInterface))
#define IS_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE))
#define COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE, ComLgeGeelyCarConfigProviderInterfaceIface))

struct _ComLgeGeelyCarConfigProviderInterface;
typedef struct _ComLgeGeelyCarConfigProviderInterface ComLgeGeelyCarConfigProviderInterface;
typedef struct _ComLgeGeelyCarConfigProviderInterfaceIface ComLgeGeelyCarConfigProviderInterfaceIface;

struct _ComLgeGeelyCarConfigProviderInterfaceIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_get_car_config_data) (
    ComLgeGeelyCarConfigProviderInterface *object,
    GDBusMethodInvocation *invocation,
    gint arg_index);

  gboolean (*handle_get_vehicle_info_data) (
    ComLgeGeelyCarConfigProviderInterface *object,
    GDBusMethodInvocation *invocation,
    gint arg_index);

  void (*notify_update_car_config_data) (
    ComLgeGeelyCarConfigProviderInterface *object,
    gint arg_index);

  void (*notify_update_vehicle_info_data) (
    ComLgeGeelyCarConfigProviderInterface *object,
    gint arg_index);

};

GType com_lge_geely_car_config_provider_interface_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *com_lge_geely_car_config_provider_interface_interface_info (void);
guint com_lge_geely_car_config_provider_interface_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void com_lge_geely_car_config_provider_interface_complete_get_car_config_data (
    ComLgeGeelyCarConfigProviderInterface *object,
    GDBusMethodInvocation *invocation,
    gint data);

void com_lge_geely_car_config_provider_interface_complete_get_vehicle_info_data (
    ComLgeGeelyCarConfigProviderInterface *object,
    GDBusMethodInvocation *invocation,
    gint data);



/* D-Bus signal emissions functions: */
void com_lge_geely_car_config_provider_interface_emit_notify_update_car_config_data (
    ComLgeGeelyCarConfigProviderInterface *object,
    gint arg_index);

void com_lge_geely_car_config_provider_interface_emit_notify_update_vehicle_info_data (
    ComLgeGeelyCarConfigProviderInterface *object,
    gint arg_index);



/* D-Bus method calls: */
void com_lge_geely_car_config_provider_interface_call_get_car_config_data (
    ComLgeGeelyCarConfigProviderInterface *proxy,
    gint arg_index,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_geely_car_config_provider_interface_call_get_car_config_data_finish (
    ComLgeGeelyCarConfigProviderInterface *proxy,
    gint *out_data,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_geely_car_config_provider_interface_call_get_car_config_data_sync (
    ComLgeGeelyCarConfigProviderInterface *proxy,
    gint arg_index,
    gint *out_data,
    GCancellable *cancellable,
    GError **error);

void com_lge_geely_car_config_provider_interface_call_get_vehicle_info_data (
    ComLgeGeelyCarConfigProviderInterface *proxy,
    gint arg_index,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean com_lge_geely_car_config_provider_interface_call_get_vehicle_info_data_finish (
    ComLgeGeelyCarConfigProviderInterface *proxy,
    gint *out_data,
    GAsyncResult *res,
    GError **error);

gboolean com_lge_geely_car_config_provider_interface_call_get_vehicle_info_data_sync (
    ComLgeGeelyCarConfigProviderInterface *proxy,
    gint arg_index,
    gint *out_data,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY (com_lge_geely_car_config_provider_interface_proxy_get_type ())
#define COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY, ComLgeGeelyCarConfigProviderInterfaceProxy))
#define COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY, ComLgeGeelyCarConfigProviderInterfaceProxyClass))
#define COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY, ComLgeGeelyCarConfigProviderInterfaceProxyClass))
#define IS_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY))
#define IS_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_PROXY))

typedef struct _ComLgeGeelyCarConfigProviderInterfaceProxy ComLgeGeelyCarConfigProviderInterfaceProxy;
typedef struct _ComLgeGeelyCarConfigProviderInterfaceProxyClass ComLgeGeelyCarConfigProviderInterfaceProxyClass;
typedef struct _ComLgeGeelyCarConfigProviderInterfaceProxyPrivate ComLgeGeelyCarConfigProviderInterfaceProxyPrivate;

struct _ComLgeGeelyCarConfigProviderInterfaceProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  ComLgeGeelyCarConfigProviderInterfaceProxyPrivate *priv;
};

struct _ComLgeGeelyCarConfigProviderInterfaceProxyClass
{
  GDBusProxyClass parent_class;
};

GType com_lge_geely_car_config_provider_interface_proxy_get_type (void) G_GNUC_CONST;

void com_lge_geely_car_config_provider_interface_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeGeelyCarConfigProviderInterface *com_lge_geely_car_config_provider_interface_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeGeelyCarConfigProviderInterface *com_lge_geely_car_config_provider_interface_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void com_lge_geely_car_config_provider_interface_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ComLgeGeelyCarConfigProviderInterface *com_lge_geely_car_config_provider_interface_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
ComLgeGeelyCarConfigProviderInterface *com_lge_geely_car_config_provider_interface_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON (com_lge_geely_car_config_provider_interface_skeleton_get_type ())
#define COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON, ComLgeGeelyCarConfigProviderInterfaceSkeleton))
#define COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON, ComLgeGeelyCarConfigProviderInterfaceSkeletonClass))
#define COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON, ComLgeGeelyCarConfigProviderInterfaceSkeletonClass))
#define IS_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON))
#define IS_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_COM_LGE_GEELY_CAR_CONFIG_PROVIDER_INTERFACE_SKELETON))

typedef struct _ComLgeGeelyCarConfigProviderInterfaceSkeleton ComLgeGeelyCarConfigProviderInterfaceSkeleton;
typedef struct _ComLgeGeelyCarConfigProviderInterfaceSkeletonClass ComLgeGeelyCarConfigProviderInterfaceSkeletonClass;
typedef struct _ComLgeGeelyCarConfigProviderInterfaceSkeletonPrivate ComLgeGeelyCarConfigProviderInterfaceSkeletonPrivate;

struct _ComLgeGeelyCarConfigProviderInterfaceSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  ComLgeGeelyCarConfigProviderInterfaceSkeletonPrivate *priv;
};

struct _ComLgeGeelyCarConfigProviderInterfaceSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType com_lge_geely_car_config_provider_interface_skeleton_get_type (void) G_GNUC_CONST;

ComLgeGeelyCarConfigProviderInterface *com_lge_geely_car_config_provider_interface_skeleton_new (void);


G_END_DECLS

#endif /* __DBUS_CARCONFIGPROVIDER_INTERFACE_H__ */