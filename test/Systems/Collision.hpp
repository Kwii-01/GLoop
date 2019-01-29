#pragma once

#include "../../src/System.hpp"

class Collision : public gloop::ISystem
{
public:
	Collision():_priority(3), _callRate(1000), _startTime(std::chrono::system_clock::now()) {};
	~Collision() {};

	void	start() {};
	void	update() {

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _startTime).count() > _callRate) {
			std::cout << "updating Collision system" <<  std::endl;
			_startTime = std::chrono::system_clock::now();
		}
		// utiliser le register pour modifier valeur de l'EC
	}
	const uint32_t	&getPriority() const noexcept { return _priority; }
	void		setPriority(const uint32_t priority) noexcept { _priority = priority; }
	const int		&getCallrate() const noexcept { return _callRate; }
	void		setCallrate(const int callRate) noexcept { _callRate = callRate; }

private:
	uint32_t	_priority;
	int			_callRate;
	std::chrono::time_point<std::chrono::system_clock> _startTime;
};