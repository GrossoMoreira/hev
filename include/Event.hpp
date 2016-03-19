#ifndef EVENT_FRAMEWORK_INCLUDE_EVENT_HPP_
#define EVENT_FRAMEWORK_INCLUDE_EVENT_HPP_

#include <include/Event.h>
#include "include/MetaEvent.h"

#include <iostream>

namespace hev {

	template <typename ... ParentType> template <typename S> void Event<ParentType...>::registerP(MetaEvent<S>& m) {
	}

	template <typename ... ParentType> template <typename S, typename Last> void Event<ParentType...>::registerP(MetaEvent<S>& m, MetaEvent<Last>& last) {
		m.connectToParent(last);
	}

	template <typename ... ParentType> template <typename S, typename First, typename Second, typename ... Rest> void Event<ParentType...>::registerP(MetaEvent<S>& m, MetaEvent<First>& first, MetaEvent<Second>& second, MetaEvent<Rest>&... rest) {
		registerP(m, first);
		registerP(m, second, rest...);
	}

	template <typename ... ParentType> template <typename S> void Event<ParentType...>::registerParents(MetaEvent<S>& m, MetaEvent<ParentType>&... p) {
		registerP(m, p...);
	}

}

#endif /* EVENT_FRAMEWORK_INCLUDE_EVENT_HPP_ */
