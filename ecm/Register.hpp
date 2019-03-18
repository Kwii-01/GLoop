#pragma once

#include <typeinfo>
#include <typeindex>
#include <memory>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>
#include "SparseSet.hpp"

// - work back on the global_view to optimize it
// - make idgenerator faster

namespace GEcm {

	template<typename ...Components>
	struct	view_s {
		entity_type				id;
		std::tuple<Components *...>	comps;
	};

	class Register {
		public:
			Register(size_type size = 100000, size_type compsize = 100) : _maxEntity(size) {
				_entities.reserve(size);
				_cpool.reserve(compsize);
			}

			Register(const Register &) = delete;

			Register(Register &&) = default;

			Register	&operator=(const Register &) = delete;

			Register	&operator=(Register &&) = default;

		public:

			/**
			 * size
			 * @deprecated Use this function to get the size of entities
			 * @returns This function will return the size of entities
			*/
			inline size_type	size() {
				return _entities.size();
			}

			/**
			 * size<T>
			 * @deprecated Use this function to get the size of a component pool
			 * @returns This function will return the size of the component pool
			*/
			template<typename Component>
			inline size_type	size() {
				return _cpool[assure<Component>()]->size();
			}

			/**
			 * has<T>
			 * @deprecated Use this function to know if an entity have a component <T>
			 * @returns This function will return True if the entity has the componenet otherwise it will return False
			*/
			template<typename Component>
			inline bool	has(entity_type id) {
				return _cpool[assure<Component>()]->has(id);
			}

			/**
			 * create
			 * @deprecated Use this function to create an entity
			 * @returns This function will return the id of the entity newly created
			*/
			entity_type	create() {
				entity_type	entity = idgenerator();

				if (entity >= _entities.size())
					_entities.push_back(entity);
				else
					_entities[GetRealId(entity)] = entity;
				return entity;
			}

			/**
			 * assign<T>
			 * @deprecated Use this function to assign a component to an entity
			 * @param ent is the id of the assigned entity
			 * @param comp is the component wich will be assigned
			*/
			template<typename Component>
			void	assign(const entity_type ent, const Component &comp) {
				static_cast<SparseSet<Component> *>(_cpool[assure<Component>()].get())->push(ent, comp);
			}

			/**
			 * construct<T, Args...>
			 * @deprecated Use this function to create a component and assign it to an entity
			 * @param ent is the id of the entity
			 * @param Args are the argument needed to call the component constructor
			 * @returns This function will return the component newly created
			*/
			template<typename Component, typename ...Args>
			Component	&construct(const entity_type ent, Args&& ...args) {
				return static_cast<SparseSet<Component> *>(_cpool[assure<Component>()].get())->emplace(ent, args...);
			}

			/**
			 * delete_components_of<Comps...>
			 * @deprecated Use this function to delete the choosen components of an entity
			 * @param ent is the id of the entity
			*/
			template<typename ...Components>
			inline void	delete_components_of(const entity_type id) {
				(delete_component<Components>(id), ...);
			}

			/**
			 * delete_entity
			 * @deprecated Use this function to delete an entity and its components
			 * @param ent is the id of the entity
			*/
			inline void	delete_entity(const entity_type id) {
				entity_type	realId = GetRealId(id);

				if (realId < _entities.size()) {
					_entities[realId] = 0;
					for(auto&& comps : _cpool)
						comps.second->destroy(id);
				}
			}

			/**
			 * get<T>
			 * @deprecated Use this function to get a component of an entity. 
			 * This function is not safe if the entity doesn't have the component.
			 * @param id is the id of the entity
			 * @returns this function will return the components
			*/
			template<typename Component>
			inline Component	&get(const entity_type id) {
				return static_cast<SparseSet<Component> *>(_cpool[assure<Component>()].get())->get(id);
			}

			/**
			 * try_get<T>
			 * @deprecated Use this function to get a component of an entity. 
			 * @param id is the id of the entity
			 * @returns this function will return a pointer to the components. If the entity doesn't have the component, it will return a nullptr.
			*/
			template<typename Component>
			inline Component	*try_get(const entity_type id) {
				return static_cast<SparseSet<Component> *>(_cpool[assure<Component>()].get())->try_get(id);
			}

			/**
			 * getPool<T>
			 * @deprecated Use this function to get the component pool choosen
			 * @returns this function will return the component pool
			*/
			template<typename Component>
			inline SparseSet<Component>	*getPool() {
				return static_cast<SparseSet<Component> *>(_cpool[assure<Component>()].get());
			}

			/**
			 * getNativePool<T>
			 * @deprecated Use this function to get the component pool choosen
			 * @returns this function will return the component pool
			*/
			template<typename Component>
			inline BaseSparseSet	*getNativePool() {
				return _cpool[assure<Component>()].get();
			}

			/**
			 * initPool<T>
			 * @deprecated Use this function to init the component pool by choosing its size
			 * @param size size of the component pool
			*/
			template<typename Component>
			inline void	initPool(const size_type size) {
				std::type_index	ctype = std::type_index(typeid(Component));

				if (_cpool.find(ctype) == _cpool.end())
					_cpool[ctype] = std::move(std::unique_ptr<BaseSparseSet>(new SparseSet<Component>{size}));
			}

			/**
			 * safe_view<T...>
			 * @deprecated Use this function to get safely the components of an entity
			 * @param id entity id
			 * @returns This function return a tuple of pointers on asked components
			*/
			template<typename ...Components>
			inline std::tuple<Components *...>	safe_view(const entity_type id) {
				std::tuple<Components *...>	data;
				(safe_initialise_tuple<Components>(data, id), ...);
				return data;
			}

			/**
			 * view<T...>
			 * @deprecated Use this function to get the components of an entity. This function can throw.
			 * @param id entity id
			 * @returns This function return a tuple of asked components
			*/
			template<typename ...Components>
			inline std::tuple<Components ...>	view(const entity_type id) {
				std::tuple<Components ...>	data;
				(initialise_tuple<Components>(data, id), ...);
				return data;
			}

			/**
			 * global_view<T...>
			 * @deprecated Use this function to get all the entity wich posses all asked components
			 * @returns This function return a sparset of view_s
			*/
			template<typename ...Components>
			SparseSet<view_s<Components...>>	global_view() {
				SparseSet<view_s<Components...>>	views(_entities.size());

				for(auto&& id : _entities) {
					if (!cpool_has<Components...>(id))
						continue;
					views.emplace(id, id, safe_view<Components...>(id));
				}
				views.shrink_to_fit();
				return views;
			}

		private:

			/**
			 * assure<T>
			 * @deprecated This function assure that the component pool is created for the component choosed
			 * @returns this function will return the id of the component pool
			*/
			template<typename Component>
			std::type_index	assure() {
				std::type_index	ctype = std::type_index(typeid(Component));

				if (_cpool.find(ctype) == _cpool.end())
					_cpool[ctype] = std::move(std::unique_ptr<BaseSparseSet>(new SparseSet<Component>{_maxEntity}));
				return ctype;
			}

			/**
			 * idgenerator
			 * @deprecated This function create the id and ca reuse old ids
			 * @returns this function will return an unused id
			*/
			entity_type	idgenerator() {
				auto	elem = std::find_if(_entities.begin(), _entities.end(), [](const entity_type &elem){ return (elem == 0) ? 1 : 0; });
				if (elem == _entities.end())
					return CreateId(_entities.size());
				return CreateId(elem - _entities.begin());
			}

			template<typename ...Components>
			inline bool	cpool_has(const entity_type id) {
				return (has<Components>(id) && ...);
			}

			/**
			 * delete_component
			 * @deprecated This function delete the component choosen of an entity
			 * @param id is the id of the entity
			*/
			template<typename Component>
			void	delete_component(const entity_type id) {
				static_cast<SparseSet<Component> *>(_cpool[assure<Component>()].get())->destroy(id);
			}

			template<typename Component, typename ...Components>
			inline void	safe_initialise_tuple(std::tuple<Components *...> &tuple, const entity_type id) {
				std::get<Component *>(tuple) = try_get<Component>(id);
			}

			template<typename Component, typename ...Components>
			inline void	initialise_tuple(std::tuple<Components ...> &tuple, const entity_type id) {
				std::get<Component>(tuple) = get<Component>(id);
			}

		private:
			size_type											_maxEntity;
			std::unordered_map<std::type_index, std::unique_ptr<BaseSparseSet>>	_cpool;
			std::vector<entity_type>								_entities;
	};

};