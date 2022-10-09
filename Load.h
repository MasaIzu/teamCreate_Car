#pragma once
#include "Model.h"
#include "WorldTransform.h"
///<summary>
///道路
/// </summary>
class Load {
public:
	///<summary>
	///初期化
	/// </summary>
	void Initialize(Model* model);

	///<summary>
	///更新
	/// </summary>
	void Update(float speed);

	///<summary>
	///描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

private:
	//ワールド変換データ
	WorldTransform worldTransform_[20];
	//モデル
	Model* model_;

	float speed_;
};