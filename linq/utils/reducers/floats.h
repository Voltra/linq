#ifndef LINQ_FLOATS_H
#define LINQ_FLOATS_H

#define thisNamespace linq::utils::reducers::floats

namespace linq{
	namespace utils{
		namespace reducers{
			namespace floats{
				inline float sum(float acc, float elem){ return acc+elem; }
				inline float product(float acc, float elem){ return acc*elem; }
				inline float diff(float acc, float elem){ return acc-elem; }
				inline float div(float acc, float elem){ return acc/elem; }
			};
		};
	};
};

#undef thisNamespace

#endif
