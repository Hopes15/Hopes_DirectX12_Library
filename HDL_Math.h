#pragma once
#include <iostream>
#include <cmath>

class Vector2
{
private:
	float mX;
	float mY;

public:
	//コンストラクタ
	//----------------------------------------------------------------------------------------
	Vector2();
	Vector2(float x, float y);

	//Setter
	//----------------------------------------------------------------------------------------
	/// <summary>
	/// xの値をセットする
	/// </summary>
	/// <param name="x">	セットするX座標の値	</param>
	inline void SetX(float x) { mX = x; }

	/// <summary>
	/// yの値をセットする
	/// </summary>
	/// <param name="y">	セットするY座標の値	</param>
	inline void SetY(float y) { mY = y; }

	/// <summary>
	/// x, yの値をセットする
	/// </summary>
	/// <param name="x">	セットするX座標の値	</param>
	/// <param name="y">	セットするY座標の値	</param>
	inline void SetValue(float x, float y) { mX = x; mY = y; }

	//Getter
	//----------------------------------------------------------------------------------------
	/// <summary>
	/// xの値を取得
	/// </summary>
	/// <returns>	x座標の値	</returns>
	inline float GetX() const { return mX; }

	/// <summary>
	/// yの値を取得
	/// </summary>
	/// <returns>	y座標の値	</returns>
	inline float GetY() const { return mY; }

	/// <summary>
	/// 自身を返す
	/// </summary>
	/// <returns>	Vector2		</returns>
	inline Vector2 GetValue() const { return *this; }

	//演算子のオーバーロード
	//----------------------------------------------------------------------------------------
	//足し算
	friend Vector2 operator+(const Vector2& a, const Vector2& b);

	//引き算
	friend Vector2 operator-(const Vector2& a, const Vector2& b);

	//掛け算
	friend Vector2 operator*(float L, const Vector2& R);
	friend Vector2 operator*(const Vector2& L, float R);

	//内積（・Dot）
	inline float Dot(const Vector2& b) const { return mX * b.mX + mY * b.mY; }

	//外積 (×Cross)
	//friend float operator×(const Vector2& a, const Vector2& b);

	//割り算
	friend Vector2 operator/(const Vector2& L, float R);

	//Other
	//----------------------------------------------------------------------------------------
	/// <summary>
	/// 座標を表示する
	/// </summary>
	inline void OutputPosition() const { std::cout << "(" << mX << ", " << mY << ")" << std::endl; }

	/// <summary>
	/// 絶対値
	/// </summary>
	/// <returns>	絶対値	</returns>
	inline float Abs() const { return sqrt((mX * mX) + (mY * mY)); }

	/// <summary>
	/// 単位ベクトル
	/// </summary>
	/// <returns>	Vector2	</returns>
	inline Vector2 Normal() const { return *this / Abs(); }

	/// <summary>
	/// 自身と他ベクトルがなすCosθを返す
	/// </summary>
	/// <param name="other">	他ベクトル	</param>
	/// <returns>				Cosθ		</returns>
	//inline float GetCosθ(const Vector2& other) const { return  Dot(other) / (this->Abs() * other.Abs()); }
};

//class Vector3
//{
//private:
//	float x;
//	float y;
//	float z;
//};

