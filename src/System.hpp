#pragma once

#include <cstdint>

namespace gloop {

	class ISystem {
		public:
			virtual ~ISystem() = default;

			virtual void	start() = 0;
			virtual void	update() = 0;

			virtual const uint32_t	&getPriority() const noexcept = 0;
			virtual void		setPriority(const uint32_t) = 0;

			virtual const int		&getCallrate() const noexcept = 0;
			virtual void		setCallrate(const int) const noexcept = 0;
	};
};