#ifndef _HEV_INCLUDE_METAEVENT_HPP_
#define _HEV_INCLUDE_METAEVENT_HPP_

#include "include/Event.h"
#include "include/MetaEvent.h"
#include "include/MetaEventConnector.hpp"

#include <utility>

namespace hev {

	template <typename T> std::string toString(const T& v) {
		return std::to_string(v);
	}

	template <> std::string toString(const std::string& s) {
		return s;
	}

	/* ----- Field ----- */

	template <typename S> MetaEvent<S>::Field::Field(std::string name) :
			name(name) {
	}

	template <typename S> const std::string& MetaEvent<S>::Field::getName() const {
		return name;
	}

	/* ----- FieldImpl ----- */

	template <typename S> template <typename FieldT> MetaEvent<S>::FieldImpl<FieldT>::FieldImpl(std::string name, const FieldT& (*getter)(const S&), std::string (*toStr)(const FieldT&)) :
			MetaEvent<S>::Field(name), getter(getter), toStr(toStr) {
	}

	template <typename S> template <typename FieldT> std::string MetaEvent<S>::FieldImpl<FieldT>::str(const S& object) {
		const FieldT& value = getter(object);

		if(toStr)
			return toStr(value);
		else
			return toString(value);
	}

	/* ----- ConnectorImpl ----- */

	template <typename S> template <typename U> MetaEvent<S>::ConnectorImpl<U>::ConnectorImpl(MetaEvent<U>& connectedTo) :
			connectedTo(connectedTo) {
	}

	template <typename S> template <typename U> void MetaEvent<S>::ConnectorImpl<U>::propagate(const S& event) {
		connectedTo.fire(event);
	}

	/* ----- MetaEvent ----- */

	template <typename S> const std::string MetaEvent<S>::getName() const {
		return name;
	}

	template <typename S> template <typename ... Parents> MetaEvent<S>::MetaEvent(std::string name, Parents&... p) :
			name(name) {
		//std::cout << "$$ " << name << "\n";
		S::registerParents(*this, p...);
	}

	template <typename S> template <typename U> void MetaEvent<S>::connectToParent(MetaEvent<U>& parent) {
		//std::cout << getName() << " -> " << parent.getName() << "\n";
		connectors.push_back(new ConnectorImpl<U>(parent));
	}

	template <typename S> template <typename T> void MetaEvent<S>::addField(std::string name,
									const T& (*getter)(const S&),
									std::string (*toStr)(const T&)) {
		//std::cout << "Meta event " << getName() << ": added field " << name << "\n";
		fields.push_back(new FieldImpl<T>(name, getter, toStr));
	}

	template <typename S> void MetaEvent<S>::fire(const S& e) {
		for (auto* l : listeners)
			l->listen(e);

		for (Connector* c : connectors)
			c->propagate(e);
	}

	template <typename S> void MetaEvent<S>::addListener(Listener<S>* l) {
		listeners.push_back(l);
	}

	template <typename S> void MetaEvent<S>::removeListener(Listener<S>* l) {
		for (auto it = listeners.begin(), et = listeners.end(); it != et; ++it) {
			if (*it == l) {
				listeners.erase(it);
				return;
			}
		}
	}

	template <typename S> typename MetaEvent<S>::const_iterator MetaEvent<S>::begin() const {
		return fields.begin();
	}

	template <typename S> typename MetaEvent<S>::const_iterator MetaEvent<S>::end() const {
		return fields.end();
	}

}

#endif // _HEV_INCLUDE_METAEVENT_HPP_
