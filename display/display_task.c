/** @file   display_task.c
    @author Narottam Royal， Hao Li
    @date   16 October 2018
*/

#include <stdlib.h>
#include "display_task.h"
#include "ledmat.h"
#include "melody_task.h"
#include "mmelody.h"
#include "songs.h"
#include "tweeter_task.h"


#define DISPLAY_DELAY 0
#define NOTE_BITMAP 0b11
#define COLUMN_BITMAP 0b01111111


static uint8_t notes[LEDMAT_COLS_NUM] = {0};
static bool pressed_notes[LEDMAT_COLS_NUM] = {false};
static uint8_t pressed_notes_count = 0;
static uint8_t score = 0;


void display_task_init(song_melody_t song,
											uint8_t bpm,
											display_note_t display_note)
{
	// Initialise the LED matrix
	ledmat_init();

	display = mmelody_init(&display_info, TUNE_TASK_RATE,
			 (mmelody_callback_t) display_note, tweeter, DISPLAY_DELAY, false, true);

	mmelody_speed_set(display, bpm);
	mmelody_octave_set(display, song.octave);
	mmelody_play(display, song.melody);

	uint8_t i = 0;
	for (i = 0; i < LEDMAT_COLS_NUM; i++) {
		notes[i] = 0;
		pressed_notes[i] = false;
	}
	pressed_notes_count = 0;
	score = 0;
}


// Randomly selects a column and creates a new note
void display_task_create_note(__unused__ tweeter_t tweet,
															tweeter_note_t note,
															uint8_t velocity)
{
	// Only create a note if the note and velocity are non-zero
	if ((note & velocity) != 0) {
		// Randomly select a column
		uint8_t col = rand() % LEDMAT_COLS_NUM;

		// Ensure the current column is unused
		uint8_t i = 0;
		while (notes[col] != 0 && i++ < LEDMAT_COLS_NUM) {
			// Incrementing by 2 reduces the number of adjacent notes
			col = (col + 2) % LEDMAT_COLS_NUM;
		}
		// Create the note!
		notes[col] = 1;
	}
}


bool display_task_note_pressed_p()
{
	return pressed_notes_count > 0;
}


uint8_t display_task_score()
{
	return score;
}


// Illuminates an entire column if the corresponding button is pressed
void display_task_check_button(uint8_t button)
{
	if (notes[button] && notes[button] < LEDMAT_ROWS_NUM && !pressed_notes[button]) {
		pressed_notes[button] = true;
		pressed_notes_count++;
		score++;
	}
}


// Increments the position of each note
void display_task_increment(__unused__ void *data)
{
	uint8_t col = 0;
	for (col = 0; col < LEDMAT_COLS_NUM; col++) {
		if (notes[col] != 0) {
			notes[col]++;
			if (notes[col] > LEDMAT_ROWS_NUM + 2) {
				notes[col] = 0;
				if (pressed_notes[col] && pressed_notes_count > 0) {
					pressed_notes_count--;
				}
				pressed_notes[col] = false;
			}
		}
	}
}


// Updates a column of the display
void display_task_update(__unused__ void *data)
{
	static uint8_t col = 0;
	if (pressed_notes[col]) {
		ledmat_display_column(COLUMN_BITMAP, col);
	} else if (notes[col] != 0) {
		if (notes[col] == 1) {
			ledmat_display_column(NOTE_BITMAP >> notes[col], col);
		} else {
			ledmat_display_column(NOTE_BITMAP << (notes[col] - 2), col);
		}
	}
	col = (col + 1) % LEDMAT_COLS_NUM;
}
