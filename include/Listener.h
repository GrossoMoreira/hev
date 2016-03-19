#ifndef _HEV_LISTENER_
#define _HEV_LISTENER_

#include "include/MetaEvent.h"

#include <iostream>

namespace hev {
	template <typename T> class Listener {

			MetaEvent<T>& meta;
			std::string name;

		public:
			const MetaEvent<T>& getMeta();

			Listener(std::string name, MetaEvent<T>& meta);

			virtual ~Listener();

			virtual void listen(const T&) = 0;
	};
}

#endif // _HEV_LISTENER_
