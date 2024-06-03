#include"MusicSprite.h"

MusicSprite::MusicSprite(Mix_Music* music)
{
	Music = music;
}

void MusicSprite::Play()
{
	if (Mix_PlayMusic(Music, -1) != 0)
	{
		cout << "Failed to play music: " << Mix_GetError() << endl;
	}
}

void MusicSprite::Pause()
{
	Mix_PauseMusic();
}

void MusicSprite::Rusume()
{
	Mix_ResumeMusic();
}

void MusicSprite::FreeMix()
{
	Mix_FreeMusic(Music);
	Mix_Quit();
}

void MusicSprite::MusicShutDown()//ÎÞ·¨ÓÃMix_ResumeMusic()»Ö¸´
{
	if (Mix_HaltMusic() != 0)
	{
		cout << "Failed to HaltMusic. " << Mix_GetError() << endl;
	}
}

void MusicSprite::FadeInMusicDraw(int loops, int times)
{
	if (Mix_FadeInMusic(Music, loops, times) != 0)
	{
		cout << "Failed to FadeInMusic. " << Mix_GetError() << endl;
	}
	cout << "draw FadeInMusicSprite loops " << loops << " times " << times << endl;
}
void MusicSprite::SetVolumeMusicDraw(int Volume)
{
	if (Mix_VolumeMusic(Volume) == 0)
	{
		cout << "Failed to VolumeMusic:" << Mix_GetError() << endl;
	}
	cout << "draw SetVolumeMusicDraw Volume " << Volume << endl;
}
void MusicSprite::SetVolumeChannelDraw(int Volume)
{
	if (Mix_Volume(1, Volume) != 0)
	{
		cout << "Failed to VolumeChunk: " << Mix_GetError() << endl;
	}

}