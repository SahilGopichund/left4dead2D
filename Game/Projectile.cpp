#include "Projectile.h"
#include <math.h>


Projectile::Projectile(int destination_x, int destination_y, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ, int hitboxR, int Identity, ALLEGRO_BITMAP *imag) : GameEntity(lif, maxX, maxY, xPos, yPos, speedX, speedY, Dir, activ, hitboxR, Identity, imag)
{
	
	//Animation Initialisation
	animationFrameHeight = 15;
	animationFrameWidth = 15;
	currentAnimationFrame = 0;
	frameCount = 0;
	frameDelay = 3;
	maxFrameCount = 3;
	direction = 0;

	//Bullet Path Initialisation
	old_pos_x = xPos;
	old_pos_y = yPos;
	destinationY = destination_y;
	destinationX = destination_x;
	angleOfPath = atan2f(destinationY - old_pos_y, destinationX - old_pos_x);
	hitboxHeight = 15;
	hitboxWidth = 15;

	//Other Initialisation
	explosionStarted = false;
}


Projectile::~Projectile()
{
}

bool Projectile::UpdatePosition()
{
	if (active)
	{
		if (((pos_x + int(speed_x*cosf(angleOfPath))) > 0) && ((pos_x + int(speed_x*cosf(angleOfPath))) < (maxXpos - animationFrameWidth)))
		{
			pos_x += int(speed_x*cosf(angleOfPath));
		}
		else
		{
			active = 0;
			if (!explosionStarted) explosionStarted = true;
		}
		if (((pos_y + int(speed_y*sinf(angleOfPath))) > 0) && ((pos_y + int(speed_y*sinf(angleOfPath))) < (maxYpos - animationFrameHeight)))
		{
			pos_y += int(speed_y*sinf(angleOfPath));
		}
		else
		{
			active = 0;
			if (!explosionStarted) explosionStarted = true;
		}
		return 1;
	}
	else return 0;
}

void Projectile::UpdateDirection()
{
	
}
void Projectile::update()
{
	if (active)
	{
		if (UpdatePosition())
		{
			UpdateDirection();
			UpdateAnimation();
		}
	}
	else if ((!active) && isAlive) //Explosion Sequence Out
	{
		if (explosionStarted)
		{
			image = al_load_bitmap("explosion.png");
			animationFrameHeight = 32;
			animationFrameWidth = 32;
			currentAnimationFrame = 0;
			frameCount = 0;
			frameDelay = 4;
			maxFrameCount = 12;
			explosionStarted = false;
		}
		UpdateAnimation();
		if (frameCount == 0)
			isAlive = false;
	}
}

void Projectile::Collided(GameEntity *otherObject)
{
	
	if (otherObject->getID() == ENEMY)
	{
		active = 0;
		if (!explosionStarted) explosionStarted = true;
	}
}