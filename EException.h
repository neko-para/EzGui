#ifndef _E_EXCEPTION_H_
#define _E_EXCEPTION_H_

#include <exception>

namespace Eg {

	namespace Exceptions {

		struct Exception : public std::exception {};

		struct AppAlreadyConstruct : public Exception {
			virtual const char* what() const noexcept {
				return "EApp: app already construct";
			}
		};

	}

}

#endif