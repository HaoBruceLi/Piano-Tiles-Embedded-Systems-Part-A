/** @file   melody_task.c
    @author Narottam Royal， Hao Li
    @date   16 October 2018
*/

#include "display_task.h"
#include "melody_task.h"
#include "mmelody.h"
#include "songs.h"
#include "tweeter_task.h"


void tune_task_init(song_melody_t song,
                    uint8_t bpm,
                    play_note_t play_note,
                    bool auto_mode)
{
    melody = mmelody_init(&melody_info, TUNE_TASK_RATE,
			   (mmelody_callback_t) play_note, tweeter,
         PLAY_TUNE_DELAY, auto_mode, false);

		tweeter_set_period(song.tweeter_period);

    mmelody_speed_set(melody, bpm);
		mmelody_octave_set(melody, song.octave);
    mmelody_play(melody, song.melody);
}


void tune_task(__unused__ void *data)
{
    mmelody_update(melody);
    mmelody_update(display);
}
