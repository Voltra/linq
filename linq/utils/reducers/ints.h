#ifndef LINQ_INTS_H
#define LINQ_INTS_H

#define thisNamespace linq::utils::reducers::ints

namespace linq{
	namespace utils{
		namespace reducers{
			namespace ints{
				inline int sum(int acc, int elem){ return acc+elem; }
				inline int product(int acc, int elem){ return acc*elem; }
				inline int diff(int acc, int elem){ return acc-elem; }
				inline int div(int acc, int elem){ return acc/elem; }
			}
		};
	};
};

#undef thisNamespace

#endif
