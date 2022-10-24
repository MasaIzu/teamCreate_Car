#pragma once
#include "Model.h"
#include "WorldTransform.h"
///<summary>
///���H
/// </summary>
class BackGround {
public:
	///<summary>
	///������
	/// </summary>
	void Initialize(Model* model);

	///<summary>
	///�X�V
	/// </summary>
	void Update(float speed);

	///<summary>
	///�`��
	/// </summary>
	void Draw(ViewProjection viewProjection);

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_[2];
	//���f��
	Model* model_;

	float speed_;
};