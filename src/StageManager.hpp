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

			/**
			 * add_hook
			 * @deprecated this function add a SystemHook to the HookType chosen (early, middle, last)
			 * @param1 type of the hook
			 * @param2 SystemHook to add
			*/
			void	add_hook(const gloop::HookType type, gloop::SystemHook &hook) { _hooks[type].insert(std::make_pair(hook.weight_p, gloop::HookCallRate{hook, std::chrono::system_clock::now()})); }

			/**
			 * remove_system_hooks
			 * @deprecated this function remove a system from the stage
			 * @param1 system name
			*/
			void	remove_system_hooks(const std::string &sys) {
				for(auto&& hooks : _hooks)
					remove_system_hook_from(hooks.first, sys);
			}

			/**
			 * remove_system_hook_from
			 * @deprecated this function remove a hook of a system
			 * @param1 hooktype to remove
			 * @param2 system name
			*/
			void	remove_system_hook_from(const gloop::HookType type, const std::string &sys) {
				auto elem = std::find_if(_hooks[type].begin(), _hooks[type].end(), [sys](const std::pair<gloop::guint, gloop::HookCallRate> &h){ return h.second.hook.sys_name == sys; });
				if (elem != _hooks[type].end())
					_hooks[type].erase(elem);
			}

			/**
			 * clear_hooks
			 * @deprecated clear all the hooks of the stage
			*/
			void	clear_hooks() noexcept {
				for(auto&& hooks : _hooks)
					clear_hooks(hooks.first);
			}

			/**
			 * clear_hooks
			 * @deprecated clear the hook chosen of the stage
			 * @param1 hooktype to clear
			*/
			void	clear_hooks(const gloop::HookType type) noexcept { _hooks[type].clear(); }

			/**
			 * get_hookMap
			 * @deprecated return the hookMap chosen
			 * @param1 type of the hook to return
			 * @return hookmap chosen
			*/
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

			/**
			 * get_stage
			 * @deprecated return the stage chosen
			 * @param1 type of the stage to return
			 * @return stage chosen
			*/
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