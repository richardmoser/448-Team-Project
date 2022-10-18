//Entity Component System

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
	
	static ComponentID lastID = 0;
	return lastID++;

}

template <typename T> inline ComponentID getComponentTypeID() noexcept{
	
	static ComponentID typeID = getComponentTypeID();
	return typeID;

}

//max ammount of items and entity is able to hold
constexpr std::size_t maxCompnents = 32;

//used to find out if an entity has a selection of components
using ComponentBitSet = std::bitset<maxCompnents>;
//array of component pointers
using ComponentArray = std::array<Component*, maxCompnents>;

class Component {

	public:
		Entity* entity;

		virtual void init() {}
		virtual void update() {}
		virtual void draw() {}

		virtual ~Component() {}

};

class Entity {

	private:
		bool active = true;
		std::vector<std::unique_ptr<Component>> components;

		ComponentArray componentArray;
		ComponentBitSet componentBitSet;
	public:
		void update() {
			for (auto& c : components) c->update();
			for (auto& c : components) c->draw();
		}
		void draw() {
	
		}
		bool isActive() const { return active; }
		void destory() { active = false; }

		//true or fase if we have that component
		template <typename T> bool hasComponent() const {
			return componentBitSet[getComponentTypeID<T>()];
		}

		template <typename T,typename... TArgs>
		T& addComponent(TArgs&&... myArgs) {
			
			T* c(new T(std::forward<TArgs>(myArgs)...));
			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			components.emplace_back(std::move(uPtr));

			componentArray[getComponentTypeID<T>()] = c;
			componentBitSet[getComponentTypeID<T>()] = true;

			c->init();
			return *c;
		}

		template <typename T> T& getComponent() const{
			auto ptr(componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

		//GameObject.getComponent<PosistionComponent>().setXpos(25);
};

class Manager {

	private:
		std::vector<std::unique_ptr<Entity>> entities;

	public:
		void update() {
			
			for (auto& e : entities) e->update();
		
		}

		void draw() {
		
			for (auto& e : entities) e->draw();

		}

		//removes entities if not active
		void refresh() {

			entities.erase(std::remove_if(std::begin(entities), std::end(entities),
				[](const std::unique_ptr<Entity>& mEntity)

				{
					return !mEntity->isActive();
				}),

				std::end(entities));

		}

		Entity& addEntity() {
		
			Entity* e = new Entity();
			std::unique_ptr<Entity> uPtr{ e };
			entities.emplace_back(std::move(uPtr));
			return *e;

		}
};