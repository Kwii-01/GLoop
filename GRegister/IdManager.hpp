#pragma once

#include <set>

namespace g_reg {
      
      class IdManager {
            public:
                  IdManager(const std::size_t max) : _max(max) {
                        for (std::size_t i = 0; i < max; ++i)
                              _unused.insert(_unused.end(), i);
                  }

                  std::size_t use() {
                        if (_unused.empty()) {
                              _unused.insert(_unused.end(), _max);
                              ++_max;
                        }
                        auto it = _unused.begin();
                        std::size_t id = *it;
                        _unused.erase(it);
                        return id;
                  }

                  void  free(const std::size_t id) {
                        if (_unused.count(id) == 0)
                              _unused.insert(_unused.end(), id);
                  }

            private:
                  std::size_t             _max;
                  std::set<std::size_t>   _unused;
      }; // IdManager

} // namespace g_reg
