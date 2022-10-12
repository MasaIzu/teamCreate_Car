#include "wing.h"
#include <cassert>
#include "Affin.h"

void Wing::Initialize(Model* model) {
	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 6,6,6 };

	//フラグ初期化
	make = false;

	//時間初期化
	drawTime = 0;

	//デバックテキスト初期化
	debugText_ = DebugText::GetInstance();
}

void Wing::Update(Vector3 player) {
	worldTransform_.translation_ = player;

	//表示時間カウント
	if (drawTime > 0) {
		drawTime--;
	}
	else {
		make = false;
		drawTime = 0;
	}

	debugText_->SetPos(50, 100);
	debugText_->Printf("drawTime : %d", drawTime);

	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Wing::Draw(ViewProjection viewProjection) {
	//3Dモデルを描画
	if (make == true) {
		model_->Draw(worldTransform_, viewProjection);
	}
}

void Wing::Distance() {
	make = true;
	drawTime = 1;
}