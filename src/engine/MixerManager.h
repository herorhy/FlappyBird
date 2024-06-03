#ifndef _MIXERMANAGER_H_
#define _MIXERMANAGER_H_

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
using namespace std;

class Mixer
{
public:
	Mixer();
	virtual void Play()=0;
	virtual void Pause()=0;
	virtual void Rusume()=0;
	virtual void FreeMix()=0;

	virtual void FadeInMusicDraw(int loops, int times) = 0;
	virtual void SetVolumeMusicDraw(int Volume) = 0;
	virtual void SetVolumeChannelDraw(int Volume) = 0;

protected:
	string name_;
	
	
};
#endif // !_MIXERMANAGER_H_