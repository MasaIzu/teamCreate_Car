#include "Collision.h"

bool collision::boxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth, Vector3 enemyWidth)
{

	//�v���C���[
	float pXMin = player.x - playerWidth.x;

	float pXMax = player.x + playerWidth.x;

	float pYMin = player.y - playerWidth.y;

	float pYMax = player.y + playerWidth.y;

	float pZMin = player.z - playerWidth.z;

	float pZMax = player.z + playerWidth.z;

	//�G
	//����
	float eXMin = enemy.x - enemyWidth.x;

	float eXMax = enemy.x + enemyWidth.x;

	float eYMin = enemy.y - enemyWidth.y;

	float eYMax = enemy.y + enemyWidth.y;

	float eZMin = enemy.z - enemyWidth.z;

	float eZMax = enemy.z + enemyWidth.z;

	if ((pXMin <= eXMax && pXMax >= eXMin) && (pYMin <= eYMax && pYMax >= eYMin) && (pZMin <= eZMax && pZMax >= eZMin)) {
		return true;
	}
	return false;
}

bool collision::boxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth, Vector3 enemyWidth, bool flag)
{

	///�v���C���[
	float pXMin = player.x - playerWidth.x;

	float pXMax = player.x + playerWidth.x;

	float pYMin = player.y - playerWidth.y;

	float pYMax = player.y + playerWidth.y;

	float pZMin = 0;

	float pZMax = player.z + playerWidth.z;

	//�G
	//����
	float eXMin = enemy.x - enemyWidth.x;

	float eXMax = enemy.x + enemyWidth.x;

	float eYMin = enemy.y - enemyWidth.y;

	float eYMax = enemy.y + enemyWidth.y;

	float eZMin = enemy.z - enemyWidth.z;

	float eZMax = enemy.z + enemyWidth.z;

	if ((pXMin <= eXMax && pXMax >= eXMin) && (pYMin <= eYMax && pYMax >= eYMin) && (pZMin <= eZMax && pZMax >= eZMin)) {
		return true;
	}
	return false;
}

void collision::Contact(int playerMove, Vector3 player, WorldTransform enemy,Vector3 enemyRotationMove, Vector3 enemyMove)
{
	if (playerMove == 1) {
		enemy.rotation_ += enemyRotationMove;
		enemy.translation_ += enemyMove;
	}
	else if (playerMove == 0) {
		enemy.translation_ += enemyMove;
	}
	else if (playerMove == -1) {
		enemy.rotation_ += enemyRotationMove;
		enemy.translation_ -= enemyMove;
	}
}
