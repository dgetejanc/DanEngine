#pragma once

//Includes
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//This is a very basic ECS I build to learn how to build an ECS, but I am going to switch this 
//out with EnTT eventually. 


//Class Definitions
class Component; //Component base class 
class Entity; //Entity base class
class Manager; //Manager

//using directives 
using ComponentID = std::size_t; 
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
	
	static ComponentID lastID = 0u; //The using Directive prevented me from typing "static std::size_t lastID"
	
	return lastID++;
	
}

//Component Template
template <typename T> inline ComponentID getComponentTypeID() noexcept {
	
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;

}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;


using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;


//Component Class / Just an Interface
class Component{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component() {}

};

class Entity {
private: 

	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitset groupBitset;

public:
	
	Entity(Manager& mManager) : manager(mManager) {}
	
	void update() {
		for (auto& c : components) c->update();
	}

	void draw(){

		for (auto& c : components) c->draw();
	}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	//Grouping Entities if possible for speed
	bool hasGroup(Group mGroup){

		return groupBitset[mGroup];
	
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup){

		groupBitset[mGroup] = false;
	
	}

	template <typename T> bool hasComponent() const{

		return componentBitset[getComponentTypeID<T>()];

	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs){

		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->init();
		return *c;

	}

	template<typename T> T& getComponent() const{

		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	
	}

};

class Manager{

private:

	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:

	void update(){

		for (auto& e : entities) e->update();
	
	}
	
	void draw(){

		for (auto& e : entities) e->draw();
	
	}

	void refresh(){

		for (auto i(0u); i < maxGroups; i++){

			auto& v(groupedEntities[i]);

			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity){
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),std::end(v));
		
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),[](const std::unique_ptr<Entity> &mEntity){

			return !mEntity->isActive();
		
		}),std::end(entities));
	
	}

	void AddToGroup(Entity* mEntity, Group mGroup){

		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup){

		return groupedEntities[mGroup];
	
	}

	Entity& addEntity(){

		Entity *e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	
	}

};

