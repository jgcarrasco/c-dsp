#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <pulse/simple.h>
#include <pulse/error.h>

#define BUFSIZE 1024


int main(int argc, char *argv[]) {
    /* The sample type to use */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 48000,
        .channels = 2
    };

    pa_buffer_attr buffer_attr;
    buffer_attr.maxlength = (uint32_t)-1;
    buffer_attr.tlength = pa_usec_to_bytes(20000, &ss); // Target buffer length of 20ms
    buffer_attr.prebuf = (uint32_t)-1;
    buffer_attr.minreq = (uint32_t)-1;
    buffer_attr.fragsize = pa_usec_to_bytes(20000, &ss); // Recording fragment size of 20ms

    pa_simple *s_record  = NULL;
    pa_simple *s_playback= NULL;
    int ret = 1;
    int error;

    /* Create the recording stream */
    if (!(s_record = pa_simple_new(NULL, argv[0], PA_STREAM_RECORD, NULL, "record", &ss, NULL, &buffer_attr, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }

    /* Create the playback stream */
    if (!(s_playback = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "record", &ss, NULL, &buffer_attr, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }

    uint8_t buffer[BUFSIZE];

    for (;;) {
        /* Read data from microphone */
        if (pa_simple_read(s_record, buffer, sizeof(buffer), &error) < 0) {
            fprintf(stderr, "PulseAudio read failed: %s\n", pa_strerror(error));
            goto finish;
        }

        /* Write data to the speakers */
        if (pa_simple_write(s_playback, buffer, sizeof(buffer), &error) < 0) {
            fprintf(stderr, "Pulseaudio write failed: %s\n", pa_strerror(error));
            goto finish;
        }
    }


finish:
    
    if (s_record)
        pa_simple_free(s_record);
    if (s_playback)
        pa_simple_free(s_playback);

    return 0;
}
