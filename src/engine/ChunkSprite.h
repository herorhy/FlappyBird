#ifndef _CHUNKSPRITE_H_
#define _CHUNKSPRITE_H_

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include"MixerManager.h"
using namespace std;

class ChunkSprite :public Mixer
{
public:
	ChunkSprite(Mix_Chunk* chunk);

	void Play();
	void PlayAsBGM();
	void Pause();
	void Rusume();
	void FreeMix();

	void ChunkShutDown();
	static int numchan;
private:
	void FadeInMusicDraw(int loops, int times);
	void SetVolumeMusicDraw(int Volume);
	void SetVolumeChannelDraw(int Volume);
protected:
	Mix_Chunk* chunk_;
	int channel_;
};


#endif // !_CHUNKSPRITE_H_