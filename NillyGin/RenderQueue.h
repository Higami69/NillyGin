#pragma once
#include "Structs.h"
#include "DataBlockSoa.h"
#include <SDL_opengl.h>

class RenderBackEnd;

#pragma region RenderTasks
#pragma region RenderPointTask
struct RenderPointTask
{
	struct Aos
	{
		Float3::Aos point;
		Colour::Aos colour;
		float pointSize;
	};
	struct Soa
	{
		Float3::Soa* point;
		Colour::Soa* colour;
		float* pointSize;
	};
};

DEFINE_SOA_CLASS(RenderPointTask, 8, 2)
DEFINE_SOA_STRUCT(RenderPointTask,0,Float3::Soa, point)
DEFINE_SOA_STRUCT(RenderPointTask,1,Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderPointTask, 0, Float3, float, point, x)
DEFINE_SOA_TYPE_STRUCT(RenderPointTask, 1, Float3, float, point, y)
DEFINE_SOA_TYPE_STRUCT(RenderPointTask, 2, Float3, float, point, z)
DEFINE_SOA_TYPE_STRUCT(RenderPointTask, 3, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderPointTask, 4, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderPointTask, 5, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderPointTask, 6, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderPointTask, 7, float, pointSize)
#pragma endregion 
#pragma region RenderLineTask
struct RenderLineTask
{
	struct Aos
	{
		Float2::Aos point1, point2;
		Colour::Aos colour;
		float depth, lineWidth;
	};
	struct Soa
	{
		Float2::Soa *point1, *point2;
		Colour::Soa *colour;
		float *depth, *lineWidth;
	};
};

DEFINE_SOA_CLASS(RenderLineTask, 10, 3)
DEFINE_SOA_STRUCT(RenderLineTask, 0, Float2::Soa, point1)
DEFINE_SOA_STRUCT(RenderLineTask, 1, Float2::Soa, point2)
DEFINE_SOA_STRUCT(RenderLineTask, 2, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderLineTask, 0, Float2, float, point1, x)
DEFINE_SOA_TYPE_STRUCT(RenderLineTask, 1, Float2, float, point1, y)
DEFINE_SOA_TYPE_STRUCT(RenderLineTask, 2, Float2, float, point2, x)
DEFINE_SOA_TYPE_STRUCT(RenderLineTask, 3, Float2, float, point2, y)
DEFINE_SOA_TYPE_STRUCT(RenderLineTask, 4, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderLineTask, 5, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderLineTask, 6, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderLineTask, 7, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderLineTask, 8, float, depth)
DEFINE_SOA_TYPE(RenderLineTask, 9, float, lineWidth)
#pragma endregion 
#pragma region RenderFilledTriangleTask
struct RenderFilledTriangleTask
{
	struct Aos
	{
		Float2::Aos point1, point2, point3;
		Colour::Aos colour;
		float depth;
	};
	struct Soa
	{
		Float2::Soa *point1, *point2, *point3;
		Colour::Soa *colour;
		float *depth;
	};
};

DEFINE_SOA_CLASS(RenderFilledTriangleTask, 11, 4)
DEFINE_SOA_STRUCT(RenderFilledTriangleTask, 0, Float2::Soa, point1)
DEFINE_SOA_STRUCT(RenderFilledTriangleTask, 1, Float2::Soa, point2)
DEFINE_SOA_STRUCT(RenderFilledTriangleTask, 2, Float2::Soa, point3)
DEFINE_SOA_STRUCT(RenderFilledTriangleTask, 3, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 0, Float2, float, point1, x)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 1, Float2, float, point1, y)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 2, Float2, float, point2, x)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 3, Float2, float, point2, y)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 4, Float2, float, point3, x)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 5, Float2, float, point3, y)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 6, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 7, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 8, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderFilledTriangleTask, 9, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderFilledTriangleTask, 10, float, depth)
#pragma endregion
#pragma region RenderTriangleTask
struct RenderTriangleTask
{
	struct Aos
	{
		Float2::Aos point1, point2, point3;
		Colour::Aos colour;
		float depth, lineWidth;
	};
	struct Soa
	{
		Float2::Soa *point1, *point2, *point3;
		Colour::Soa *colour;
		float *depth, *lineWidth;
	};
};

DEFINE_SOA_CLASS(RenderTriangleTask, 12, 4)
DEFINE_SOA_STRUCT(RenderTriangleTask, 0, Float2::Soa, point1)
DEFINE_SOA_STRUCT(RenderTriangleTask, 1, Float2::Soa, point2)
DEFINE_SOA_STRUCT(RenderTriangleTask, 2, Float2::Soa, point3)
DEFINE_SOA_STRUCT(RenderTriangleTask, 3, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 0, Float2, float, point1, x)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 1, Float2, float, point1, y)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 2, Float2, float, point2, x)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 3, Float2, float, point2, y)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 4, Float2, float, point3, x)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 5, Float2, float, point3, y)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 6, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 7, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 8, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleTask, 9, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderTriangleTask, 10, float, depth)
DEFINE_SOA_TYPE(RenderTriangleTask, 11, float, lineWidth)
#pragma endregion
#pragma region RenderFilledRectangleTask
struct RenderFilledRectangleTask
{
	struct Aos
	{
		Float2::Aos bottomLeft, dimensions;
		Colour::Aos colour;
		float depth;
	};
	struct Soa
	{
		Float2::Soa *bottomLeft, *dimensions;
		Colour::Soa *colour;
		float *depth;
	};
};

DEFINE_SOA_CLASS(RenderFilledRectangleTask, 9, 3)
DEFINE_SOA_STRUCT(RenderFilledRectangleTask, 0, Float2::Soa, bottomLeft)
DEFINE_SOA_STRUCT(RenderFilledRectangleTask, 1, Float2::Soa, dimensions)
DEFINE_SOA_STRUCT(RenderFilledRectangleTask, 2, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderFilledRectangleTask, 0, Float2, float, bottomLeft, x)
DEFINE_SOA_TYPE_STRUCT(RenderFilledRectangleTask, 1, Float2, float, bottomLeft, y)
DEFINE_SOA_TYPE_STRUCT(RenderFilledRectangleTask, 2, Float2, float, dimensions, x)
DEFINE_SOA_TYPE_STRUCT(RenderFilledRectangleTask, 3, Float2, float, dimensions, y)
DEFINE_SOA_TYPE_STRUCT(RenderFilledRectangleTask, 4, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderFilledRectangleTask, 5, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderFilledRectangleTask, 6, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderFilledRectangleTask, 7, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderFilledRectangleTask, 8, float, depth)
#pragma endregion
#pragma region RenderRectangleTask
struct RenderRectangleTask
{
	struct Aos
	{
		Float2::Aos bottomLeft, dimensions;
		Colour::Aos colour;
		float depth, lineWidth;
	};
	struct Soa
	{
		Float2::Soa *bottomLeft, *dimensions;
		Colour::Soa *colour;
		float *depth, *lineWidth;
	};
};

DEFINE_SOA_CLASS(RenderRectangleTask, 10, 3)
DEFINE_SOA_STRUCT(RenderRectangleTask, 0, Float2::Soa, bottomLeft)
DEFINE_SOA_STRUCT(RenderRectangleTask, 1, Float2::Soa, dimensions)
DEFINE_SOA_STRUCT(RenderRectangleTask, 2, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleTask, 0, Float2, float, bottomLeft, x)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleTask, 1, Float2, float, bottomLeft, y)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleTask, 2, Float2, float, dimensions, x)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleTask, 3, Float2, float, dimensions, y)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleTask, 4, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleTask, 5, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleTask, 6, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleTask, 7, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderRectangleTask, 8, float, depth)
DEFINE_SOA_TYPE(RenderRectangleTask, 9, float, lineWidth)
#pragma endregion
#pragma region RenderFilledEllipseTask
struct RenderFilledEllipseTask
{
	struct Aos
	{
		Float2::Aos center, dimensions;
		Colour::Aos colour;
		float depth, nrSections;
	};
	struct Soa
	{
		Float2::Soa *center, *dimensions;
		Colour::Soa *colour;
		float *depth, *nrSections;
	};
};

DEFINE_SOA_CLASS(RenderFilledEllipseTask, 10, 3)
DEFINE_SOA_STRUCT(RenderFilledEllipseTask, 0, Float2::Soa, center)
DEFINE_SOA_STRUCT(RenderFilledEllipseTask, 1, Float2::Soa, dimensions)
DEFINE_SOA_STRUCT(RenderFilledEllipseTask, 2, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderFilledEllipseTask, 0, Float2, float, center, x)
DEFINE_SOA_TYPE_STRUCT(RenderFilledEllipseTask, 1, Float2, float, center, y)
DEFINE_SOA_TYPE_STRUCT(RenderFilledEllipseTask, 2, Float2, float, dimensions, x)
DEFINE_SOA_TYPE_STRUCT(RenderFilledEllipseTask, 3, Float2, float, dimensions, y)
DEFINE_SOA_TYPE_STRUCT(RenderFilledEllipseTask, 4, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderFilledEllipseTask, 5, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderFilledEllipseTask, 6, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderFilledEllipseTask, 7, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderFilledEllipseTask, 8, float, depth)
DEFINE_SOA_TYPE(RenderFilledEllipseTask, 9, float, nrSections)
#pragma endregion
#pragma region RenderEllipseTask
struct RenderEllipseTask
{
	struct Aos
	{
		Float2::Aos center, dimensions;
		Colour::Aos colour;
		float depth, lineWidth, nrSections;
	};
	struct Soa
	{
		Float2::Soa *center, *dimensions;
		Colour::Soa *colour;
		float *depth, *lineWidth, *nrSections;
	};
};

DEFINE_SOA_CLASS(RenderEllipseTask, 11, 3)
DEFINE_SOA_STRUCT(RenderEllipseTask, 0, Float2::Soa, center)
DEFINE_SOA_STRUCT(RenderEllipseTask, 1, Float2::Soa, dimensions)
DEFINE_SOA_STRUCT(RenderEllipseTask, 2, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseTask, 0, Float2, float, center, x)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseTask, 1, Float2, float, center, y)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseTask, 2, Float2, float, dimensions, x)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseTask, 3, Float2, float, dimensions, y)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseTask, 4, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseTask, 5, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseTask, 6, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseTask, 7, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderEllipseTask, 8, float, depth)
DEFINE_SOA_TYPE(RenderEllipseTask, 9, float, lineWidth)
DEFINE_SOA_TYPE(RenderEllipseTask, 10, float, nrSections)

#pragma endregion
#pragma region RenderTextureTask
struct RenderTextureTask
{
	struct Aos
	{
		Float2::Aos botLeft, dimensions;
		float depth;
		GLuint texId;
	};
	struct Soa
	{
		Float2::Soa *botLeft, *dimensions;
		float *depth;
		GLuint *texId;
	};
};

DEFINE_SOA_CLASS(RenderTextureTask, 6, 2)
DEFINE_SOA_STRUCT(RenderTextureTask, 0, Float2::Soa, botLeft)
DEFINE_SOA_STRUCT(RenderTextureTask, 1, Float2::Soa, dimensions)
DEFINE_SOA_TYPE_STRUCT(RenderTextureTask, 0, Float2, float, botLeft, x)
DEFINE_SOA_TYPE_STRUCT(RenderTextureTask, 1, Float2, float, botLeft, y)
DEFINE_SOA_TYPE_STRUCT(RenderTextureTask, 2, Float2, float, dimensions, x)
DEFINE_SOA_TYPE_STRUCT(RenderTextureTask, 3, Float2, float, dimensions, y)
DEFINE_SOA_TYPE(RenderTextureTask, 4, float, depth)
DEFINE_SOA_TYPE(RenderTextureTask, 5, GLuint, texId)
#pragma endregion
struct RenderTaskBuffer
{
	DataBlockSoa<RenderPointTask> pointTasks;
	DataBlockSoa<RenderLineTask> lineTasks;
	DataBlockSoa<RenderFilledTriangleTask> filledTriangleTasks;
	DataBlockSoa<RenderTriangleTask> triangleTasks;
	DataBlockSoa<RenderFilledRectangleTask> filledRectangleTasks;
	DataBlockSoa<RenderRectangleTask> rectangleTasks;
	DataBlockSoa<RenderFilledEllipseTask> filledEllipseTasks;
	DataBlockSoa<RenderEllipseTask> ellipseTasks;
	DataBlockSoa<RenderTextureTask> textureTasks;

	void Free();
};
#pragma endregion

class RenderQueue
{
public:
	RenderQueue();
	~RenderQueue();

	void Initialize(RenderBackEnd* backEnd);

	template<typename T> void AddTask(typename T::Aos& task);

	void Flush();
	void FlushToPersistent();

private:
	RenderBackEnd* m_pRenderBackEnd;

	RenderTaskBuffer *m_pFrontBuffer, *m_pBackBuffer;
	bool m_FrontBufferActive;
};

template <typename T>
void RenderQueue::AddTask(typename T::Aos& task)
{
	//TODO: Throw/Log error
}

template<>
inline void RenderQueue::AddTask<RenderPointTask>(RenderPointTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->pointTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->pointTasks.Add(task);
	}
}

template<>
inline void RenderQueue::AddTask<RenderLineTask>(RenderLineTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->lineTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->lineTasks.Add(task);
	}
}

template<>
inline void RenderQueue::AddTask<RenderFilledTriangleTask>(RenderFilledTriangleTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->filledTriangleTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->filledTriangleTasks.Add(task);
	}
}

template<>
inline void RenderQueue::AddTask<RenderTriangleTask>(RenderTriangleTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->triangleTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->triangleTasks.Add(task);
	}
}

template<>
inline void RenderQueue::AddTask<RenderFilledRectangleTask>(RenderFilledRectangleTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->filledRectangleTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->filledRectangleTasks.Add(task);
	}
}

template<>
inline void RenderQueue::AddTask<RenderRectangleTask>(RenderRectangleTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->rectangleTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->rectangleTasks.Add(task);
	}
}

template<>
inline void RenderQueue::AddTask<RenderFilledEllipseTask>(RenderFilledEllipseTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->filledEllipseTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->filledEllipseTasks.Add(task);
	}
}

template<>
inline void RenderQueue::AddTask<RenderEllipseTask>(RenderEllipseTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->ellipseTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->ellipseTasks.Add(task);
	}
}

template<>
inline void RenderQueue::AddTask<RenderTextureTask>(RenderTextureTask::Aos& task)
{
	if(m_FrontBufferActive)
	{
		m_pFrontBuffer->textureTasks.Add(task);
	}
	else
	{
		m_pBackBuffer->textureTasks.Add(task);
	}
}