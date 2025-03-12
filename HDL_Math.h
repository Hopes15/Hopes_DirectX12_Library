#pragma once
#include <iostream>
#include <cmath>

class Vector2
{
private:
	float mX;
	float mY;

public:
	//�R���X�g���N�^
	//----------------------------------------------------------------------------------------
	Vector2();
	Vector2(float x, float y);

	//Setter
	//----------------------------------------------------------------------------------------
	/// <summary>
	/// x�̒l���Z�b�g����
	/// </summary>
	/// <param name="x">	�Z�b�g����X���W�̒l	</param>
	inline void SetX(float x) { mX = x; }

	/// <summary>
	/// y�̒l���Z�b�g����
	/// </summary>
	/// <param name="y">	�Z�b�g����Y���W�̒l	</param>
	inline void SetY(float y) { mY = y; }

	/// <summary>
	/// x, y�̒l���Z�b�g����
	/// </summary>
	/// <param name="x">	�Z�b�g����X���W�̒l	</param>
	/// <param name="y">	�Z�b�g����Y���W�̒l	</param>
	inline void SetValue(float x, float y) { mX = x; mY = y; }

	//Getter
	//----------------------------------------------------------------------------------------
	/// <summary>
	/// x�̒l���擾
	/// </summary>
	/// <returns>	x���W�̒l	</returns>
	inline float GetX() const { return mX; }

	/// <summary>
	/// y�̒l���擾
	/// </summary>
	/// <returns>	y���W�̒l	</returns>
	inline float GetY() const { return mY; }

	/// <summary>
	/// ���g��Ԃ�
	/// </summary>
	/// <returns>	Vector2		</returns>
	inline Vector2 GetValue() const { return *this; }

	//���Z�q�̃I�[�o�[���[�h
	//----------------------------------------------------------------------------------------
	//�����Z
	friend Vector2 operator+(const Vector2& a, const Vector2& b);

	//�����Z
	friend Vector2 operator-(const Vector2& a, const Vector2& b);

	//�|���Z
	friend Vector2 operator*(float L, const Vector2& R);
	friend Vector2 operator*(const Vector2& L, float R);

	//���ρi�EDot�j
	inline float Dot(const Vector2& b) const { return mX * b.mX + mY * b.mY; }

	//�O�� (�~Cross)
	//friend float operator�~(const Vector2& a, const Vector2& b);

	//����Z
	friend Vector2 operator/(const Vector2& L, float R);

	//Other
	//----------------------------------------------------------------------------------------
	/// <summary>
	/// ���W��\������
	/// </summary>
	inline void OutputPosition() const { std::cout << "(" << mX << ", " << mY << ")" << std::endl; }

	/// <summary>
	/// ��Βl
	/// </summary>
	/// <returns>	��Βl	</returns>
	inline float Abs() const { return sqrt((mX * mX) + (mY * mY)); }

	/// <summary>
	/// �P�ʃx�N�g��
	/// </summary>
	/// <returns>	Vector2	</returns>
	inline Vector2 Normal() const { return *this / Abs(); }

	/// <summary>
	/// ���g�Ƒ��x�N�g�����Ȃ�Cos�Ƃ�Ԃ�
	/// </summary>
	/// <param name="other">	���x�N�g��	</param>
	/// <returns>				Cos��		</returns>
	//inline float GetCos��(const Vector2& other) const { return  Dot(other) / (this->Abs() * other.Abs()); }
};

//class Vector3
//{
//private:
//	float x;
//	float y;
//	float z;
//};

