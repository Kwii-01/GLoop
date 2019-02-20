#pragma once

#include "StageManager.hpp"

namespace gloop {

	class GLoop {
		public:
			GLoop() = default;
			~GLoop() = default;

			void	run(/* ecm::Register & */);

			void	load_system(const std::string &);
			void	unload_system(const std::string &);

			gloop::StageManager	&get_stage_manager() noexcept { return _stageM; }

		private:
			gloop::StageManager					_stageM;
			std::unordered_map<std::string, std::string>	_loaded_systems;
	};
};