/*
** EPITECH PROJECT, 2018
** Zia
** File description:
** IdManager
*/

#include <vector>
#include <algorithm>

namespace tools {

	class IdManager final {
		public:
			IdManager() = default;
			~IdManager() = default;

			std::size_t	generate() {
				std::size_t	id = 1;

				for(auto&& elem : Ids) {
					if (id != elem)
						break;
					id++;
				}
				Ids.push_back(id);
				std::sort(Ids.begin(), Ids.end());
				return id;
			}

			void		erase(std::size_t id) {
				Ids.erase(std::find(Ids.begin(), Ids.end(), id));
			}

		private:
			std::vector<std::size_t>	Ids;
	};
};