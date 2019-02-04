/*
** EPITECH PROJECT, 2018
** Zia
** File description:
** Loader
*/

#pragma once

#include <exception>
#include <unordered_map>
#include <string>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

#include "IdManager.hpp"

namespace tools {

	using	load_id = std::size_t;

	template<typename Fcnt>
	struct	load_s {
		load_id	id;
		Fcnt		function;
	};

	class Loader {
		public:
			Loader() : _idManager() {}

			~Loader() {
					for(auto&& elem : _hdlrs) {
						#ifdef _WIN32
							FreeLibrary(elem.second);
						#else
							dlclose(elem.second);
						#endif
					}
			}

		public:
			#ifdef _WIN32
			template<typename Fcnt>
			load_s<Fcnt>	load(const std::string &libname, const std::string &name)
			#else
			template<typename Fcnt>
			load_s<Fcnt>	load(const std::string &libname, const std::string &name, const int &flag = RTLD_LAZY)
			#endif
			{
				#ifdef _WIN32

				HINSTANCE	hdlr;
				hdlr = LoadLibrary(libname.c_str());
				if (!hdlr)
					throw std::exception();

				#else

				void	*hdlr;
				hdlr = dlopen(libname.c_str(), flag);
				if (!(hdlr) || dlerror())
					throw std::exception();

				#endif

				load_id id = _idManager.generate();
				_hdlrs[id] = hdlr;

				#ifdef _WIN32

				Fcnt function = (Fcnt)GetProcAddress(hdlr, name.c_str());
				if (!function) {
					FreeLibrary(hdlr);
					throw std::exception();
				}
				
				#else
				
				Fcnt function = (Fcnt)dlsym(hdlr, name.c_str());
				if (!function || dlerror()) {
					dlclose(hdlr);
					throw std::exception();
				}
				
				#endif
				
				return load_s<Fcnt>{id, function};
			}

			void	unload(const load_id id) {
				if (_hdlrs.find(id) != _hdlrs.end()) {
					#ifdef _WIN32
						FreeLibrary(_hdlrs[id]);
					#else
						dlclose(_hdlrs[id]);
					#endif
					_hdlrs.erase(id);
				}
			}

		private:
			IdManager					_idManager;
			#ifdef _WIN32
				std::unordered_map<load_id, HINSTANCE>	_hdlrs;
			#else
				std::unordered_map<load_id, void *>	_hdlrs;
			#endif
	};
};