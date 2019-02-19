#pragma once

#include "System.hpp"
#include "Loader.hpp"
#include "IdManager.hpp"

namespace gloop {

	using family_type = uint32_t;

	struct system_s {
		std::size_t id;
		gloop::ISystem *system;
	};

	class GLoop {
		public:
			GLoop() = default;
			~GLoop() = default;

			void	run() {
				init();
				while (1) {
					update();
				}
			};

			void	runStart();
			void	runMiddle();
			void	runEnd();

			/*
			** construct a system and return it
			*/
			template<typename System, typename ...Args>
			System	&construct(Args&& ...args) {
				return System{std::forward<Args>(args) ...};
			}

			void	addSystem(gloop::ISystem *systemToAdd) {
				/*for (auto &&elem = _systems.begin(); elem != _systems.end(); ++elem)
				{
					if ((*elem)->getPriority() >= systemToAdd->getPriority()) {
						_systems.emplace(elem, std::move(systemToAdd));
						return;
					}
				}*/
				std::size_t id = _idManager.generate();
				_systems.push_back( {id, std::move(systemToAdd)} );
			}

			void	removeSystem(std::size_t id) {
				for (auto &&elem = _systems.begin(); elem != _systems.end(); ++elem)
				{
					if (elem->id == id) {
						_systems.erase(elem);
						return;
					}
				}
				std::cerr << "Error: Cannot found system" << std::endl;

			};

		private:
			void	init() {};
			void	update() {
				for (auto &&elem: _systems) {
					elem.system->update();
				}
			};

		private:
			tools::IdManager			_idManager;
			tools::Loader		_loader;
			std::size_t			_maxSys;
			std::vector<system_s> _systems;

	};
};

// ADD SYSTEM
				/*_systems.push_back(systemToAdd);
				auto start = _systems.begin();
				auto end = _systems.end();

				std::sort(start, end, [](const std::shared_ptr<ISystem> &left, const std::shared_ptr<ISystem> &right) {return left->getPriority() < right->getPriority(); } );
				std::cout << "system added" << std::endl;
				auto it = _systems.begin();*/

// REMOVE SYSTEM
				/*est ce que on lie le gloop a family pour generate un id pour system (on aurait 2 family une de component et autre de systeme)
				romove via un id ? ou getname ? ou ?
				check if path in system vector
				if it's in remove it
				else return error message cannot found this system.*/

