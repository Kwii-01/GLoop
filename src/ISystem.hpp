#pragma once

#include <cstdint>

namespace gloop {

	class ISystem {
		public:
			virtual ~ISystem() = default;

			virtual void	init() = 0;
			virtual void	update() = 0;
			virtual void	render() = 0;

			virtual const uint32_t	priority() const noexcept = 0;
	};
};