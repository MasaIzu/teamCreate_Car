#include "Load.h"
#include <cassert>
#include "MatSet.h"

void Load::Initialize(Model* model) {
	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//初期座標をセット
	for (int i = 0; i < 12; i++) {
		float z = i * 39;
		worldTransform_[i].translation_ = Vector3{0,-50,z + 390};

		//ワールド変換の初期化
		worldTransform_[i].Initialize();

		worldTransform_[i].scale_ = Vector3{10,10,10};
	}

	speed = 3;
}

void Load::Update() {
	//更新用の変数
	MatSet2 matSet;

	for (int i = 0; i < 12; i++) {
		worldTransform_[i].translation_.z -= speed;

		if (worldTransform_[i].translation_.z < -90) {
			worldTransform_[i].translation_.z = 370;
		}

		//ワールドトランスフォームの更新
		matSet.MatIdentity(worldTransform_[i]);
		worldTransform_[i].TransferMatrix();
	}
}

void Load::Draw(ViewProjection viewProjection) {
	//3Dモデルを描画
	for (int i = 0; i < 12; i++) {
		model_->Draw(worldTransform_[i], viewProjection);
	}
}