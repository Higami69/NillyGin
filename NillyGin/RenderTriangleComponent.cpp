#include "pch.h"
#include "RenderTriangleComponent.h"
#include "RenderQueue.h"

RenderTriangleComponentSystem::RenderTriangleComponentSystem()
{
}

void RenderTriangleComponentSystem::OnUpdate(RenderTriangleComponent::Soa* component, size_t entity)
{
}

void RenderTriangleComponentSystem::OnLateUpdate(RenderTriangleComponent::Soa* component, size_t entity)
{
}

void RenderTriangleComponentSystem::OnCleanUp(RenderTriangleComponent::Soa* component)
{
}

void RenderTriangleComponentSystem::OnDraw(RenderQueue* renderQueue, const RenderTriangleComponent::Aos& component, TransformComponent::Aos transform)
{
	if(component.isFilled)
	{
		RenderFilledTriangleTask::Aos task;
		task.colour = component.colour;
		task.depth = transform.pos.z;
		task.point1 = Float2::Aos(transform.pos.x + component.point1.x, transform.pos.y + component.point1.y);
		task.point2 = Float2::Aos(transform.pos.x + component.point2.x, transform.pos.y + component.point2.y);
		task.point3 = Float2::Aos(transform.pos.x + component.point3.x, transform.pos.y + component.point3.y);
		renderQueue->AddTask<RenderFilledTriangleTask>(task);
	}
	else
	{
		RenderTriangleTask::Aos task;
		task.colour = component.colour;
		task.depth = transform.pos.z;
		task.lineWidth = component.lineWidth;
		task.point1 = Float2::Aos(transform.pos.x + component.point1.x, transform.pos.y + component.point1.y);
		task.point2 = Float2::Aos(transform.pos.x + component.point2.x, transform.pos.y + component.point2.y);
		task.point3 = Float2::Aos(transform.pos.x + component.point3.x, transform.pos.y + component.point3.y);
		renderQueue->AddTask<RenderTriangleTask>(task);
	}
}

RenderTriangleComponent::Aos RenderTriangleComponentSystem::CreateTriangleAroundPoint(float width, float height, Colour::Aos colour, bool isFilled, float lineWidth)
{
	RenderTriangleComponent::Aos triangle;
	triangle.colour = colour;
	triangle.point1 = Float2::Aos(-width / 2.f, -height / 2.f);
	triangle.point2 = Float2::Aos(width / 2.f, -height / 2.f);
	triangle.point3 = Float2::Aos(0.f, height / 2.f);
	triangle.isFilled = isFilled;
	triangle.lineWidth = lineWidth;
	return triangle;
}
