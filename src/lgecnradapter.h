//
// Created by root on 5/11/17.
//

#ifndef GST_PLUGINS_LGECNRADAPTER_H
#define GST_PLUGINS_LGECNRADAPTER_H

#include <gst/base/gstadapter.h>

/****************************************************************************
 *                             +------------------------+
 * <MIC Stream>     MIC_IN --- |                        | --- MIC_OUT
 *                             |                        |
 *                             | LGECNR_FilterProcess   |
 *                             |                        |
 * <RECV Stream>   RECV_IN --- |                        | --- RECV_OUT
 *                             +------------------------+
 ****************************************************************************
 */
class LgEcnrAdapter {
public:
    LgEcnrAdapter ();
    virtual ~LgEcnrAdapter();
    gboolean PushMicBuffer (GstBuffer *buffer);
    GstBuffer *PopMicBuffer ();
    gboolean PushRecvBuffer (GstBuffer *buffer);
    GstBuffer *PopRecvBuffer ();
    void process ();

    GstBuffer *ReadFromRecvInAdapter(GstClockTime rec_time);
private:
    inline void MICIN_LOCK () {g_mutex_lock (m_MicInLock);}
    inline void MICIN_UNLOCK () {g_mutex_unlock (m_MicInLock);}
    inline void MICOUT_LOCK () {g_mutex_lock (m_MicOutLock);}
    inline void MICOUT_UNLOCK () {g_mutex_unlock (m_MicOutLock);}
    inline void RECVIN_LOCK () {g_mutex_lock (m_RecvInLock);}
    inline void RECVIN_UNLOCK () {g_mutex_unlock (m_RecvInLock);}
    inline void RECVOUT_LOCK () {g_mutex_lock (m_RecvOutLock);}
    inline void RECVOUT_UNLOCK () {g_mutex_unlock (m_RecvOutLock);}

    GMutex          m_MicInLock, m_MicOutLock, m_RecvInLock, m_RecvOutLock;
    GstAdapter      *m_MicInAdapter;
    GstAdapter      *m_MicOutAdapter;
    GstAdapter      *m_RecvInAdapter;
    GstAdapter      *m_RecvOutAdapter;
    //GstClockTime    m_MicStreamBaseTime;    //absolute time
    //GstClockTime    m_RecvStreamBaseTime;   //absolute time
    GstClockTime    m_PrevRefTime;              //absolute time
    GstClockTime    m_InitialMicPts;
    GstClockTime    m_InitialRecvPts;
    GstClockTime    m_RecvStreamLatency;
    GstClockTime    m_RecvStreamDelay;
    guint           m_PeriodSize;
    GstClockTime    m_PeriodTime;
    GstClockTime    m_RecvStreamLatency;
    GstClockTime    m_RecvStreamDelay;
    // stream info
    gint            m_rate;
    gint            m_channels;
    gint            m_bpf;
};


#endif //GST_PLUGINS_LGECNRADAPTER_H
