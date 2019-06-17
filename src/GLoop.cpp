#include "GLoop.hpp"

namespace gloop {

	void	GLoop::run(g_reg::GRegister &reg) {
		auto ret = run_hooks(_stageM.get_stage(gloop::StageType::INIT), reg);
		if (ret == gloop::HookStatus::ERROR)
			return;
		while ((ret = run_loop_hooks(_stageM.get_stage(gloop::StageType::LOOP), reg)) == gloop::HookStatus::OK);
		if (ret != gloop::HookStatus::STOP_LOOP)
			return;
		run_hooks(_stageM.get_stage(gloop::StageType::FINAL), reg);
	}

	gloop::HookStatus		GLoop::run_hooks(gloop::Stage &stage, g_reg::GRegister &reg) {
		for (auto &&elem : stage.get_hookMap()) {
			auto ret = elem.second.hook.callback(reg, *this);
			if (ret != gloop::HookStatus::OK)
				return ret;
		}
		return gloop::HookStatus::OK;
	}

	gloop::HookStatus		GLoop::run_loop_hooks(gloop::Stage &stage, g_reg::GRegister &reg) {
		for (auto &&elem : stage.get_hookMap()) {
			gtimer		now = std::chrono::system_clock::now();
			long		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - elem.second.last_call).count();
			if (elapsed >= elem.second.hook.callrate) {
				auto		ret = gloop::HookStatus::OK;
				elem.second.last_call = now;
				ret = elem.second.hook.callback(reg, *this);
				if (ret != gloop::HookStatus::OK)
					return ret;
			}
		}
		return gloop::HookStatus::OK;
	}

} // gloop