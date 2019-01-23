#pragma once

#include <vector>
#include <memory>
#include "System.hpp"

Register register;

namespace gloop {

	using family_type = uint32_t;

	class GLoop {
		public:
			GLoop() = default;
			~GLoop() = default;

			void	run();

			void	addSystem(ISystem systemToAdd) {
				auto it = _systems.begin();

				while (it != _systems.end()) {
					if (it->getPriority() >= systemToAdd.getPriority()) {
						_systems.emplace(it, systemToAdd);
						break;
					}
					it += 1;
				}
				if (it == _systems.end()) {
					_systems.emplace_back(systemToAdd);
				}
			};
			void	removeSystem(ISystem System) {
				//check if path in system vector
				//if it's in remove it
				//else return error message cannot found this system.
			};

		private:
			void	init();

			void	update();
			void	loadSystem(std::string const &path);
			void	unloadSystem(std::string const &path);


		private:
			std::size_t			_maxSys;
	//		SparseSet<ISystem>	_systems;
			std::vector<ISystem> _systems;
	};
};