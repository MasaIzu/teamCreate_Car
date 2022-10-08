#include "Collision.h"

bool collision::boxCollision(Vector3 player, Vector3 enemy, float playerWidthX, float playerWidthZ, float playerHight, float enemyWidthX, float enemyWidthZ, float enemyHight)
{
	
	//ÉvÉåÉCÉÑÅ[
	float pXMin = player.x - playerWidthX / 2;

	float pXMax = player.x + playerWidthX / 2;
	
	float pYMin = player.y - playerHight / 2;

	float pYMax = player.y + playerHight / 2;

	float pZMin = player.z - playerWidthZ / 2;

	float pZMax = player.z + playerWidthZ / 2;
	
	//ìG
	//ïΩñ 
	float eXMin = enemy.x - enemyWidthX / 2;

	float eXMax = enemy.x + enemyWidthX / 2;

	float eYMin = enemy.y - enemyHight / 2;

	float eYMax = enemy.y + enemyHight / 2;

	float eZMin = enemy.z - enemyWidthZ / 2;

	float eZMax = enemy.z + enemyWidthZ / 2;

	if ((pXMin <= eXMax && pXMax >= eXMin) && (pYMin <= eYMax && pYMax >= eYMin) && (pZMin <= eZMax && pZMax >= eZMin)) {
		return true;
	}
	return false;
}
