#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "ECM/Register.hpp"

ecm::Register regist;

namespace gloop {

	class ISystem {
		public:
			virtual ~ISystem() = default;

			virtual void	start() = 0;
			virtual void	update() = 0;

			virtual const uint32_t	&getPriority() const noexcept = 0;
			virtual void		setPriority(const uint32_t) noexcept = 0;

			virtual const int		&getCallrate() const noexcept = 0;
			virtual void		setCallrate(const int) noexcept = 0;
	};
};