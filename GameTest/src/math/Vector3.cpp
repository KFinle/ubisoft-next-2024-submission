#include "stdafx.h"
#include "Vector3.h"
#include "MathUtility.h"
#include "Mathf.h"
#include "iomanip"
#include "sstream"

Vector3::Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
{
}


Vector3::~Vector3()
{
}


Vector3::Vector3(const Vector3& rhs)
{
	Set(rhs.GetX(), rhs.GetY(), rhs.GetZ());
}


Vector3 Vector3::operator+(const Vector3& rhs) const
{
	Vector3 vector;
	vector.Set(GetX() + rhs.GetX(), GetY() + rhs.GetY(), GetZ() + rhs.GetZ());
	return vector;
}


Vector3 Vector3::operator-(const Vector3& rhs) const
{
	Vector3 vector;
	vector.Set(GetX() - rhs.GetX(), GetY() - rhs.GetY(), GetZ() - rhs.GetZ());
	return vector;
}


Vector3 Vector3::operator*(const Vector3& rhs) const
{
	Vector3 vector;
	vector.Set(GetX() * rhs.GetX(), GetY() * rhs.GetY(), GetZ() * rhs.GetZ());
	return vector;
}

Vector3 Vector3::operator*(float scale) const
{
	Vector3 vector;
	vector.Set(GetX() * scale, GetY() * scale, GetZ() * scale);
	return vector;
}


Vector3 Vector3::operator/(const Vector3& rhs) const
{
	Vector3 vector;
	vector.Set(GetX() / rhs.GetX(), GetY() / rhs.GetY(), GetZ() / rhs.GetZ());
	return vector;
}


Vector3 Vector3::operator/(float scale) const
{
	return Vector3(GetX() / scale, GetY() / scale, GetZ() / scale);
}


Vector3& Vector3::operator=(const Vector3& rhs)
{
	Set(rhs.GetX(), rhs.GetY(), rhs.GetZ());
	return *this;
}


Vector3& Vector3::operator+=(const Vector3& rhs)
{
	Set(GetX() + rhs.GetX(), GetY() + rhs.GetY(), GetZ() + rhs.GetZ());
	return *this;
}


Vector3& Vector3::operator-=(const Vector3& rhs)
{
	Set(GetX() - rhs.GetX(), GetY() - rhs.GetY(), GetZ() - rhs.GetZ());
	return *this;
}


Vector3& Vector3::operator*=(const Vector3& rhs)
{
	Set(GetX() * rhs.GetX(), GetY() * rhs.GetY(), GetZ() * rhs.GetZ());
	return *this;
}

Vector3& Vector3::operator*=(float scale)
{
	Set(GetX() * scale, GetY() * scale, GetZ() * scale);
	return *this;
}


Vector3& Vector3::operator/=(const Vector3& rhs)
{
	Set(GetX() / rhs.GetX(), GetY() / rhs.GetY(), GetZ() / rhs.GetZ());
	return *this;
}

Vector3& Vector3::operator/=(float scale)
{
	Set(GetX() / scale, GetY() / scale, GetZ() / scale);
	return *this;
}


bool Vector3::operator==(const Vector3& rhs) const
{
	return ((GetX() == rhs.GetX()) && (GetY() == rhs.GetY()) && (GetZ() == rhs.GetZ()));
}


bool Vector3::operator!=(const Vector3& rhs) const
{
	return ((GetX() != rhs.GetX()) && (GetY() != rhs.GetY()) && (GetZ() != rhs.GetZ()));
}


bool Vector3::operator>(const Vector3& rhs) const
{
	return ((GetX() > rhs.GetX()) && (GetY() > rhs.GetY()) && (GetZ() >= rhs.GetZ()));
}


bool Vector3::operator<(const Vector3& rhs) const
{
	return ((GetX() < rhs.GetX()) && (GetY() < rhs.GetY()) && (GetZ() <= rhs.GetZ()));
}


bool Vector3::operator>=(const Vector3& rhs) const
{
	return ((GetX() >= rhs.GetX()) && (GetY() >= rhs.GetY()) && (GetZ() >= rhs.GetZ()));
}


bool Vector3::operator<=(const Vector3& rhs) const
{
	return ((GetX() <= rhs.GetX()) && (GetY() <= rhs.GetY()) && (GetZ() <= rhs.GetZ()));
}



Vector3& Vector3::operator++()
{
	Set(GetX() + 1, GetY() + 1, GetZ() + 1);
	return *this;
}


Vector3 Vector3::operator++(int)
{
	Vector3 vector = *this;
	++*this;
	return vector;
}


Vector3& Vector3::operator--()
{
	Set(GetX() - 1, GetY() - 1, GetZ() - 1);
	return *this;
}


Vector3 Vector3::operator--(int)
{
	Vector3 vector = *this;
	--*this;
	return vector;
}


float Vector3::GetX() const
{
	return m_x;
}


float Vector3::GetY() const
{
	return m_y;
}


float Vector3::GetZ() const
{
	return m_z;
}


void Vector3::SetX(float x)
{
	m_x = x;
}


void Vector3::SetY(float y)
{
	m_y = y;
}


void Vector3::SetZ(float z)
{
	m_z = z;
}


void Vector3::Set(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}


float Vector3::GetMagnitude() const
{
	return Mathf::Sqrt(GetX() * GetX() +
		GetY() * GetY() +
		GetZ() * GetZ());
}


float Vector3::GetSqrMagnitude() const
{
	return GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ();
}


void Vector3::SetScale(const Vector3& scale)
{
	*this *= scale;
}


Vector3 Vector3::GetNormalized() const
{
	Vector3 vector = Vector3(GetX(), GetY(), GetZ());
	vector.Normalize();
	return vector;
}


void Vector3::Normalize()
{
	const auto magnitude = GetMagnitude();
	if (static_cast<double>(magnitude) > 9.99999974737875E-06)
	{
		Set(GetX() / magnitude, GetY() / magnitude, GetZ() / magnitude);
	}
	else
	{
		*this = Vector3::Zero();
	}
}


Vector3 Vector3::Zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}


Vector3 Vector3::One()
{
	return Vector3(1.0, 1.0, 1.0);
}


Vector3 Vector3::Up()
{
	return Vector3(0.0, 1.0, 0.0);
}


Vector3 Vector3::Down()
{
	return Vector3(0.0, -1.0, 0.0);
}


Vector3 Vector3::Right()
{
	return Vector3(1.0, 0.0, 0.0);
}


Vector3 Vector3::Left()
{
	return Vector3(-1.0, 0.0, 0.0);
}





Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
	t = Mathf::ClampFloat(t);
	return Vector3(a.GetX() + (b.GetX() - a.GetX()) * t, a.GetY() + (b.GetY() - a.GetY()) * t, a.GetZ() + (b.GetZ() - a.GetZ()));
}


Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t)
{
	return Vector3(a.GetX() + (b.GetX() - a.GetX()) * t, a.GetY() + (b.GetY() - a.GetY()) * t, a.GetZ() + (b.GetZ() - a.GetZ()));
}


Vector3 Vector3::MoveTowards(const Vector3& current, const Vector3& target, float max_distance_delta)
{
	const Vector3 vector = target - current;
	const auto magnitude = vector.GetMagnitude();
	if (static_cast<double>(magnitude) <= static_cast<double>(max_distance_delta) || static_cast<double>(magnitude) == 0.0)
	{
		return target;
	}
	return current + vector / magnitude * max_distance_delta;
}


Vector3 Vector3::Scale(const Vector3& a, const Vector3& b)
{
	return Vector3(a.GetX() * b.GetX(), a.GetY() * b.GetY(), a.GetZ() * b.GetZ());
}


Vector3 Vector3::Reflect(const Vector3& in_direction, const Vector3& in_normal)
{
	return in_normal * (-2.0f * Vector3::Dot(in_normal, in_direction)) + in_direction;
}


Vector3 Vector3::Perpendicular(const Vector3& in_direction)
{
	return Vector3(-in_direction.GetY(), in_direction.GetX(), in_direction.GetZ());
}


float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.GetX() * rhs.GetX() + lhs.GetY() * rhs.GetY() + lhs.GetZ() * rhs.GetZ();
}

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
	float x, y, z;
	x = lhs.GetY() * rhs.GetZ() - lhs.GetZ() * rhs.GetY();
	y = lhs.GetZ() * rhs.GetX() - lhs.GetX() * rhs.GetZ();
	z = lhs.GetX() * rhs.GetY() - lhs.GetY() * rhs.GetX();

	return Vector3(x, y, z);

}


float Vector3::Angle(const Vector3& from, const Vector3& to)
{
	const auto denominator = Mathf::Sqrt(from.GetSqrMagnitude() * to.GetSqrMagnitude());
	if (denominator < Mathf::EpsilonNormalSqrt)
	{
		return 0.0F;
	}

	const auto dot = Mathf::Clamp(Vector3::Dot(from, to) / denominator, -1.0F, 1.0F);
	return Mathf::Acos(dot) * Mathf::Rad2Deg;
}

float Vector3::SignedAngle(const Vector3& from, const Vector3& to)
{
	const auto unsigned_angle = Vector3::Angle(from, to);
	const auto sign = Mathf::Sign(from.GetX() * to.GetY() - from.GetY() * to.GetX());
	return unsigned_angle * sign;
}


float Vector3::Distance(const Vector3& a, const Vector3& b)
{
	const auto delta_x = static_cast<double>(b.GetX()) - static_cast<double>(a.GetX());
	const auto delta_y = static_cast<double>(b.GetY()) - static_cast<double>(a.GetY());
	const auto delta_z = static_cast<double>(b.GetZ()) - static_cast<double>(a.GetZ());
	return Mathf::Sqrt(static_cast<float>(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z));
}


Vector3 Vector3::ClampMagnitude(const Vector3& vector, float max_length)
{
	if (static_cast<double>(vector.GetSqrMagnitude()) > static_cast<double>(max_length) * static_cast<double>(max_length))
	{
		return vector.GetNormalized() * max_length;
	}
	return vector;
}


float Vector3::SqrMagnitude(const Vector3& a)
{
	return a.GetX() * a.GetX() + a.GetY() * a.GetY() + a.GetZ() * a.GetZ();
}


Vector3 Vector3::Min(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(Mathf::Min(lhs.GetX(), rhs.GetX()), Mathf::Min(lhs.GetY(), rhs.GetY()), Mathf::Min(lhs.GetZ(), rhs.GetZ()));
}


Vector3 Vector3::Max(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(Mathf::Max(lhs.GetX(), rhs.GetX()), Mathf::Max(lhs.GetY(), rhs.GetY()), Mathf::Max(lhs.GetZ(), rhs.GetZ()));
}

Vector3 Vector3::ScaledToScreen(const Vector3& a)
{
	Vector3 scaled;
	scaled.SetX(MathUtility::ScaleToVirtualWidth(a.GetX()));
	scaled.SetY(MathUtility::ScaleToVirtualHeight(a.GetY()));
	scaled.SetZ(a.GetZ());
	return scaled;
}


std::string Vector3::ToString(const int precision) const
{
	std::stringstream out;

	out << std::fixed << std::setprecision(precision);
	out << "(" << m_x << ", " << m_y << ", " << m_z << ")";
	return out.str();
}

