#pragma once

#include <vector>
#include <memory>
#include "System.hpp"

namespace gloop {

	using family_type = uint32_t;

	class GLoop {
		public:
			GLoop() = default;
			~GLoop() = default;

			void	run();


			void	addSystem();
			void	removeSystem();

		private:
			void	init();

			void	update();

		private:
	//		SparseSet<ISystem>	_systems;
	};
};