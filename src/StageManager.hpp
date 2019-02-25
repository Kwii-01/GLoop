#pragma once

#include <unordered_map>
#include <map>
#include "GHeaders.hpp"

namespace gloop {

	class Stage {
		public:
			using hookMap = std::multimap<gloop::guint, gloop::HookCallRate>;

			Stage() = default;
			~Stage() = default;

			void	add_hook(const gloop::HookType type, gloop::SystemHook &hook) { _hooks[type].insert(std::make_pair(hook.weight_p, gloop::HookCallRate{hook, std::chrono::system_clock::now()})); }

			void	remove_system_hooks(const std::string &sys) {
				for(auto&& hooks : _hooks)
					remove_system_hook_from(hooks.first, sys);
			}

			void	remove_system_hook_from(const gloop::HookType type, const std::string &sys) {
				auto elem = std::find_if(_hooks[type].begin(), _hooks[type].end(), [sys](const std::pair<gloop::guint, gloop::HookCallRate> &h){ return h.second.hook.sys_name == sys; });
				if (elem != _hooks[type].end())
					_hooks[type].erase(elem);
			}

			void	clear_hooks() noexcept {
				for(auto&& hooks : _hooks)
					clear_hooks(hooks.first);
			}

			void	clear_hooks(const gloop::HookType type) noexcept { _hooks[type].clear(); }

			hookMap	&get_hookMap(const gloop::HookType type) noexcept { return _hooks[type]; }

		private:
			/* data */
			std::unordered_map<gloop::HookType, hookMap>	_hooks = {
				{gloop::HookType::EARLY, {}},
				{gloop::HookType::MIDDLE, {}},
				{gloop::HookType::LAST, {}},
			};
	}; // Stage

	class StageManager {
		public:
			StageManager() = default;
			~StageManager() = default;

			Stage	&get_stage(const gloop::StageType type) noexcept { return _stages[type]; }

		private:
			/* data */
			std::unordered_map<gloop::StageType, Stage>	_stages = {
				{gloop::StageType::INIT, Stage{}},
				{gloop::StageType::LOOP, Stage{}},
				{gloop::StageType::FINAL, Stage{}}
			};

	}; // StageManager

} // gloop