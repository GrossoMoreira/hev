#ifndef _HEV_INCLUDE_LISTENER_HPP_
#define _HEV_INCLUDE_LISTENER_HPP_

#include "include/MetaEvent.h"
#include "include/Listener.h"

namespace hev {

	template <typename T> const MetaEvent<T>& Listener<T>::getMeta() {
		return meta;
	}

	template <typename T> Listener<T>::Listener(std::string name, MetaEvent<T>& meta) :
			meta(meta), name(name) {
		//std::cout << "(( " << name << " @ " << meta.getName() << ".\n";
		meta.addListener(this);
	}

	template <typename T> Listener<T>::~Listener() {
		meta.removeListener(this);
	}

}

#endif // _HEV_INCLUDE_LISTENER_HPP_
