#include "pch.h"
#include <vld.h>
#include "DataBlockSoa.h"
#include "EntityManager.h"
#include "ComponentSystem.h"
#include <iostream>

#pragma region test
struct Foo
{
	struct Aos
	{
		int a, b;
		float c;
	};

	struct Soa
	{
		int *a, *b;
		float *c;
	};
};

DEFINE_SOA_CLASS(Foo, 3)
DEFINE_SOA_TYPE(Foo, 0, int, a)
DEFINE_SOA_TYPE(Foo, 1, int, b)
DEFINE_SOA_TYPE(Foo, 2, float, c)

class FooSystem : public ComponentSystem<Foo>
{
public:
	void OnUpdate(Foo::Soa* component,size_t entity) override;
	void OnLateUpdate(Foo::Soa* component, size_t entity) override
	{
		
	}
	void OnCleanUp(Foo::Soa* component) override
	{
		
	}
};

void FooSystem::OnUpdate(Foo::Soa* component, size_t entity)
{
	std::cout << "A";
}

struct Bar
{
	struct Aos
	{
		float b, c;
		char d;
	};

	struct Soa
	{
		float *b, *c;
		char *d;
	};
};

DEFINE_SOA_CLASS(Bar,3)
DEFINE_SOA_TYPE(Bar,0,float,b)
DEFINE_SOA_TYPE(Bar,1,float,c)
DEFINE_SOA_TYPE(Bar,2,char,d)

class BarSystem : public ComponentSystem<Bar>
{
	void OnUpdate(Bar::Soa* component, size_t entity) override
	{
		std::cout << "X";
	}
	void OnLateUpdate(Bar::Soa* component, size_t entity) override
	{
		
	}
	void OnCleanUp(Bar::Soa* component) override
	{
		
	}
};

struct Rekt
{
	struct Aos
	{
		int b;
	};

	struct Soa
	{
		int *b;
	};
};

DEFINE_SOA_CLASS(Rekt,1)
DEFINE_SOA_TYPE(Rekt,0,int,b)

class RektSystem : public ComponentSystem<Rekt>
{
	void OnUpdate(Rekt::Soa* component, size_t entity) override
	{
		EntityManager::GetInstance()->Destroy(entity);
	}
	void OnLateUpdate(Rekt::Soa* component, size_t entity) override
	{
		
	}
	void OnCleanUp(Rekt::Soa* component) override
	{
		
	}
};
#pragma endregion 

//int main()
//{
//	srand(unsigned int(time(nullptr)));
//	auto entityManager = EntityManager::GetInstance();
//	auto systemManager = SystemManager::GetInstance();
//	FooSystem foo{};
//	BarSystem bar{};
//	RektSystem rekt{};
//
//	for(size_t i = 0;i < 100u;i++)
//	{
//		for (size_t j = 0; j < 2; j++)
//		{
//			size_t idx = entityManager->Create();
//			foo.AddComponent(idx, Foo::Aos{});
//			bar.AddComponent(idx, Bar::Aos{});
//			if ((rand() % 5) == 0) rekt.AddComponent(idx, Rekt::Aos{});
//		}
//		
//		entityManager->Destroy(i);
//
//		systemManager->Update();
//		std::cout << std::endl;
//	}
//
//	systemManager->CleanUp();
//	EntityManager::DeleteInstance();
//	SystemManager::DeleteInstance();
//
//	system("pause");
//	return 0;
//}