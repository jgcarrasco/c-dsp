#include "portaudio.h"

typedef int PaStreamCallback( const void *input,
                                void *output,
                                unsigned long frameCount,
                                const PaStreamCallbackTimeInfo *timeInfo,
                                PaStreamCallbackFlags statusFlags,
                                void *userData );

typedef struct {
    float left_phase;
    float right_phase;
} paTestData;

static int patestCallback ( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo *timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData ) {
    /* Cast data passed through stream to out structure */
    paTestData *data = (paTestData*) userData;
    float *out = (float*) outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning */

    for ( i = 0; i < framesPerBuffer; i++) {
        out++ = data->left_phase;
        out++ = data->right_phase;
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0 */
        data->left_phase += 0.01f;
        /* When signal reaches top, drop back down */
        if (data->left_phase >= 1.0f) 
            data->left_phase -= 2.0f;
        /* Higher pitch so we can distinguish left and right */
        data->right_phase += 0.03f;
        if (data->right_phase >= 1.0f)
            data->right_phase -= 2.0f;
    }
    return 0;
}
