//
// Created by root on 5/11/17.
//

#include "lgecnradapter.h"

//LGECNR_PERIOD = 16 * GST_MSECOND
//period_size = 8000Hz * 0.016s * 2Bytes
#define LGECNR_PERIOD_SIZE 256

static inline GstClockTime CorrespondRecvTime(GstClockTime ref_time) {
    return ref_time + m_RecvStreamLatency + m_RecvStreamDelay;
}
static inline GstClockTime CorrespondMicTime(GstClockTime ref_time) {
    return ref_time;
}

static gboolean CopyBufferFromAdapter (GstBuffer *target, GstAdapter *src, gsize size) {
    GstMapInfo mapinfo;

    if (!gst_buffer_map (target, &mapinfo, GST_MAP_WRITE)) {
        return FALSE;
    }

    gst_adapter_copy (src, mapinfo.data, 0, size);
    gst_buffer_unmap (target, &mapinfo);
    return TRUE;

    _CopyBufferFromAdapter_failed:
    gst_buffer_unmap (target, &mapinfo);
    return FALSE;
}

LgEcnrAdapter::LgEcnrAdapter() :
        m_InitialMicPts(GST_CLOCK_TIME_NONE), m_InitialRecvPts(GST_CLOCK_TIME_NONE) {

}

LgEcnrAdapter::~LgEcnrAdapter() {
    MICIN_LOCK ();
    gst_adapter_clear (m_MicInAdapter);
    g_object_unref (m_MicInAdapter);
    MICIN_UNLOCK ();
    MICOUT_LOCK();
    gst_adapter_clear (m_MicOutAdapter);
    g_object_unref (m_MicOutAdapter);
    MICOUT_UNLOCK();
    RECVIN_LOCK();
    gst_adapter_clear (m_RecvInAdapter);
    g_object_unref (m_RecvInAdapter);
    RECVIN_UNLOCK();
    RECVOUT_LOCK();
    gst_adapter_clear (m_RecvOutAdapter);
    g_object_unref (m_RecvOutAdapter);
    RECVOUT_UNLOCK();
}

GstBuffer* LgEcnrAdapter::PopMicBuffer() {
    GstBuffer *out = NULL;
    gsize out_buffer_size = 0;

    if (gst_adapter_available (m_MicOutAdapter) < LGECNR_PERIOD_SIZE) {
        // Not enough data in MicOutAdapter
        return NULL;
    }

    out_buffer_size = gst_adapter_available(m_MicOutAdapter) % LGECNR_PERIOD_SIZE;
    out = gst_buffer_new_allocate (NULL, out_buffer_size, NULL);
    if (!out) {
        // memory couldnot be allocated
        goto _PopMicBuffer_failed;
    }

    MICOUT_LOCK(this);
    if (!CopyBufferFromAdapter(out, m_MicOutAdapter, out_buffer_size)) {
        MICOUT_UNLOCK(this);
        goto _PopMicBuffer_failed;
    }
    MICOUT_UNLOCK(this);

    return out;

    _PopMicBuffer_failed:
    if (out) gst_buffer_unref(out);
    return NULL;
}

GstBuffer* LgEcnrAdapter::PopRecvBuffer() {
    GstBuffer *out = NULL;
    gsize out_buffer_size = 0;

    if (gst_adapter_available (m_RecvOutAdapter) < LGECNR_PERIOD_SIZE) {
        // Not enough data in RecvOutAdapter
        return NULL;
    }

    out_buffer_size = gst_adapter_available(m_RecvOutAdapter) % LGECNR_PERIOD_SIZE;
    out = gst_buffer_new_allocate (NULL, out_buffer_size, NULL);
    if (!out) {
        // memory couldnot be allocated
        goto _PopRecvBuffer_failed;
    }

    RECVOUT_LOCK(this);
    if (!CopyBufferFromAdapter(out, m_RecvOutAdapter, out_buffer_size)) {
        RECVOUT_UNLOCK(this);
        goto _PopRecvBuffer_failed;
    }
    RECVOUT_UNLOCK(this);

    return out;

    _PopRecvBuffer_failed:
    if (out) gst_buffer_unref(out);
    return NULL;
}

gboolean LgEcnrAdapter::PushMicBuffer(GstBuffer *buffer) {
    MICIN_LOCK();
    gst_adapter_push (m_MicInAdapter, buffer);
    MICIN_UNLOCK();

    return TRUE;
}

/* process_first_buffer:
 * Remove zero data at the buffer beginning
 */
static gboolean process_first_buffer(GstBuffer *buffer) {

}

gboolean LgEcnrAdapter::PushRecvBuffer(GstBuffer *buffer) {
    RECVIN_LOCK();
    if (GST_BUFFER_FLAG_SET (buffer, GST_BUFFER_FLAG_DISCONT)) {
        gst_adapter_clear(m_RecvInAdapter);
        RECVOUT_LOCK();
        gst_adapter_clear(m_RecvOutAdapter);
        RECVOUT_UNLOCK();
        m_InitialRecvPts = GST_BUFFER_PTS(buffer);
    }
    gst_adapter_push (m_RecvInAdapter, buffer);
    RECVIN_UNLOCK();

    return TRUE;
}

static gssize adapter_available (GstAdapter *adapter, GstClockTime from) {
    GstClockTime adapter_pts;
    guint64 distance;
    guint64 diff_size = 0;
    gssize avail;

    adapter_pts = gst_adapter_prev_pts (adapter, &distance);
    adapter_pts += gst_util_uint64_scale_int(distance / m_bpf, GST_SECOND, m_rate);

    if (adapter_pts < from) {
        GstClockTimeDiff diff = from - adapter_pts;
        diff_size = diff * m_bpf;
    }
    avail = gst_adapter_available - diff_size;
    return avail > 0 ? avail : 0;
}
static gboolean fill_memory_from_adapter (GstClockTime time, GstAdapter *adapter, gchar *memory, guint *skip, gssize *size) {
    GstClockTime adapter_pts;

    adapter_pts =
}

void LgEcnrAdapter::process() {
    GstClockTime ref_time = m_PrevRefTime;
    gchar micstream_buf[m_PeriodSize];
    gchar recvstream_buf[m_PeriodSize];

    if (!GST_CLOCK_TIME_IS_VALID(ref_time)) {
        // if m_MicInAdapter and m_RecvInAdapter have enough data, set ref_time
    }
    else {
        ref_time += m_PeriodTime;
    }

    // if m_MicInAdapter and m_RecvInAdapter have enough data based on ref_time
    MICIN_LOCK();
    RECVIN_LOCK();

    GstClockTime micin_adapter_pts;
    guint64 micin_distance;
    micin_adapter_pts = gst_adapter_prev_pts (m_MicInAdapter, &micin_distance);


    MICIN_LOCK();
    // get a buffer that its pts is from m_RefTime to m_RefTime+period time in MicInAdapter
    MICIN_UNLOCK();

    RECVIN_LOCK();
    // get a buffer that its pts+latency is from m_RefTime to m_RefTime+period time in RecvInAdapter
    RECVIN_UNLOCK();

#if 0
    LGTSE_FilterProcess(lgecnr->mTseCtx, (char *) InputData, (char *) mapinfo.data, (char *) frame.data_,
                                (char *) outpuAudioBuffer, &lgecnr->volumeInfo);
#endif

    MICOUT_LOCK();

    MICOUT_UNLOCK();

    RECVOUT_LOCK();
    RECVOUT_UNLOCK();
}

GstBuffer *LgEcnrAdapter::ReadFromRecvInAdapter(GstClockTime rec_time) {
    RECVIN_LOCK();

    if (!GST_CLOCK_TIME_IS_VALID (m_RecvStreamLatency))
        goto done;

    if (!GST_CLOCK_TIME_IS_VALID (rec_time)) {
        goto done;
    }

    if (gst_adapter_available (m_RecvInAdapter) == 0) {
        diff = G_MAXINT64;
    } else {
        GstClockTime play_time;
        guint64 distance;

        play_time = gst_adapter_prev_pts (m_RecvStreamLatency, &distance);

        if (GST_CLOCK_TIME_IS_VALID (play_time)) {
            play_time += gst_util_uint64_scale_int (distance / lgecnrprobe->info.bpf,
                                                    GST_SECOND, lgecnrprobe->info.rate);
            play_time += m_RecvStreamLatency;

            diff = GST_CLOCK_DIFF (rec_time, play_time) / GST_MSECOND;
        } else {
            /* We have no timestamp, assume perfect delay */
            diff = lgecnrprobe->delay;
        }
        frame->timestamp = play_time;
    }

    avail = gst_adapter_available (lgecnrprobe->adapter);

    if (diff > lgecnrprobe->delay) {
        //skip = gst_util_uint64_scale(diff-m_RecvStreamDelay, rate, GST_SECOND) * bpf;
        skip = (diff - lgecnrprobe->delay) * lgecnrprobe->info.rate / 1000 * lgecnrprobe->info.bpf;
        skip = MIN (lgecnrprobe->period_size, skip);
        offset = 0;
    } else {
        skip = 0;
        offset = (lgecnrprobe->delay - diff) * lgecnrprobe->info.rate / 1000 * lgecnrprobe->info.bpf;
        offset = MIN (avail, offset);
    }

    size = MIN (avail - offset, lgecnrprobe->period_size - skip);

    if (size < lgecnrprobe->period_size)
        memset (frame->data_, 0, lgecnrprobe->period_size);

    copy:
    if (size) {
        gst_adapter_copy (lgecnrprobe->adapter, (guint8 *) frame->data_ + skip,
                          offset, size);
        gst_adapter_flush (lgecnrprobe->adapter, offset + size);
        frame->size = size;
    }

    frame->num_channels_ = lgecnrprobe->info.channels;
    frame->sample_rate_hz_ = lgecnrprobe->info.rate;
    frame->samples_per_channel_ = lgecnrprobe->period_size / lgecnrprobe->info.bpf;

    delay = lgecnrprobe->delay;

    done:
    RECVIN_UNLOCK();
    return NULL;
}

