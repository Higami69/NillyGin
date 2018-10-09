#pragma once
template <typename T>
class Singleton
{
public:
	static T* GetInstance();
	static void DeleteInstance();

private:
	static T* m_pInstance;
};

template<typename T> T* Singleton<T>::m_pInstance = nullptr;

template <typename T>
T* Singleton<T>::GetInstance()
{
	if(m_pInstance) return m_pInstance;

	m_pInstance = new T();
	return m_pInstance;
}

template <typename T>
void Singleton<T>::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}
