/** @file   display_task.h
    @author Narottam Royal
    @date   16 October 2018
*/

#ifndef DISPLAY_H
#define DISPLAY_H


#include "mmelody.h"
#include "songs.h"
#include "tweeter_task.h"


#define DISPLAY_INCREMENT_RATE (4 * TUNE_BPM_RATE / 60.0)
#define DISPLAY_UPDATE_RATE 5000


typedef void (* display_note_t) (tweeter_t, tweeter_note_t, uint8_t);


mmelody_t display;
mmelody_obj_t display_info;


void display_task_init(song_melody_t song,
                      uint8_t bpm,
                      display_note_t display_note);


bool display_task_note_pressed_p(void);


uint8_t display_task_score(void);


// Illuminates an entire column if the corresponding button is pressed
void display_task_check_button(uint8_t button);


// Randomly selects a column and creates a new note
void display_task_create_note(tweeter_t tweet,
															tweeter_note_t note,
															uint8_t velocity);


// Increments the position of each note
void display_task_increment(void *data);


// Updates a column of the display
void display_task_update(void *data);


#endif
