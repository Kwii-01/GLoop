#pragma once

#include <typeinfo>
#include <typeindex>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <vector>

#include "IdManager.hpp"
#include "SparseSet.hpp"

namespace g_reg {

	using bsparse_set = sparset_collection::BaseSparseSet;
	template<typename T>
	using sparse_set = sparset_collection::SparseSet<T>;
	using	components_pool = std::unordered_map<std::type_index, std::unique_ptr<bsparse_set>>;

	template<typename ...T>
	struct entity_s {
		std::size_t			id;
		std::tuple<T *...>	components;
	};


	class GRegister {
		public:
			GRegister(const std::size_t max_entity, const std::size_t max_components) : _max(max_entity), _gid(max_entity) {
				_pool.reserve(max_components);
			}

			GRegister(const g_reg::GRegister &) = default;
			GRegister(g_reg::GRegister &&) = default;

			std::size_t	size() const { return _reg.size(); }

			template<typename T>
			std::size_t	cpool_size() { return _pool[assure<T>()]->size(); }

			template<typename T>
			bool	has(const std::size_t id) { return _pool[assure<T>()]->has(id); }

			template<typename ...T>
			bool	cpool_has(const std::size_t id) { return (has<T>(id) && ...); }

			std::size_t	create() {
				std::size_t id = _gid.use();

				_reg.insert(id);
				return id;
			}

			template<typename T>
			void	assign(const std::size_t id, const T &component) {
				static_cast<sparse_set<T> *>(_pool[assure<T>()].get())->insert(id, component);
			}

			template<typename Component, typename ...Args>
			Component	&construct(const std::size_t id, Args&& ...arguments) {
				return static_cast<sparse_set<Component> *>(_pool[assure<Component>()].get())->emplace(id, arguments...);
			}

			template<typename ...T>
			void	delete_components(const std::size_t id) {
				(delete_component<T>(id), ...);
			}

			void	delete_entity(const std::size_t id) {
				_gid.free(id);
				_reg.erase(id);
				for (auto &&comp : _pool)
					comp.second->remove(id);
			}

			void	clear_entity_components(const std::size_t id) {
				for (auto &&comp : _pool)
					comp.second->remove(id);
			}

			template<typename T>
			inline T	&get(const std::size_t id) {
				return static_cast<sparse_set<T> *>(_pool[assure<T>()].get())->get(id);
			}

			template<typename T>
			inline T	*try_get(const std::size_t id) {
				return static_cast<sparse_set<T> *>(_pool[assure<T>()].get())->try_get(id);
			}

			template<typename ...T>
			std::tuple<T ...>	view(const std::size_t id) {
				return std::tuple<T ...>{get<T>(id)...};
			}

			template<typename ...T>
			std::tuple<T *...>	safe_view(const std::size_t id) {
				return std::tuple<T *...>{try_get<T>(id)...};
			}

			template<typename ...T>
			std::vector<g_reg::entity_s<T...>>	global_view() {
				std::vector<g_reg::entity_s<T...>>	data;

				data.reserve(_reg.size());
				for (auto &&id : _reg) {
					if (cpool_has<T...>(id))
						data.push_back({id, safe_view<T...>(id)});
				}
				data.shrink_to_fit();
				return data;
			}

			template<typename T>
			sparse_set<T>	*get_pool() { return static_cast<sparse_set<T> *>(_pool[assure<T>()].get()); }

			template<typename T>
			inline bsparse_set	*get_native_pool() { return _pool[assure<T>()].get(); }

		private:
			template<typename T>
			std::type_index	assure() {
				std::type_index ctype = std::type_index(typeid(T));

				if (_pool.find(ctype) == _pool.end())
					_pool[ctype] = std::move(std::unique_ptr<bsparse_set>(new sparse_set<T>{_max}));
				return ctype;
			}

			template<typename T>
			void	delete_component(const std::size_t id) {
				_pool[assure<T>()]->remove(id);
			}


			std::size_t				_max;
			g_reg::IdManager		_gid;
			std::unordered_set<std::size_t>	_reg;
			components_pool			_pool;
	}; // GRegister

} // g_reg