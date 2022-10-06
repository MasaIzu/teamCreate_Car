#include"Matrix4.h"

// �Q�����Z�q�@*�@�̃I�[�o�[���[�h�֐��i�s��ƍs��̐ρj
Matrix4 Matrix4::operator*(const Matrix4& m1)
{
	return *this *= m1;
}

// �Q�����Z�q�@*�@�̃I�[�o�[���[�h�֐��i�x�N�g���ƍs��̐ρj
Vector3 operator*(const Vector3& v, const Matrix4& m)
{
	float W = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	Vector3 result
	{
		(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / W,
		(v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / W,
		(v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / W
	};
	return result;
}