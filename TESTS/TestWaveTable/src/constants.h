#pragma once

#define N_KNOBS 4

#define FRETBOARD_IN_PIN 1
#define MORPH_IN_PIN 2
#define RESO_IN_PIN 3
#define CUTOFF_IN_PIN 6
#define BEND_IN_PIN 7

#define OCT_UP_PIN 0
#define OCT_DWN_PIN 1
#define ROOT_SW_PIN 2
#define SCALE_SW_PIN 3


#define FRETBOARD_RANGE 1
#define MORPH_RANGE 2
#define RESO_RANGE 3
#define CUTOFF_RANGE 4
#define BEND_RANGE 5

int knobsInputs[N_KNOBS] = {MORPH_IN_PIN, RESO_IN_PIN, CUTOFF_IN_PIN, BEND_IN_PIN };