#pragma once

#include "MovementSystem.hpp"

class PlayerCreator
{
public:
	PlayerCreator() {
		_hookType = gloop::HookType::EARLY;
		_stageType = gloop::StageType::INIT;
		_info.sys_name = "PlayerCreator";
		_info.weight_p = 3;
		_info.callrate = 1000;
		_info.threadable = true;
		_info.callback = [this](ecm::Register &reg, gloop::GLoop &gloop) {
			ecm::entity_type player = reg.create();
			reg.construct<Movement>(player, 2, 0);

			return gloop::HookStatus::OK;
		};
	};

	~PlayerCreator() {};

private:
	gloop::SystemHook	_info;
	gloop::HookType		_hookType;
	gloop::StageType	_stageType;
	
};