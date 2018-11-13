#pragma once
#pragma region Macros
#define DEFINE_SOA_CLASS(classType, nrMembers, nrStructs) \
	template<>\
	struct DataBlockSoaTraits<classType> { static const size_t member_count = nrMembers; \
											static const size_t struct_count = nrStructs; };

#define DEFINE_SOA_STRUCT(classType, structIdx, structType, structMember) \
	template<> \
	struct GetStructTypeByStructIdx<classType,structIdx> {typedef structType Type;}; \
	template<> \
	static typename GetPointerToStructMemberType<classType, structIdx>::Type GetPointerToStructMember<classType,structIdx>(void) \
	{return &classType::Soa::structMember;};

#define DEFINE_SOA_TYPE(classType, idx, memberType, member) \
	template<> \
	struct GetType<classType,idx> {typedef memberType Type;}; \
	template<> \
	static GetPointerToMemberTypeAos<classType,idx>::Type GetPointerToMemberAos<classType,idx>(void) \
	{return &classType::Aos::member;}; \
	template<> \
	static GetPointerToMemberTypeSoa<classType,idx>::Type GetPointerToMemberSoa<classType,idx>(void)\
	{return &classType::Soa::member;};

#define DEFINE_SOA_TYPE_STRUCT(classType, idx, structType, memberType, structName, member) \
	template<> \
	struct GetType<classType,idx> {typedef memberType Type;}; \
	template<> \
	struct GetStructType<classType,idx> {typedef structType Type;}; \
	template<> \
	struct IsInStruct<classType, idx> {const static bool IsStructMember = true;}; \
	template<> \
	static typename GetPointerToMemberTypeStructMemberAos<classType, structType, idx>::Type GetPointerToMemberStructMemberAos<classType,structType,idx>(void) \
	{return &structType::Aos::member;} \
	template<> \
	static typename GetPointerToMemberTypeStructMemberSoa<classType, structType, idx>::Type GetPointerToMemberStructMemberSoa<classType,structType,idx>(void) \
	{return &structType::Soa::member;} \
	template <> \
	static typename GetPointerToMemberTypeStructAos<classType, idx>::Type GetPointerToMemberStructAos<classType, idx>(void) \
	{return &classType::Aos::structName;} \
	template <> \
	static typename GetPointerToMemberTypeStructSoa<classType, idx>::Type GetPointerToMemberStructSoa<classType, idx>(void) \
	{return &classType::Soa::structName;}

#pragma endregion 

#pragma region declarations
template<int I>
struct IntToType {};

typedef IntToType<true> ForEachDontTerminate;
typedef IntToType<false> ForEachTerminate;
typedef IntToType<true> IsStruct;
typedef IntToType<false> IsNotStruct;

template <class T>
struct DataBlockSoaTraits
{
	static const size_t member_count = 0;
	static const size_t struct_count = 0;
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

	void FillSoaDefault(typename T::Soa* data);

	typename T::Aos GetAos(size_t index); //Read-Only
	typename T::Soa* GetSoa(typename T::Soa* data, size_t index); //Read/Write
private:
	size_t m_Size, m_AllocatedSize;
	void* m_Data[DataBlockSoaTraits<T>::member_count];

private:
	//Functors
	template <size_t IDX> struct AllocateInitial
	{
		void operator()(IsStruct, DataBlockSoa<T>* obj);
		void operator()(IsNotStruct, DataBlockSoa<T>* obj);
	};
	template <size_t IDX> struct AddMember
	{
		void operator()(IsStruct, DataBlockSoa<T>* obj, const typename T::Aos& data);
		void operator()(IsNotStruct, DataBlockSoa<T>* obj, const typename T::Aos& data);
	};
	template <size_t IDX> struct RemoveMember
	{
		void operator()(IsStruct, DataBlockSoa<T>* obj, size_t index);
		void operator()(IsNotStruct, DataBlockSoa<T>* obj, size_t index);
	};
	template <size_t IDX> struct ReallocateBlock
	{
		void operator()(IsStruct, DataBlockSoa<T>* obj, size_t newSize);
		void operator()(IsNotStruct, DataBlockSoa<T>* obj, size_t newSize);
	};
	template <size_t IDX> struct GetMemberAos
	{
		void operator()(IsStruct, DataBlockSoa<T>* obj, typename T::Aos* temp, size_t index);
		void operator()(IsNotStruct, DataBlockSoa<T>* obj, typename T::Aos* temp, size_t index);
	};
	template <size_t IDX> struct GetMemberSoa
	{
		void operator()(IsStruct, DataBlockSoa<T>* obj, typename T::Soa* temp, size_t index);
		void operator()(IsNotStruct, DataBlockSoa<T>* obj, typename T::Soa* temp, size_t index);
	};
	template <size_t IDX> struct FillSoaDefaultMember
	{
		void operator()(IsStruct, DataBlockSoa<T>* obj, typename T::Soa* data);
		void operator()(IsNotStruct, DataBlockSoa<T>* obj, typename T::Soa* data);
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
struct GetStructType;

template <typename T, size_t N>
struct GetStructTypeByStructIdx;

template<typename T, size_t N> 
struct IsInStruct { const static bool IsStructMember = false; }; 

template <typename T, size_t N>
struct GetPointerToMemberTypeAos
{
	typedef typename GetType<T, N>::Type T::Aos::*Type;
};

template <typename T, typename Y, size_t N>
struct GetPointerToMemberTypeStructMemberAos
{
	typedef typename GetType<T, N>::Type Y::Aos::*Type;
};

template <typename T, typename Y, size_t N>
struct GetPointerToMemberTypeStructMemberSoa
{
	typedef typename GetType<T, N>::Type* Y::Soa::*Type;
};

template <typename T, size_t N>
struct GetPointerToMemberTypeStructAos
{
	typedef typename GetStructType<T, N>::Type::Aos T::Aos::*Type;
};

template <typename T, size_t N>
struct GetPointerToMemberTypeStructSoa
{
	typedef typename GetStructType<T, N>::Type::Soa* T::Soa::*Type;
};

template <typename T, size_t N>
struct GetPointerToMemberTypeSoa
{
	typedef typename GetType<T, N>::Type* T::Soa::*Type;
};

template <typename T, size_t N>
struct GetPointerToStructMemberType
{
	typedef typename GetStructTypeByStructIdx<T, N>::Type* T::Soa::*Type;
};

template <typename T, typename Y, size_t N>
static typename GetPointerToMemberTypeStructMemberAos<T, Y, N>::Type GetPointerToMemberStructMemberAos(void);

template <typename T, typename Y, size_t N>
static typename GetPointerToMemberTypeStructMemberSoa<T, Y, N>::Type GetPointerToMemberStructMemberSoa(void);

template <typename T, size_t N>
static typename GetPointerToMemberTypeStructAos<T, N>::Type GetPointerToMemberStructAos(void);

template <typename T, size_t N>
static typename GetPointerToMemberTypeStructSoa<T, N>::Type GetPointerToMemberStructSoa(void);

template <typename T, size_t N>
static typename GetPointerToStructMemberType<T, N>::Type GetPointerToStructMember(void);

template <typename T, size_t N>
static typename GetPointerToMemberTypeAos<T, N>::Type GetPointerToMemberAos(void);

template <typename T, size_t N>
static typename GetPointerToMemberTypeSoa<T, N>::Type GetPointerToMemberSoa(void);

template <size_t IDX, template<size_t IDX> class FUNC, size_t COUNT,class T, class ...Args>
void ForEach(ForEachDontTerminate, IsNotStruct, DataBlockSoa<T>* obj,Args ...args)
{
	FUNC<IDX> functor;
	functor(IntToType<IsInStruct<T, IDX>().IsStructMember>(), obj, args...);
	ForEach<IDX + 1,FUNC, COUNT>(IntToType<(IDX + 1 < COUNT)>(), IntToType<IsInStruct<T,IDX + 1>().IsStructMember>(), obj, args...);
}

template <size_t IDX, template<size_t IDX> class FUNC, size_t COUNT, class T, class ...Args>
void ForEach(ForEachDontTerminate, IsStruct, DataBlockSoa<T>* obj, Args ...args)
{
	FUNC<IDX> functor;
	functor(IntToType<IsInStruct<T, IDX>().IsStructMember>(), obj, args...);
	ForEach<IDX + 1, FUNC, COUNT>(IntToType<(IDX + 1 < COUNT)>(), IntToType<IsInStruct<T, IDX + 1>().IsStructMember>(), obj, args...);
}

template <size_t IDX,template <size_t IDX> class FUNC,size_t COUNT, class T, class ...Args>
void ForEach(ForEachTerminate, IsStruct, DataBlockSoa<T>* obj,Args ...args)
{
	//Empty to end the loop
}

template <size_t IDX, template <size_t IDX> class FUNC, size_t COUNT, class T, class ...Args>
void ForEach(ForEachTerminate, IsNotStruct, DataBlockSoa<T>* obj, Args ...args)
{
	//Empty to end the loop
}

template <size_t IDX,template <size_t IDX> class FUNC, size_t COUNT, class T,class ...Args>
void ForEachClassMethod(DataBlockSoa<T>* obj,Args ...args)
{
	ForEach<0, FUNC, COUNT>(IntToType<0 < COUNT>(), IntToType<IsInStruct<T, 0>().IsStructMember>(), obj, args...);
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
		m_Data[i] = nullptr;
	}
}

template <class T>
void DataBlockSoa<T>::Free()
{
	for (int i = 0; i < DataBlockSoaTraits<T>::member_count; i++)
	{
		free(m_Data[i]);
		m_Data[i] = nullptr;
	}

	m_Size = 0;
	m_AllocatedSize = 0;
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
	if (m_AllocatedSize > 0)
	{
		m_AllocatedSize *= 2;
		Resize(m_AllocatedSize);
		return Add(data);
	}
	m_AllocatedSize = 8;
	Resize(m_AllocatedSize);
	return Add(data);
}

template <class T>
void DataBlockSoa<T>::FillSoaDefault(typename T::Soa* data)
{
	ForEachClassMethod<0, FillSoaDefaultMember, DataBlockSoaTraits<T>::struct_count>(this, data);
}

template <class T>
typename T::Aos DataBlockSoa<T>::GetAos(size_t index)
{
	typename T::Aos temp{};

	ForEachClassMethod<0, GetMemberAos, DataBlockSoaTraits<T>::member_count>(this, &temp, index);

	return temp;
}

template <class T>
typename T::Soa* DataBlockSoa<T>::GetSoa(typename T::Soa* data, size_t index)
{
	ForEachClassMethod<0, GetMemberSoa, DataBlockSoaTraits<T>::member_count>(this, data, index);

	return data;
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::AllocateInitial<IDX>::operator()(IsStruct, DataBlockSoa<T>* obj)
{
	typedef typename GetType<T, IDX>::Type DataType;
	obj->m_Data[IDX] = malloc(obj->m_AllocatedSize * sizeof(DataType));
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::AllocateInitial<IDX>::operator()(IsNotStruct, DataBlockSoa<T>* obj)
{
	typedef typename GetType<T, IDX>::Type DataType;
	obj->m_Data[IDX] = malloc(obj->m_AllocatedSize * sizeof(DataType));
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::AddMember<IDX>::operator()(IsStruct, DataBlockSoa<T>* obj, const typename T::Aos& data)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* _data = static_cast<DataType*>(obj->m_Data[IDX]);
	_data[obj->m_Size] = data.*(GetPointerToMemberStructAos<T, IDX>()).*(GetPointerToMemberStructMemberAos<T, typename GetStructType<T, IDX>::Type, IDX>());
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::AddMember<IDX>::operator()(IsNotStruct, DataBlockSoa<T>* obj, const  typename T::Aos& data)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* _data = static_cast<DataType*>(obj->m_Data[IDX]);
	_data[obj->m_Size] = data.*(GetPointerToMemberAos<T,IDX>());
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::RemoveMember<IDX>::operator()(IsStruct, DataBlockSoa<T>* obj, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	data[index] = data[obj->m_Size - 1u];
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::RemoveMember<IDX>::operator()(IsNotStruct, DataBlockSoa<T>* obj, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	data[index] = data[obj->m_Size - 1u];
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::ReallocateBlock<IDX>::operator()(IsStruct, DataBlockSoa<T>* obj, size_t newSize)
{
	typedef typename GetType<T, IDX>::Type DataType;
	obj->m_Data[IDX] = realloc(obj->m_Data[IDX], newSize * sizeof(DataType));
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::ReallocateBlock<IDX>::operator()(IsNotStruct, DataBlockSoa<T>* obj, size_t newSize)
{
	typedef typename GetType<T, IDX>::Type DataType;
	obj->m_Data[IDX] = realloc(obj->m_Data[IDX], newSize * sizeof(DataType));
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::GetMemberAos<IDX>::operator()(IsStruct, DataBlockSoa<T>* obj, typename T::Aos* temp, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	temp->*(GetPointerToMemberStructAos<T, IDX>()).*(GetPointerToMemberStructMemberAos<T,typename GetStructType<T,IDX>::Type,IDX>()) = data[index];
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::GetMemberAos<IDX>::operator()(IsNotStruct, DataBlockSoa<T>* obj, typename T::Aos* temp, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	temp->*(GetPointerToMemberAos<T, IDX>()) = data[index];
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::GetMemberSoa<IDX>::operator()(IsStruct, DataBlockSoa<T>* obj, typename T::Soa* temp, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	temp->*(GetPointerToMemberStructSoa<T, IDX>())->*(GetPointerToMemberStructMemberSoa<T,typename GetStructType<T,IDX>::Type,IDX>()) = &data[index];
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::GetMemberSoa<IDX>::operator()(IsNotStruct, DataBlockSoa<T>* obj, typename T::Soa* temp, size_t index)
{
	typedef typename GetType<T, IDX>::Type DataType;
	DataType* data = static_cast<DataType*>(obj->m_Data[IDX]);
	temp->*(GetPointerToMemberSoa<T, IDX>()) = &data[index];
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::FillSoaDefaultMember<IDX>::operator()(IsStruct, DataBlockSoa<T>* obj, typename T::Soa* data)
{
	typedef typename GetStructTypeByStructIdx<T, IDX>::Type DataType;
	data->*(GetPointerToStructMember<T, IDX>()) = new DataType();
}

template <class T>
template <size_t IDX>
void DataBlockSoa<T>::FillSoaDefaultMember<IDX>::operator()(IsNotStruct, DataBlockSoa<T>* obj, typename T::Soa* data)
{
	typedef typename GetStructTypeByStructIdx<T, IDX>::Type DataType;
	data->*(GetPointerToStructMember<T, IDX>()) = new DataType();
}
#pragma endregion 
