#include "Player.h"
#include "InputManager.h"
#include "EntityManager.h"
#define PI 3.14159265

Player::Player(int score, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ,
	int hitboxR, int Identity, ALLEGRO_BITMAP *imag, ALLEGRO_BITMAP *bulletSpriteSheet) :GameEntity(lif, maxX, maxY, xPos, yPos, speedX, speedY, Dir, activ, hitboxR, Identity, imag)
{
	score = 0;
	shooting_control = 0;
	animationFrameHeight = 32;
	animationFrameWidth = 32;
	currentAnimationFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	maxFrameCount = 8;
	minFrameCount = 0;
	this->bulletSpriteSheet = bulletSpriteSheet;
	hitboxHeight = 32;
	hitboxWidth = 32;
}


Player::~Player()
{
}

void Player::update()
{
	ShootCheck();
	if (UpdatePosition())
	{
		UpdateDirection();
		UpdateAnimation();
	}
}

void Player::UpdateDirection()
{
	enum dir{ D, L, R, U };
	if (InputManager::getInstance().isKeyPressed(UP))
	{
		direction = U;
	}
	else if (InputManager::getInstance().isKeyPressed(DOWN))
	{
		direction = D;
	}
	else if (InputManager::getInstance().isKeyPressed(RIGHT))
	{
		direction = R;
	}
	else if (InputManager::getInstance().isKeyPressed(LEFT))
	{
		direction = L;
	}
}
bool Player::UpdatePosition()
{
	int horizontal = 0;
	int vertical = 0;
	old_pos_x = pos_x;
	old_pos_y = pos_y;

	//get inputs
	if (InputManager::getInstance().isKeyPressed(UP))
	{
		vertical = -1;
	}
	if (InputManager::getInstance().isKeyPressed(DOWN))
	{
		vertical = 1;
	}
	if (InputManager::getInstance().isKeyPressed(RIGHT))
	{
		horizontal = 1;
	}
	if (InputManager::getInstance().isKeyPressed(LEFT))
	{
		horizontal = -1;
	}

	
	//move position
	if (((pos_x + speed_x*horizontal) > 0) && ((pos_x + speed_x*horizontal) < (maxXpos - animationFrameWidth)))
	{
			pos_x += speed_x*horizontal;
	}
	if (((pos_y + speed_y*vertical) > 0) && ((pos_y + speed_y*vertical) < (maxYpos - animationFrameHeight)))
	{
		pos_y += speed_y*vertical;
	}

		if ((old_pos_x == pos_x) && (old_pos_y == pos_y))
			return 0;
		else return 1;
}

void Player::ShootCheck()
{
	hasShot = false;
	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
		hasShot = true;
	if (hasShot)
	{
		if ((shooting_control == 0) || (shooting_control > 3))
		{
			int destination_x = InputManager::getInstance().getMouseX();
			float destination_y = InputManager::getInstance().getMouseY();
			Projectile *bulletPtr = new Projectile(destination_x, destination_y, 0, 800, 600, pos_x, pos_y, 10, 10, 0, 1, 2, PROJECTILE, bulletSpriteSheet);
			EntityManager::getInstance().AddEntity(bulletPtr);
			shooting_control = 0;
		}
		shooting_control++;
		
	}
	
}
void Player::megaShot(){//shoots 24 projectiles radially around the player
	int destination_x, destination_y;
	for (int angle = 0; angle < 360; angle += 15)
	{
		destination_x = pos_x + 100*cosf(angle*PI/180);
		destination_y = pos_y + 100*sinf(angle*PI/180);
		Projectile *bulletPtr = new Projectile(destination_x, destination_y, 0, 800, 600, pos_x, pos_y, 10, 10, 0, 1, 2, PROJECTILE, bulletSpriteSheet);
		EntityManager::getInstance().AddEntity(bulletPtr);
	}
}
int Player::GetPos_X()
{
	return pos_x;
}

int Player::GetPos_Y()
{
	return pos_y;
}