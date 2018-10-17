#pragma once
#pragma region Macros
#define DEFINE_SOA_CLASS(classType, nrMembers) \
	template<>\
	struct DataBlockSoaTraits<classType> { static const size_t member_count = nrMembers; };

#define DEFINE_SOA_TYPE(classType, idx, memberType, member) \
	template<> \
	struct GetType<classType,idx> {typedef memberType Type;}; \
	template<> \
	static GetPointerToMemberTypeAos<classType,idx>::Type GetPointerToMemberAos<classType,idx>(void) \
	{return &classType::Aos::member;} \
	template<> \
	static GetPointerToMemberTypeSoa<classType,idx>::Type GetPointerToMemberSoa<classType,idx>(void)\
	{return &classType::Soa::member;}
#pragma endregion 

#pragma region declarations
template <class T>
struct DataBlockSoaTraits
{
	static const size_t member_count = 0;
};

template<class T>
class DataBlockSoa
{
public:
	DataBlockSoa();
	~DataBlockSoa();

	void Free();
	void Resize(size_t newSize);
	size_t Remove(size_t index);

	size_t Add(const typename T::Aos& data);
	size_t GetSize() const { return m_Size; };

	typename T::Aos GetAos(size_t index); //Read-Only
	typename T::Soa GetSoa(size_t index); //Read/Write
private:
	size_t m_Size, m_AllocatedSize;
	void* m_Data[DataBlockSoaTraits<T>::member_count];

private:
	//Functors
	template <size_t IDX> struct AllocateInitial
	{
		void operator()(DataBlockSoa<T>* obj);
	};
	template <size_t IDX> struct AddMember
	{
		void operator()(DataBlockSoa<T>* obj,const typename T::Aos& data);
	};
	template <size_t IDX> struct RemoveMember
	{
		void operator()(DataBlockSoa<T>* obj, size_t index);
	};
	template <size_t IDX> struct ReallocateBlock
	{
		void operator()(DataBlockSoa<T>* obj, size_t newSize);
	};
	template <size_t IDX> struct GetMemberAos
	{
		void operator()(DataBlockSoa<T>* obj, typename T::Aos* temp, size_t index);
	};
	template <size_t IDX> struct GetMemberSoa
	{
		void operator()(DataBlockSoa<T>* obj, typename T::Soa* temp, size_t index);
	};

private:
	DataBlockSoa(const DataBlockSoa& other) = delete;
	DataBlockSoa& operator=(const DataBlockSoa& other) = delete;
	DataBlockSoa(DataBlockSoa&& other) = delete;
	DataBlockSoa& operator=(DataBlockSoa&& other) = delete;
};
#pragma endregion 

#pragma region Templates
#include <cstdlib>
template <typename T, size_t N>
struct GetType;

template <typename T, size_t N>
struct GetPointerToMemberTypeAos
{
	typedef typename GetType<T, N>::Type T::Aos::*Type;
};

template <typename T, size_t N>
struct GetPointerToMemberTypeSoa
{
	typedef typename GetType<T, N>::Type* T::Soa::*Type;
};

template <typename T, size_t N>
static typename GetPointerToMemberTypeAos<T, N>::Type GetPointerToMemberAos(void);

template <typename T, size_t N>
static typename GetPointerToMemberTypeSoa<T, N>::Type GetPointerToMemberSoa(void);

template<int I>
struct IntToType {};

typedef IntToType<true> ForEachDontTerminate;
typedef IntToType<false> ForEachTerminate;

template <size_t IDX, template<size_t IDX> class FUNC, size_t COUNT,class T, class ...Args>
void ForEach(ForEachDontTerminate, DataBlockSoa<T>* obj,Args ...args)
{
	FUNC<IDX> functor;
	functor(obj,args...);
	ForEach<IDX + 1,FUNC, COUNT>(IntToType<(IDX + 1 < COUNT)>(),obj,args...);
}

template <size_t IDX,template <size_t IDX> class FUNC,size_t COUNT, class T, class ...Args>
void ForEach(ForEachTerminate, DataBlockSoa<T>* obj,Args ...args)
{
	//Empty to end the loop
}

template <size_t IDX,template <size_t IDX> class FUNC, size_t COUNT, class T,class ...Args>
void ForEachClassMethod(DataBlockSoa<T>* obj,Args ...args)
{
	ForEach<0, FUNC, COUNT>(IntToType<0 < COUNT>(),obj, args...);
}
#pragma endregion 

#pragma region definitions
template <class T>
DataBlockSoa<T>::DataBlockSoa()
	:m_Size(0)
	,m_AllocatedSize(8)
{
	ForEachClassMethod<0, AllocateInitial, DataBlockSoaTraits<T>::member_count>(this);
}

template <class T>
DataBlockSoa<T>::~DataBlockSoa()
{
	for(int i = 0; i < DataBlockSoaTraits<T>::member_count;i++)
	{
		free(m_Data[i]);
	}
}

template <class T>
void DataBlockSoa<T>::Free()
{
	for (int i = 0; i < DataBlockSoaTraits<T>::member_count; i++)
	{
		free(m_Data[i]);
	}
}

template <class T>
void DataBlockSoa<T>::Resize(size_t newSize)
{
	ForEachClassMethod<0, ReallocateBlock, DataBlockSoaTraits<T>::member_count>(this, newSize);
}

template <class T>
size_t DataBlockSoa<T>::Remove(size_t index)
{
	if(index != (m_Size - 1u))
	{
		ForEachClassMethod<0, RemoveMember, DataBlockSoaTraits<T>::member_count>(this, index);
	}

	--m_Size;
	return m_Size;
}

template <class T>
size_t DataBlockSoa<T>::Add(const typename T::Aos& data)
{
	if (m_Size != m_AllocatedSize)
	{
		ForEachClassMethod<0, AddMember, DataBlockSoaTraits<T>::member_count>(this, data);
		++m_Size;
		return m_Size - 1;
	}
	Resize(m_AllocatedSize * 2);
	m_AllocatedSize *= 2;
	return Add(data);
}

template <class T>
typename T::Aos DataBlockSoa<T>::GetAos(size_t index)
{
	typename T::Aos temp{};

	ForEachClassMethod<0, GetMemberAos, DataBlockSoaTraits<T>::member_count>(this, &temp, index);

	return temp;
}

template <class T>
typename T::Soa DataBlockSoa<T>::GetSoa(size_t index)
{
	typename T::Soa temp{};

	ForEachClassMethod<0, GetMemberSoa, DataBlockSoaTraits<T>::member_count>(this, &temp, index);

	return temp;
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::AllocateInitial<IDX>::operator()(DataBlockSoa<T>* obj)
{
	typedef typename GetType<T, IDX>::Type DataType;
	obj->m_Data[IDX] = malloc(obj->m_AllocatedSize * sizeof(DataType));
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::AddMember<IDX>::operator()(DataBlockSoa<T>* obj, const  typename T::Aos& data)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* _data = static_cast<DataType*>(obj->m_Data[IDX]);
	_data[obj->m_Size] = data.*(GetPointerToMemberAos<T,IDX>());
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::RemoveMember<IDX>::operator()(DataBlockSoa<T>* obj, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	data[index] = data[obj->m_Size - 1u];
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::ReallocateBlock<IDX>::operator()(DataBlockSoa<T>* obj, size_t newSize)
{
	typedef typename GetType<T, IDX>::Type DataType;
	obj->m_Data[IDX] = realloc(obj->m_Data[IDX], newSize * sizeof(DataType));
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::GetMemberAos<IDX>::operator()(DataBlockSoa<T>* obj, typename T::Aos* temp, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	temp->*(GetPointerToMemberAos<T, IDX>()) = data[index];
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::GetMemberSoa<IDX>::operator()(DataBlockSoa<T>* obj, typename T::Soa* temp, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	temp->*(GetPointerToMemberSoa<T, IDX>()) = &data[index];
}
#pragma endregion 
