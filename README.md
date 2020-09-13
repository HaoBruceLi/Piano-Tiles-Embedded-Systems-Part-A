# Piano Tiles

This implementation of piano tiles is for the UCFK4.

The game initially allows you to select between "NORMAL MODE" and "AUTO MODE" (press up and down to change mode and pushing the joystick to select).
* Normal mode will run the game as expected
* Auto mode will automatically play the notes of a song for you

Next, the song can be selected using the same controls as before. When the joystick is pushed, the two fun kits will synchronise and begin playing after a short countdown.

The game consists of notes scrolling down the columns of the display.
Each joystick direction corresponds to a different column and the appropriate direction must be selected to play the currently displayed note.

From left to right, the joystick directions corresponding to each column are:

Far Left | Mid Left | Middle | Mid Right | Far Right
-------- | -------- | ------ | --------- | ---------
   UP    |   LEFT   |  PUSH  |   RIGHT   |   DOWN


- - - -

The game can be compiled by running the `make` command and the fun kits can be programmed with `make program`.
