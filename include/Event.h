#ifndef _HEV_EVENT_
#define _HEV_EVENT_

#include "include/MetaEvent.h"

#include <string>
#include <vector>
#include <iostream>

namespace hev {
	template <typename ...ParentType> class Event: virtual public ParentType... {
		private:
			template <typename S> static void registerP(MetaEvent<S>&);
			template <typename S, typename Last> static void registerP(MetaEvent<S>&, MetaEvent<Last>&);
			template <typename S, typename First, typename Second, typename ... Rest> static void registerP(MetaEvent<S>&, MetaEvent<First>&, MetaEvent<Second>&, MetaEvent<Rest>&...);


		public:
			template <typename S> static void registerParents(MetaEvent<S>& m, MetaEvent<ParentType>&... p);

	};
}

#endif //_HEV_EVENT_
