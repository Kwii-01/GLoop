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

			/**
			 * run
			 * @deprecated this function launch the gloop
			 * @param1 the register to use for the whole game
			*/
			void	run(g_reg::GRegister &reg);

			/**
			 * load_system
			 * @deprecated load one system
			 * @param1 library path
			*/
			void	load_system(const std::string &libpath, g_reg::GRegister &reg) {
				tools::load_s<fcnt>	loaded = _loader.load<fcnt>(libpath, LOADED_FUNCTION);
				loaded.function(reg, _stageM);
			}

			/**
			 * unload_system
			 * @deprecated this function unload a lib
			 * @param1 libpath to unload
			*/
			void	unload_system(const std::string &libpath) {
				_loader.unload(libpath);
			}

			/**
			 * get_stage_manager
			 * @deprecated this function return the stagemanager of the gloop
			 * @return the stage manager
			*/
			gloop::StageManager	&get_stage_manager() noexcept { return _stageM; }

		private:
			gloop::HookStatus		run_hooks(gloop::Stage &, g_reg::GRegister &);
			gloop::HookStatus		run_loop_hooks(gloop::Stage &, g_reg::GRegister &);

			/* data */
			gloop::StageManager		_stageM;
			tools::Loader			_loader;
	};
};