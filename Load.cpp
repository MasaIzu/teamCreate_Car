#include "Load.h"
#include <cassert>
#include "Affin.h"

void Load::Initialize(Model* model) {
	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//初期座標をセット
	for (int i = 0; i < 20; i++) {
		float z = i * 39 - 117;
		worldTransform_[i].translation_ = Vector3{ 0,-6,z };

		//ワールド変換の初期化
		worldTransform_[i].Initialize();

		worldTransform_[i].scale_ = Vector3{ 10,10,10 };
	}

	speed_ = 3;
}


void Load::Update(float speed) {
	for (int i = 0; i < 20; i++) {
		worldTransform_[i].translation_.z -= speed;

		if (worldTransform_[i].translation_.z < -117) {
			worldTransform_[0].translation_.z = worldTransform_[19].translation_.z + 32;
			if (i != 0) {
				worldTransform_[i].translation_.z = worldTransform_[i - 1].translation_.z + 39;
			}
		}

		//行列更新
		AffinTrans::affin(worldTransform_[i]);
		worldTransform_[i].TransferMatrix();
	}
}

void Load::Draw(ViewProjection viewProjection) {
	//3Dモデルを描画
	for (int i = 0; i < 20; i++) {
		model_->Draw(worldTransform_[i], viewProjection);
	}
}