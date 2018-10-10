#pragma once
#include "DataBlockSoa.h"

struct TransformComponent
{
	struct Aos
	{
		float xPos, yPos;
	};

	struct Soa
	{
		float *xPos, *yPos;
	};
};

DEFINE_SOA_CLASS(TransformComponent,2)
DEFINE_SOA_TYPE(TransformComponent,0,float,xPos)
DEFINE_SOA_TYPE(TransformComponent,1,float,yPos)
