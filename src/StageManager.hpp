#pragma once

#include <unordered_map>
#include <map>
#include "GHeaders.hpp"

namespace gloop {

	class Stage {
		public:
			using HookMap = std::multimap<std::size_t, gloop::HookCallRate>;

			Stage() = default;
			~Stage() = default;

			/**
			 * add_hook
			 * @deprecated this function add a SystemHook to the HookType chosen (early, middle, last)
			 * @param1 type of the hook
			 * @param2 SystemHook to add
			*/
			void	add_hook(gloop::SystemHook &hook) { _hooks.insert(std::make_pair(hook.weight_p, gloop::HookCallRate{hook, std::chrono::system_clock::now()})); }

			/**
			 * remove_system_hooks
			 * @deprecated this function remove a system from the stage
			 * @param1 system name
			*/
			void	remove_system_hooks(const std::string &sys) {
				auto elem = std::find_if(_hooks.begin(), _hooks.end(), [sys](const std::pair<std::size_t, gloop::HookCallRate> &h){ return h.second.hook.sys_name == sys; });
				if (elem != _hooks.end())
					_hooks.erase(elem);
			}

			/**
			 * clear_hooks
			 * @deprecated clear all the hooks of the stage
			*/
			void	clear_hooks() noexcept {
				_hooks.clear();
			}

			/**
			 * get_hookMap
			 * @deprecated return the hookMap chosen
			 * @param1 type of the hook to return
			 * @return hookmap chosen
			*/
			HookMap	&get_hookMap() noexcept { return _hooks; }

		private:
			/* data */
			HookMap	_hooks;
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
[type]
		private:
			/* data */
			std::unordered_map<gloop::StageType, Stage>	_stages = {
				{gloop::StageType::INIT, Stage{}},
				{gloop::StageType::LOOP, Stage{}},
				{gloop::StageType::FINAL, Stage{}}
			};

	}; // StageManager

} // gloop