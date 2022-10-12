#include "Load.h"
#include <cassert>
#include "Affin.h"

void Load::Initialize(Model* model) {
	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//初期座標をセット
	for (int i = 0; i < 15; i++) {
		float z = i * 39;
		worldTransform_[i].translation_ = Vector3{ 0,-6,z + 720 };

		//ワールド変換の初期化
		worldTransform_[i].Initialize();

		worldTransform_[i].scale_ = Vector3{ 10,10,10 };
	}

	speed_ = 3;
}

void Load::Update(float speed) {
	for (int i = 0; i < 15; i++) {
		worldTransform_[i].translation_.z -= speed;

		if (worldTransform_[i].translation_.z < -90) {
			worldTransform_[i].translation_.z = 720;
		}

		//行列更新
		AffinTrans::affin(worldTransform_[i]);
		worldTransform_[i].TransferMatrix();
	}
}

void Load::Draw(ViewProjection viewProjection) {
	//3Dモデルを描画
	for (int i = 0; i < 15; i++) {
		model_->Draw(worldTransform_[i], viewProjection);
	}
}