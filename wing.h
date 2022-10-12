#pragma once

#include"Model.h"
#include"WorldTransform.h"
#include"DebugText.h"

class Wing {
public:
	//初期化
	void Initialize(Model* model);

	//更新
	void Update(Vector3 player);

	//描画
	void Draw(ViewProjection viewProjection);

	//判定
	void Distance();
private:
	//ワールド座標
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
	//表示フラグ
	bool make;
	//描画時間
	int drawTime;
};
