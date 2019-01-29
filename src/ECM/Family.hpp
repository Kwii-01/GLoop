#pragma once

#include <cstdint>

namespace ecm {

	using family_type = uint32_t;
	
	class Family {
		public:
			template<typename>
			static inline family_type	type() {
				static family_type typeId{initFamilyType()};
				return typeId;
			}
		private:
			static inline family_type	initFamilyType() {
				static family_type	type{0};
				return type++;
			}
	};

};