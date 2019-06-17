#pragma once

#include <unordered_map>
#include <map>
#include "GHeaders.hpp"

namespace gloop {

	class Stage {
		public:
			using HookMap = std::multimap<std::size_t, gloop::Hook>;

			Stage() = default;
			~Stage() = default;

			void	add_hook(const std::size_t weight, gloop::SystemHook &hook) { _hooks.insert(std::make_pair(weight, gloop::Hook{hook, std::chrono::system_clock::now()})); }

			void	remove_system_hooks(const std::string &sys) {
				auto elem = std::find_if(_hooks.begin(), _hooks.end(), [sys](const std::pair<std::size_t, gloop::Hook> &h){ return h.second.hook.sys_name == sys; });
				if (elem != _hooks.end())
					_hooks.erase(elem);
			}

			void	clear_hooks() noexcept {
				_hooks.clear();
			}

			HookMap	&get_hookMap() noexcept { return _hooks; }

		private:
			/* data */
			HookMap	_hooks;
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