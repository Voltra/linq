#ifndef LINQ_STRING_H
#define LINQ_STRING_H

#include <string>

#define thisNamespace linq::utils::reducers::strings

namespace linq{
	namespace utils{
		namespace reducers{
			namespace strings{
				inline std::string concat(std::string acc, std::string elem){ return acc+elem; }
			};
		};
	};
};

#undef thisNamespace

#endif
