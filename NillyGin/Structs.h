#pragma once

struct Colour
{
	struct Aos
	{
		Colour::Aos(float r, float g, float b, float a)
			:r(r) ,g(g) ,b(b) ,a(a)
		{}
		Colour::Aos() = default;

		float r, g, b, a;
	};
	struct Soa
	{
		float *r, *g, *b, *a;
	};
};

struct Float2
{
	struct Aos
	{
		Float2::Aos(float x, float y) : x(x), y(y) {};
		Float2::Aos(const Float2::Aos& other) : x(other.x), y(other.y) {};
		Float2::Aos() = default;

		float x, y;
	};
	struct Soa
	{
		float *x, *y;
	};
};

struct Float3
{
	struct Aos
	{
		Float3::Aos(float x, float y, float z) : x(x), y(y), z(z) {};
		Float3::Aos(const Float3::Aos& other) : x(other.x), y(other.y), z(other.z) {};
		Float3::Aos() = default;

		float x, y, z;
	};
	struct Soa
	{
		float *x, *y, *z;
	};
};