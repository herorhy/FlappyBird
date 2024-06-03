#ifndef _MUSICSPRITE_H_
#define _MUSICSPRITE_H_

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include"MixerManager.h"
using namespace std;

class MusicSprite :public Mixer
{
public:
	MusicSprite(string name);
	
	void Play();
	void Pause();
	void Rusume();
	void FreeMix();

	void MusicShutDown();//Œﬁ∑®”√Mix_ResumeMusic()ª÷∏¥
	
private:
	Mix_Music* Music;
	void FadeInMusicDraw(int loops, int times);	
	void SetVolumeMusicDraw(int Volume);
	void SetVolumeChannelDraw(int Volume);
};

#endif // !_MUSICSPRITE_H_