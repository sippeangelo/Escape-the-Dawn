#ifndef World_h__
#define World_h__

#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

#include "logging.h"

#include "Factory.h"
#include "Entity.h"
#include "Component.h"
#include "System.h"

class World
{
public:
	World();
	~World();

	virtual void Initialize();

	virtual void RegisterComponents();
	virtual void RegisterSystems();

	void AddSystem(std::string systemType);
	template <class T>
	std::shared_ptr<T> GetSystem(std::string systemType);

	EntityID CreateEntity(EntityID parent = 0);

	void RemoveEntity(EntityID entity);

	bool ValidEntity(EntityID entity);

	EntityID GetEntityParent(EntityID entity);

	template <class T>
	std::shared_ptr<T> AddComponent(EntityID entity, std::string componentType);
	std::shared_ptr<Component> AddComponent(EntityID entity, std::string componentType);
	template <class T>
	std::shared_ptr<T> GetComponent(EntityID entity, std::string componentType);

	/*std::vector<EntityID> GetEntityChildren(EntityID entity);*/

	virtual void Update(double dt);
	// Recursively update through the scene graph 
	void RecursiveUpdate(std::shared_ptr<System> system, double dt, EntityID parentEntity);

protected:
	SystemFactory m_SystemFactory;
	ComponentFactory m_ComponentFactory;

	std::unordered_map<std::string, std::shared_ptr<System>> m_Systems;

	EntityID m_LastEntityID;
	std::stack<EntityID> m_RecycledEntityIDs;
	// A bottom to top tree. A map of child entities to parent entities.
	std::unordered_map<EntityID, EntityID> m_EntityParents;

	std::unordered_map<std::string, std::vector<std::shared_ptr<Component>>> m_ComponentsOfType;
	std::unordered_map<EntityID, std::map<std::string, std::shared_ptr<Component>>> m_EntityComponents;

	EntityID GenerateEntityID();

	void RecycleEntityID(EntityID id);
};

template <class T>
std::shared_ptr<T> World::GetSystem(std::string systemType)
{
	return std::static_pointer_cast<T>(m_Systems[systemType]);
}

template <class T>
std::shared_ptr<T> World::AddComponent(EntityID entity, std::string componentType)
{
	std::shared_ptr<T> component = std::shared_ptr<T>(static_cast<T*>(m_ComponentFactory.Create(componentType)));
	if (component == nullptr) {
		LOG_ERROR("Failed to attach invalid component \"%s\" to entity #%i", componentType.c_str(), entity);
		return nullptr;
	}

	component->Entity = entity;
	m_ComponentsOfType[componentType].push_back(component);
	m_EntityComponents[entity][componentType] = component;
	for (auto pair : m_Systems) {
		auto system = pair.second;
		system->OnComponentCreated(componentType, component);
	}
	return component;
}


template <class T>
std::shared_ptr<T> World::GetComponent(EntityID entity, std::string componentType)
{
	return std::static_pointer_cast<T>(m_EntityComponents[entity][componentType]);
}

#endif // World_h__