#include"ChunkSprite.h"

int ChunkSprite::numchan = 0;

ChunkSprite:: ChunkSprite(Mix_Chunk* chunk)
	:chunk_(chunk)
{
	channel_ = numchan;
	Mix_AllocateChannels(++numchan);
}

void ChunkSprite::Play()
{
	Mix_PlayChannel(channel_, chunk_, 0);
}
void ChunkSprite::PlayAsBGM()
{
	Mix_PlayChannel(channel_, chunk_, -1);
}

void ChunkSprite::Pause()
{
	Mix_Pause(channel_);
}

void ChunkSprite::Rusume()
{
	Mix_Resume(channel_);
}

void ChunkSprite::FreeMix()
{
	Mix_FreeChunk(chunk_);
	Mix_Quit();
}

void ChunkSprite::ChunkShutDown()
{
	if (Mix_HaltChannel(channel_) != 0)
	{
		cout << "Failed to HaltChannel: " << Mix_GetError() << endl;
	}
}

void ChunkSprite::FadeInMusicDraw(int loops, int times)
{
	/*if (Mix_FadeInMusic(Music, loops, times) != 0)
	{
		cout << "Failed to FadeInMusic. " << Mix_GetError() << endl;
	}
	cout << "draw FadeInMusicSprite loops " << loops << " times " << times << endl;*/
}
void ChunkSprite::SetVolumeMusicDraw(int Volume)
{
	if (Mix_VolumeMusic(Volume) == 0)
	{
		cout << "Failed to VolumeMusic:" << Mix_GetError() << endl;
	}
	cout << "draw SetVolumeMusicDraw Volume " << Volume << endl;
}
void ChunkSprite::SetVolumeChannelDraw(int Volume)
{
	if (Mix_Volume(1, Volume) == 0)
	{
		cout << "Failed to VolumeChunk: " << Mix_GetError() << endl;
	}
	cout << "draw SetVolumeChannelDraw Volume " << Volume << endl;

}