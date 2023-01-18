#include "Sound.h"

Sound::Sound(std::string filename) {
	alutLoadWAVFile(filename, &format, &data, &size, &freq, &loop);
}

Sound::~Sound() {
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	//device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
}

void Sound::Play() {
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);


}