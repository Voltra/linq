#ifndef LINQ_DOUBLES_H
#define LINQ_DOUBLES_H

#define thisNamespace linq::utils::reducers::doubles

namespace linq{
	namespace utils{
		namespace reducers{
			namespace doubles{
				inline double sum(double acc, double elem){ return acc+elem; }
				inline double product(double acc, double elem){ return acc*elem; }
				inline double diff(double acc, double elem){ return acc-elem; }
				inline double div(double acc, double elem){ return acc/elem; }
			};
		};
	};
};

#undef thisNamespace

#endif
