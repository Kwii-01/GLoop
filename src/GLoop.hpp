#pragma once

#include <algorithm>
//#include "ThreadPool.hpp"
#include "Loader.hpp"
#include "StageManager.hpp"

#define LOADED_FUNCTION	("HooksRegister")
using fcnt = void	(*)(g_reg::GRegister &, gloop::StageManager &);

namespace gloop {

	class GLoop {
		public:
			GLoop() = default;
			~GLoop() = default;

			void	run(g_reg::GRegister &reg);

			void	load_system(g_reg::GRegister &reg, const std::string &libPath, const std::string &functionName = LOADED_FUNCTION) {
				tools::load_s<fcnt>	loaded = _loader.load<fcnt>(libpath, functionName);
				loaded.function(reg, _stageM);
			}

			void	unload_system(const std::string &libPath) {
				_loader.unload(libpath);
			}

			gloop::StageManager	&get_stage_manager() noexcept { return _stageM; }

		private:
			gloop::HookStatus		run_hooks(gloop::Stage &, g_reg::GRegister &);
			gloop::HookStatus		run_loop_hooks(gloop::Stage &, g_reg::GRegister &);

			/* data */
			gloop::StageManager		_stageM;
			tools::Loader			_loader;
	};
};