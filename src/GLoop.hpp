#pragma once

#include <memory>
#include "System.hpp"

namespace gloop {

	using family_type = uint32_t;

	class GLoop {
		public:
			GLoop() = default;
			~GLoop() = default;

			void	run() {
				while (1) {
					update();
				}
			};

			/*
			** construct a system
			*/
			template<typename System, typename ...Args>
			System	&construct(Args&& ...args) {

			}

			void	addSystem(gloop::ISystem *systemToAdd) {
				for (auto &&elem = _systems.begin(); elem != _systems.end(); ++elem)
				{
					if ((*elem)->getPriority() >= systemToAdd->getPriority()) {
						_systems.emplace(elem, std::move(systemToAdd));
						return;
					}
				}
				_systems.emplace_back(std::move(systemToAdd));
			}

			void	removeSystem(gloop::ISystem *System) {
				for (auto &&elem = _systems.begin(); elem != _systems.end(); ++elem)
				{
					if ((*elem).get() == System) {
						_systems.erase(elem);
						return;
					}
				}
				if (System == (*_systems.end()).get())
					_systems.pop_back();
				else
					std::cerr << "Error: Cannot found system" << std::endl;

			};

		private:
			void	init() {};
			void	update() {
				for (auto &&elem: _systems) {
					elem->update();
				}
			};
			void	loadSystem(std::string const &path) {(void)path;};
			void	unloadSystem(std::string const &path) {(void)path;};


		private:
			std::size_t			_maxSys;
			std::vector<std::unique_ptr<ISystem>> _systems;

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

