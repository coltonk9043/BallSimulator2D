#pragma once

#ifndef SOUND_H
#define SOUND_H

#include "../Common.h"

class Sound
{

public:
	Sound(char* filename);
	~Sound();
	void Play();
	void Stop();
private:
	ALvoid* data;
	ALCcontext* context;
	ALsizei size, freq;
	ALenum format;
	ALuint buffer, source;
	ALboolean loop = AL_FALSE;
};

#endif
