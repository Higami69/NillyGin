#include "pch.h"
#include "POD.h"
#include <cstdlib>

POD::POD()
{
	m_Size = 0;
	m_AllocatedSize = 8;
	m_pData = malloc(8);
}

void POD::Clear()
{
	free(m_pData);
	m_pData = nullptr;
}

void POD::Resize()
{
	m_pData = realloc(m_pData, m_AllocatedSize *= 2);
}
