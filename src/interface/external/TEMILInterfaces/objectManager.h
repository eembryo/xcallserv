/*
 * Generated by gdbus-codegen 2.32.4. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ---- */

#define TYPE_OBJECT (object_get_type ())
#define OBJECT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT, Object))
#define IS_OBJECT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT))
#define OBJECT_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_OBJECT, Object))

struct _Object;
typedef struct _Object Object;
typedef struct _ObjectIface ObjectIface;

struct _ObjectIface
{
  GTypeInterface parent_iface;
};

GType object_get_type (void) G_GNUC_CONST;


#define TYPE_OBJECT_PROXY (object_proxy_get_type ())
#define OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_PROXY, ObjectProxy))
#define OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_OBJECT_PROXY, ObjectProxyClass))
#define OBJECT_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_OBJECT_PROXY, ObjectProxyClass))
#define IS_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_PROXY))
#define IS_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_OBJECT_PROXY))

typedef struct _ObjectProxy ObjectProxy;
typedef struct _ObjectProxyClass ObjectProxyClass;
typedef struct _ObjectProxyPrivate ObjectProxyPrivate;

struct _ObjectProxy
{
  /*< private >*/
  GDBusObjectProxy parent_instance;
  ObjectProxyPrivate *priv;
};

struct _ObjectProxyClass
{
  GDBusObjectProxyClass parent_class;
};

GType object_proxy_get_type (void) G_GNUC_CONST;
ObjectProxy *object_proxy_new (GDBusConnection *connection, const gchar *object_path);

#define TYPE_OBJECT_SKELETON (object_skeleton_get_type ())
#define OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_SKELETON, ObjectSkeleton))
#define OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_OBJECT_SKELETON, ObjectSkeletonClass))
#define OBJECT_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_OBJECT_SKELETON, ObjectSkeletonClass))
#define IS_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_SKELETON))
#define IS_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_OBJECT_SKELETON))

typedef struct _ObjectSkeleton ObjectSkeleton;
typedef struct _ObjectSkeletonClass ObjectSkeletonClass;
typedef struct _ObjectSkeletonPrivate ObjectSkeletonPrivate;

struct _ObjectSkeleton
{
  /*< private >*/
  GDBusObjectSkeleton parent_instance;
  ObjectSkeletonPrivate *priv;
};

struct _ObjectSkeletonClass
{
  GDBusObjectSkeletonClass parent_class;
};

GType object_skeleton_get_type (void) G_GNUC_CONST;
ObjectSkeleton *object_skeleton_new (const gchar *object_path);

/* ---- */

#define TYPE_OBJECT_MANAGER_CLIENT (object_manager_client_get_type ())
#define OBJECT_MANAGER_CLIENT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_MANAGER_CLIENT, ObjectManagerClient))
#define OBJECT_MANAGER_CLIENT_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_OBJECT_MANAGER_CLIENT, ObjectManagerClientClass))
#define OBJECT_MANAGER_CLIENT_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_OBJECT_MANAGER_CLIENT, ObjectManagerClientClass))
#define IS_OBJECT_MANAGER_CLIENT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_MANAGER_CLIENT))
#define IS_OBJECT_MANAGER_CLIENT_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_OBJECT_MANAGER_CLIENT))

typedef struct _ObjectManagerClient ObjectManagerClient;
typedef struct _ObjectManagerClientClass ObjectManagerClientClass;
typedef struct _ObjectManagerClientPrivate ObjectManagerClientPrivate;

struct _ObjectManagerClient
{
  /*< private >*/
  GDBusObjectManagerClient parent_instance;
  ObjectManagerClientPrivate *priv;
};

struct _ObjectManagerClientClass
{
  GDBusObjectManagerClientClass parent_class;
};

GType object_manager_client_get_type (void) G_GNUC_CONST;

GType object_manager_client_get_proxy_type (GDBusObjectManagerClient *manager, const gchar *object_path, const gchar *interface_name, gpointer user_data);

void object_manager_client_new (
    GDBusConnection        *connection,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GAsyncReadyCallback     callback,
    gpointer                user_data);
GDBusObjectManager *object_manager_client_new_finish (
    GAsyncResult        *res,
    GError             **error);
GDBusObjectManager *object_manager_client_new_sync (
    GDBusConnection        *connection,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GError                **error);

void object_manager_client_new_for_bus (
    GBusType                bus_type,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GAsyncReadyCallback     callback,
    gpointer                user_data);
GDBusObjectManager *object_manager_client_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
GDBusObjectManager *object_manager_client_new_for_bus_sync (
    GBusType                bus_type,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GError                **error);


G_END_DECLS

#endif /* __OBJECTMANAGER_H__ */