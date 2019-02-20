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

			void	add_hook(const gloop::HookType, gloop::SystemHook &);

			void	remove_system_hooks(const std::string &);
			void	remove_system_hook_from(const gloop::HookType, const std::string &);

			void	clear_hooks();
			void	clear_hooks(const gloop::HookType);

			hookMap	&get_hookMap(const gloop::HookType);

		private:
			/* data */
			std::unordered_map<gloop::HookType, hookMap>	_hooks = {
				{gloop::HookType::VERY_EARLY, {}},
				{gloop::HookType::EARLY, {}},
				{gloop::HookType::MIDDLE, {}},
				{gloop::HookType::LAST, {}},
				{gloop::HookType::VERY_LAST, {}}
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