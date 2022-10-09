#pragma once
#include "Model.h"
#include "WorldTransform.h"
///<summary>
///���H
/// </summary>
class Load {
public:
	///<summary>
	///������
	/// </summary>
	void Initialize(Model* model);

	///<summary>
	///�X�V
	/// </summary>
	void Update();

	///<summary>
	///�`��
	/// </summary>
	void Draw(ViewProjection viewProjection);

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_[7];
	//���f��
	Model* model_;

	int speed;
};