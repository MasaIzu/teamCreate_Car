#include "Collision.h"

bool collision::boxCollision(Vector3 player, Vector3 enemy, float playerWidthX, float playerWidthZ, float playerHight, float enemyWidthX, float enemyWidthZ, float enemyHight)
{
	
	//ÉvÉåÉCÉÑÅ[
	float pXMin = player.x - playerWidthX;

	float pXMax = player.x + playerWidthX;
	
	float pYMin = player.y - playerHight;

	float pYMax = player.y + playerHight;

	float pZMin = player.z - playerWidthZ;

	float pZMax = player.z + playerWidthZ;
	
	//ìG
	//ïΩñ 
	float eXMin = enemy.x - enemyWidthX;

	float eXMax = enemy.x + enemyWidthX;

	float eYMin = enemy.y - enemyHight;

	float eYMax = enemy.y + enemyHight;

	float eZMin = enemy.z - enemyWidthZ;

	float eZMax = enemy.z + enemyWidthZ;

	if ((pXMin <= eXMax && pXMax >= eXMin) && (pYMin <= eYMax && pYMax >= eYMin) && (pZMin <= eZMax && pZMax >= eZMin)) {
		return true;
	}
	return false;
}

void collision::Contact(int playerMove, Vector3 player, WorldTransform enemy)
{
}
