#include "EnemyPop.h"
#include <stdlib.h>
void EnemyPop::Update()
{
	popTimer++;

	// タイマーが間隔時間になったらランダムに生成と車種を抽選して、設定する
	if (popTimer >= popInterval){

		carModelnum_ = rand() % 3 + 1;
		carPattern_= rand() % 3 + 1;

		if (carModelnum_ == 1)
		{
			carModel_ = CarModel::truck;
		}
		else if (carModelnum_ == 2) {
			carModel_ = CarModel::prius;
		}
		else if (carModelnum_ == 3) {
			carModel_ = CarModel::ferrari;
		}

		
	}
}

void EnemyPop::Draw()
{

}
