#ifndef _MIXER_H_
#define _MIXER_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include"MixerManager.h"
using namespace std;

class Decorater :public Mixer
{
public:
	Mixer* _mixermanager;

	Decorater(Mixer* mixermanager) { _mixermanager = mixermanager; cout << "A MixerDecorater is Created" << endl; };
	void addon();
	void FadeInMusicDraw(int loops, int times)
	{
		addon();
		_mixermanager->FadeInMusicDraw(loops, times);

	}
	void SetVolumeMusicDraw(int Volume)
	{
		addon();
		_mixermanager->SetVolumeMusicDraw(Volume);
	}
	void SetVolumeChannelDraw(int Volume)
	{
		addon();
		_mixermanager->SetVolumeChannelDraw(Volume);
	}
};

#endif // !_MIXER_H_

