#include "string"
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////
// When I started preparing for this project, I was unsure if the game would be in 3D or 2D //
// so working with a Vector3 class instead of Vector2 made the most sense for me.			//
//////////////////////////////////////////////////////////////////////////////////////////////
// This class includes several functions that did not end up getting used. However, I felt  //
// it was still worth including in my submission, rather than trying to find everything		//
// that did not get used. In any case, I'll be happy to have this library created for my	//
// C++ project																				//
//////////////////////////////////////////////////////////////////////////////////////////////


class Vector3
{
public:
	// constructor
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Vector3();

	// copy constructor
	Vector3(const Vector3& rhs);

	// arithmetic operators
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator-(const Vector3& rhs) const;
	Vector3 operator*(const Vector3& rhs) const;
	Vector3 operator*(float scale) const;
	Vector3 operator/(const Vector3& rhs) const;
	Vector3 operator/(float scale) const;
	Vector3& operator=(const Vector3& rhs);

	// shortcut operators
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(const Vector3& rhs);
	Vector3& operator*=(float scale);
	Vector3& operator/=(const Vector3& rhs);
	Vector3& operator/=(float scale);

	// comparison operators
	bool operator==(const Vector3& rhs) const;
	bool operator!=(const Vector3& rhs) const;
	bool operator>(const Vector3& rhs) const;
	bool operator<(const Vector3& rhs) const;
	bool operator>=(const Vector3& rhs) const;
	bool operator<=(const Vector3& rhs) const;

	// increment / decrement operators
	Vector3& operator++();
	Vector3 operator++(int);
	Vector3& operator--();
	Vector3 operator--(int);

	// Getters and Setters
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void Set(float x, float y, float z);

	// utility functions
	float GetMagnitude() const;
	float GetSqrMagnitude() const;
	void SetScale(const Vector3& scale);
	Vector3 GetNormalized() const;
	void Normalize();

	// static functions
	static Vector3 Zero();
	static Vector3 One();
	static Vector3 Up();
	static Vector3 Down();
	static Vector3 Right();
	static Vector3 Left();
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
	static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float max_distance_delta);
	static Vector3 Scale(const Vector3& a, const Vector3& b);
	static Vector3 Reflect(const Vector3& in_direction, const Vector3& in_normal);
	static Vector3 Perpendicular(const Vector3& in_direction);
	static float Dot(const Vector3& lhs, const Vector3& rhs);
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
	static float Angle(const Vector3& from, const Vector3& to);
	static float SignedAngle(const Vector3& from, const Vector3& to);
	static float Distance(const Vector3& a, const Vector3& b);
	static Vector3 ClampMagnitude(const Vector3& vector, float max_length);
	static float SqrMagnitude(const Vector3& a);
	static Vector3 Min(const Vector3& lhs, const Vector3& rhs);
	static Vector3 Max(const Vector3& lhs, const Vector3& rhs);
	static Vector3 ScaledToScreen(const Vector3& a);

	// to string
	std::string ToString(int precision = 2) const;

private:
	float m_x;
	float m_y;
	float m_z;
	//float m_w = 0;
};
