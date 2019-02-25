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

namespace tools {

	template<typename Fcnt>
	struct	load_s {
		std::string	lib_name;
		Fcnt		function;
	};

	class Loader {
		public:
			Loader() {}

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
				open_lib(libname);
				#else
				open_lib(libname, flag);
				#endif

				#ifdef _WIN32
				Fcnt function = (Fcnt)GetProcAddress(_hdlrs[libname], name.c_str());
				if (!function) {
					FreeLibrary(_hdlrs[libname]);
					throw std::exception();
				}
				#else
				Fcnt function = (Fcnt)dlsym(_hdlrs[libname], name.c_str());
				if (!function || dlerror()) {
					dlclose(_hdlrs[libname]);
					throw std::exception();
				}
				#endif
				
				return load_s<Fcnt>{libname, function};
			}

			void	unload(const std::string &libname) {
				if (_hdlrs.find(libname) != _hdlrs.end()) {
					#ifdef _WIN32
						FreeLibrary(_hdlrs[libname]);
					#else
						dlclose(_hdlrs[libname]);
					#endif
					_hdlrs.erase(libname);
				}
			}

		private:
			
			#ifdef _WIN32
			void	open_lib(const std::string &libname)
			#else
			void	open_lib(const std::string &libname, const int &flag = RTLD_LAZY)
			#endif
			{
				if (_hdlrs.find(libname) != _hdlrs.end())
					return;

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

				_hdlrs[libname] = hdlr;
			}

			#ifdef _WIN32
				std::unordered_map<std::string, HINSTANCE>	_hdlrs;
			#else
				std::unordered_map<std::string, void *>	_hdlrs;
			#endif
	};
};