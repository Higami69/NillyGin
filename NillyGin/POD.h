#pragma once

class POD
{
public:
	POD();

	template<typename T, typename ...Args>
	T* Create(Args ...args);

	void Clear();

private:
	void Resize();

	void* m_pData;
	size_t m_AllocatedSize, m_Size;
};

template <typename T, typename ... Args>
T* POD::Create(Args... args)
{
	if (m_Size + sizeof(T) < m_AllocatedSize)
	{
		T* result = new(m_pData + char(m_Size)) T(args);
		m_Size += sizeof(T);
		return result;
	}
	
	Resize();
	return Create<T>(args);
}
