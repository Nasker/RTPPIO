#pragma once

#include "RTPMusicController.h"

class MusicManager{
    RTPMusicController mControl;
public:
    MusicManager();
    void setCurrentHarmony(byte channel, byte control, byte value);
};
