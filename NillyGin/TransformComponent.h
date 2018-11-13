#pragma once
#include "DataBlockSoa.h"
#include "Structs.h"

struct TransformComponent
{
	struct Aos
	{
		Float3::Aos pos;
	};
	struct Soa
	{
		Float3::Soa *pos;
	};
};

DEFINE_SOA_CLASS(TransformComponent, 3, 1)
DEFINE_SOA_STRUCT(TransformComponent, 0, Float3::Soa, pos)
DEFINE_SOA_TYPE_STRUCT(TransformComponent, 0, Float3, float, pos, x)
DEFINE_SOA_TYPE_STRUCT(TransformComponent, 1, Float3, float, pos, y)
DEFINE_SOA_TYPE_STRUCT(TransformComponent, 2, Float3, float, pos, z)