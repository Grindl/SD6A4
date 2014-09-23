#pragma once
#ifndef include_PLAYER
#define include_PLAYER

#include <math.h>

const float MAX_SPEED = 20.f;
const float MOVE_SPEED = 10.f;
const float GRAVITY = 8.f;
const float JUMP_IMPULSE = 10.f;
enum moveState {WALK, FLY, NOCLIP};
const float WIDTH = 0.4f; //as distance from center
const float HEIGHT = 0.8f; //as distance from center
const float epsilon = .00001f;

class Player
{
public:
	float m_position[3];
	float m_velocity[3];
	float m_orientation[3];
	bool m_isOnGround;
	float m_timeSinceLastFootstep;
	moveState m_currentMovementState;

	Player();
	void update(float dt);
	float incrementalMove(float dt);
	void jump();
	void flyVertical(float zVelocity);
	bool shouldPlayWalkSound();
};

Player::Player()
{
	m_currentMovementState = NOCLIP;
	m_position[0] = 0.f;
	m_position[1] = 0.f;
	m_position[2] = 0.f;
	m_velocity[0] = 0.f;
	m_velocity[1] = 0.f;
	m_velocity[2] = 0.f;
	m_orientation[0] = 0.f;
	m_orientation[1] = 0.f;
	m_orientation[2] = 0.f;
	m_timeSinceLastFootstep = 0.f;
}


void Player::update(float dt)
{
	if(m_currentMovementState == WALK)
	{
		//apply gravity
		//if(!m_isOnGround)
		{
			m_velocity[2] -= 5.f*dt;
		}

		m_timeSinceLastFootstep += dt;
	}
	
	if(m_currentMovementState == WALK || m_currentMovementState == FLY)
	{
		float timeLeftToMove = dt;
		while (timeLeftToMove > 0+epsilon)
		{
			//timeLeftToMove = incrementalMove(timeLeftToMove);
		}
	}
	else
	{
		m_position[0]+= m_velocity[0]*dt;
		m_position[1]+= m_velocity[1]*dt;
		m_position[2]+= m_velocity[2]*dt;
	}
}

//TODO: player falls through world when facing south and not moving horizontally
//float Player::incrementalMove(float dt)
//{
//	float timeLeft = dt;
//
//	bool posX, posY, posZ;
//	posX = m_velocity[0] >= 0;
//	posY = m_velocity[1] >= 0;
//	posZ = m_velocity[2] >= 0;
//
//	//the use of epsilon is to guarantee we cross the boundary
//	float timeToX, timeToY, timeToZ;
//	float adjustedX, adjustedY, adjustedZ;
//	float distX, distY, distZ;
//	/*timeToX = (posX - (m_position[0] - floor(m_position[0])))/m_velocity[0] + epsilon;
//	timeToY = (posY - (m_position[1] - floor(m_position[1])))/m_velocity[1] + epsilon;
//	timeToZ = (posZ - (m_position[2] - floor(m_position[2])))/m_velocity[2] + epsilon;
//	*/
//	if(posX)
//	{
//		adjustedX = m_position[0]+WIDTH;
//		distX = 1 - (adjustedX - floor(adjustedX));
//	}
//	else
//	{
//		adjustedX = m_position[0]-WIDTH;
//		distX = floor(adjustedX) - adjustedX;
//	}
//
//	if(posY)
//	{
//		adjustedY = m_position[1]+WIDTH;
//		distY = 1 - (adjustedY - floor(adjustedY));
//	}
//	else
//	{
//		adjustedY = m_position[1]-WIDTH;
//		distY =  floor(adjustedY) - adjustedY;
//	}
//
//	if(posZ)
//	{
//		adjustedZ = m_position[2]+HEIGHT;
//		distZ = 1 - (adjustedZ - floor(adjustedZ));
//	}
//	else
//	{
//		adjustedZ = m_position[2]-HEIGHT;
//		distZ = floor(adjustedZ) - adjustedZ;
//	}
//
//	timeToX = distX/m_velocity[0]+epsilon;
//	timeToY = distY/m_velocity[1]+epsilon;
//	timeToZ = distZ/m_velocity[2]+epsilon;
//
//	if(!(timeToX > timeToY || timeToY > timeToX || timeToY == timeToX))
//	{
//		int q = 0;
//		q++;
//		//I AM AN ERRRORRRR
//	}
//
//	//note: these first two comparisons are inverted because one of these floats could potentially be NaN, and any comparison involving NaN returns false
//	//hence, timeToX > timeToY will return false if it is smaller, or if timeToY is NaN
//	//we catch the possibility that timeToX is NaN with the final comparison to deltaTime
//	//we also have to watch out for -infinity, since it is technically smaller than dt
//
//	if(!(timeToX > timeToY) && !(timeToX > timeToZ) && timeToX < dt && timeToX > 0)
//	{
//		int minimalY = (int)floor(m_position[1]-WIDTH);
//		int maximalY = (int)floor(m_position[1]+WIDTH);
//		int minimalZ = (int)floor(m_position[2]-HEIGHT);
//		int maximalZ = (int)floor(m_position[2]+HEIGHT);
//		Vector2i endingChunk = Vector2i((int)floor(m_position[0]/16.f), (int)floor(m_position[1]/16.f));
//		bool collided = false;
//		int xindex = m_velocity[0] > 0 ? (int)floor(m_position[0]+WIDTH)+1 : (int)floor(m_position[0]-WIDTH)-1;
//		for(int yindex = minimalY; yindex <= maximalY; yindex++)
//		{
//			for(int zindex = minimalZ; zindex <= maximalZ; zindex++)
//			{
//				//if any of these are solid
//				Chunk* targetChunk = p_world->at(endingChunk);
//				Vector2i dummyChunk;
//				int checkIndex = targetChunk->getCubeIndex(xindex - endingChunk.x*16, yindex - endingChunk.y*16, zindex, endingChunk, dummyChunk);
//				targetChunk = p_world->at(dummyChunk);
//				int material = targetChunk->getMaterialAtIndex(checkIndex);
//				if(!CUBE_TABLE[material].transparent)
//				{
//					collided = true;
//				}
//			}
//		}
//		//we should bump ourselves out of where we ended up
//		//and set our x velocity to 0
//		if(collided)
//		{
//			m_position[0] = m_position[0] + m_velocity[0]*(timeToX - 2*epsilon);
//			m_velocity[0] = 0.f;
//			m_position[1] = m_position[1] + m_velocity[1]*(timeToX - 2*epsilon);
//			m_position[2] = m_position[2] + m_velocity[2]*(timeToX - 2*epsilon);
//		}
//		else
//		{
//			m_position[0] = m_position[0] + m_velocity[0]*timeToX;
//			m_position[1] = m_position[1] + m_velocity[1]*timeToX;
//			m_position[2] = m_position[2] + m_velocity[2]*timeToX;
//		}
//		
//		timeLeft = dt - timeToX;
//	}
//	else if(!(timeToY > timeToX) && !(timeToY > timeToZ) && timeToY < dt && timeToY > 0)
//	{
//		int minimalX = (int)floor(m_position[0]-WIDTH);
//		int maximalX = (int)floor(m_position[0]+WIDTH);
//		int minimalZ = (int)floor(m_position[2]-HEIGHT);
//		int maximalZ = (int)floor(m_position[2]+HEIGHT);
//		Vector2i endingChunk = Vector2i((int)floor(m_position[0]/16.f), (int)floor(m_position[1]/16.f));
//		bool collided = false;
//		int yindex = m_velocity[1] > 0 ? (int)floor(m_position[1]+WIDTH)+1 : (int)floor(m_position[1]-WIDTH)-1;
//		for(int xindex = minimalX; xindex <= maximalX; xindex++)
//		{
//			for(int zindex = minimalZ; zindex <= maximalZ; zindex++)
//			{
//				//if any of these are solid
//				Chunk* targetChunk = p_world->at(endingChunk);
//				Vector2i dummyChunk;
//				int checkIndex = targetChunk->getCubeIndex(xindex - endingChunk.x*16, yindex - endingChunk.y*16, zindex, endingChunk, dummyChunk);
//				targetChunk = p_world->at(dummyChunk);
//				int material = targetChunk->getMaterialAtIndex(checkIndex);
//				if(!CUBE_TABLE[material].transparent)
//				{
//					collided = true;
//				}
//			}
//		}
//		//we should bump ourselves out of where we ended up
//		//and set our y velocity to 0
//		if(collided)
//		{
//			m_position[0] = m_position[0] + m_velocity[0]*(timeToY - 2*epsilon);
//			m_position[1] = m_position[1] + m_velocity[1]*(timeToY - 2*epsilon);
//			m_velocity[1] = 0.f;								 
//			m_position[2] = m_position[2] + m_velocity[2]*(timeToY - 2*epsilon);
//		}
//		else
//		{
//			m_position[0] = m_position[0] + m_velocity[0]*timeToY;
//			m_position[1] = m_position[1] + m_velocity[1]*timeToY;
//			m_position[2] = m_position[2] + m_velocity[2]*timeToY;
//		}
//
//
//		timeLeft = dt - timeToY;
//	}
//	else if(!(timeToZ > timeToX) && !(timeToZ > timeToY) && timeToZ < dt && timeToZ > 0)
//	{
//		int minimalY = (int)floor(m_position[1]-WIDTH);
//		int maximalY = (int)floor(m_position[1]+WIDTH);
//		int minimalX = (int)floor(m_position[0]-WIDTH);
//		int maximalX = (int)floor(m_position[0]+WIDTH);
//		Vector2i endingChunk = Vector2i((int)floor(m_position[0]/16.f), (int)floor(m_position[1]/16.f));
//		bool collided = false;
//		int zindex = m_velocity[2] > 0 ? (int)floor(m_position[2]+HEIGHT)+1 : (int)floor(m_position[2]-HEIGHT)-1;
//		for(int yindex = minimalY; yindex <= maximalY; yindex++)
//		{
//			for(int xindex = minimalX; xindex <= maximalX; xindex++)
//			{
//				//if any of these are solid
//				Chunk* targetChunk = p_world->at(endingChunk);
//				Vector2i dummyChunk;
//				int checkIndex = targetChunk->getCubeIndex(xindex - endingChunk.x*16, yindex - endingChunk.y*16, zindex, endingChunk, dummyChunk);
//				targetChunk = p_world->at(dummyChunk);
//				int material = targetChunk->getMaterialAtIndex(checkIndex);
//				if(!CUBE_TABLE[material].transparent)
//				{
//					collided = true;
//				}
//			}
//		}
//		//we should go up to but not into the thing that would collide
//		//and set our z velocity to 0
//		//also set on the ground to true
//		if(collided)
//		{
//			m_position[0] = m_position[0] + m_velocity[0]*(timeToZ - 2*epsilon);
//			m_position[1] = m_position[1] + m_velocity[1]*(timeToZ - 2*epsilon);	
//			m_position[2] = m_position[2] + m_velocity[2]*(timeToZ - 2*epsilon);
//			m_velocity[2] = 0.f;
//			m_isOnGround = true;
//		}
//		else
//		{
//			m_position[0] = m_position[0] + m_velocity[0]*timeToZ;
//			m_position[1] = m_position[1] + m_velocity[1]*timeToZ;
//			m_position[2] = m_position[2] + m_velocity[2]*timeToZ;
//			m_isOnGround = false;
//		}
//		timeLeft = dt - timeToZ;
//	}
//	//all time used or we aren't moving at all
//	else
//	{
//		m_position[0] = m_position[0] + m_velocity[0]*dt;
//		m_position[1] = m_position[1] + m_velocity[1]*dt;
//		m_position[2] = m_position[2] + m_velocity[2]*dt;
//		timeLeft = 0.f;
//	}
//
//	if(!(m_position[0] < 100000))
//	{
//		int i = 0;
//		i++;
//		//I AM AN ERRRORRRRR
//	}
//
//	return timeLeft;
//}

void Player::jump()
{
	if(m_currentMovementState == WALK)
	{
		if(m_isOnGround)
		{
			m_isOnGround = false;
			m_velocity[2] = 20.f;
		}
	}
}

void Player::flyVertical(float zVelocity)
{
	if(m_currentMovementState != WALK)
	{
		m_velocity[2] = zVelocity;
	}
	
}

bool Player::shouldPlayWalkSound()
{
	bool playSound = m_isOnGround && m_timeSinceLastFootstep > .5f && (m_velocity[0] != 0 || m_velocity[1] != 0) && m_currentMovementState == WALK;
	if(playSound)
	{
		m_timeSinceLastFootstep = 0.f;
	}
	return playSound;
}

#endif
