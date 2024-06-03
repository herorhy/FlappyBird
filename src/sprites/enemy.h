#ifndef SG_SPRITES_ENEMY_H_
#define SG_SPRITES_ENEMY_H_

#include <cstdlib>

#include "engine/sprite.h"
#include "engine/group.h"
#include "engine/timer.h"
#include "engine/resman.h"

#include "gamedef.h"
#include "data.h"
//#include "main.h"
#include "sprites/bullet.h"

class Enemy : public Sprite {
public:
	/*Enemy(ParentPtr parent, ResManager &resman,
			Group *enemy_blt, Group *player_blt)
			: Sprite(parent, resman.GetImage("sg"), 576, 335, 130, 125),
			  resman_(resman), enemy_blt_(enemy_blt),
			  player_blt_(player_blt), hp_(kEnemyHP) {
		set_x(std::rand() % (kAreaWidth - width()));
		set_y(-height());
		set_bounding({0, 25, 130, 100});
		set_shake(std::rand() % 10 > 7);
	}*/
	//敌机位置
	/*Enemy(ParentPtr parent, ResManager& resman,
		Group* enemy_blt, Group* player_blt)
		: Sprite(parent, resman.GetImage("tube")),
		resman_(resman), enemy_blt_(enemy_blt),
		player_blt_(player_blt), hp_(kEnemyHP) {
		//更新敌机位置
		set_x(width()+800);
		set_y(std::rand() % (kAreaHeight - height()));
		set_bounding({ 0, 25, 130, 100 });
		set_shake(std::rand() % 10 > 7);
		set_rocket(std::rand() % 10 < 3);
		//set_ai(std::rand() % 10 > 7);
		set_updown(std::rand() % 10 == 5);
	}*/
	Enemy(ParentPtr parent, ResManager& resman, int posy_)
		: Sprite(parent, resman.GetImage("tube1")),
		resman_(resman), posy_(0) {
		//更新敌机位置
		set_x(900);
		set_y(posy_);
		set_bounding({ 100, 350, 185, 720 });
		/*set_shake(std::rand() % 10 > 7);
		set_rocket(std::rand() % 10 < 3);
		//set_ai(std::rand() % 10 > 7);
		set_updown(std::rand() % 10 == 5);*/
	}

	void Render(const SDLRendererPtr& renderer) override {
		/*set_y(y() + kEnemySpeed);*/
		//更改速度
		set_x(x() - kEnemySpeed);
		if (x() >= 123 && x() <= 125)
			GameData::IncreaseScore();
	
		//超出边界
		if (x() < -kAreaWidth) {
			parent()->RemoveObject(this);
			return;
		}
		
		Sprite::Render(renderer);
	}
	

private:
	ResManager& resman_;
	int posy_;
	//Group *enemy_blt_, *player_blt_;
	//Timer timer_;
	//int hp_;
	// status
	//bool shake_;
	//int interval_;
	//float org_, cur_;
	//bool rocket_;
	/*bool ai_;*/
	//bool updown_;
	//int updown_state;
};

#endif // SG_SPRITES_ENEMY_H_
