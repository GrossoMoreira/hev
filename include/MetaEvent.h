#ifndef _HEV_META_EVENT_
#define _HEV_META_EVENT_

#include <string>
#include <vector>
#include <iostream>

namespace hev {

	template <typename S> class Listener;

	template <typename S> class MetaEvent {

			/* ----- Field ----- */

			class Field {
					std::string name;

				public:
					Field(std::string name);

					const std::string& getName() const;

					virtual std::string str(const S&) = 0;
			};

			/* ----- FieldImpl ----- */

			template <typename FieldT> class FieldImpl: public Field {
					const FieldT& (*getter)(const S&);
					std::string (*toStr)(const FieldT&);

				public:
					FieldImpl(std::string name,
						const FieldT& (*getter)(const S&),
						std::string (*toStr)(const FieldT&) = 0);

					std::string str(const S&);
			};

			/* ----- Connector ----- */

			struct Connector {
					virtual void propagate(const S& event) = 0;
			};

			/* ----- ConnectorImpl ----- */

			template <typename U> class ConnectorImpl: public Connector {
				private:
					MetaEvent<U>& connectedTo;
				public:
					ConnectorImpl(MetaEvent<U>& connectedTo);
					void propagate(const S&);
			};

			/* ----- MetaEvent ----- */

			std::string name;
			std::vector<Field*> fields;
			std::vector<Connector*> connectors;
			std::vector<Listener<S>*> listeners;

		public:
			typedef typename std::vector<Field*>::const_iterator const_iterator;

			const std::string getName() const;

			template <typename ... Parents> MetaEvent(std::string name, Parents&... p);

			template <typename U> void connectToParent(MetaEvent<U>& parent);

			template <typename T> void addField(std::string name,
							const T& (*getter)(const S&),
							std::string (*toStr)(const T&) = 0);

			void fire(const S& e);

			void addListener(Listener<S>* l);
			void removeListener(Listener<S>* l);

			const_iterator begin() const;
			const_iterator end() const;
	};

}
#endif // _HEV_META_EVENT_
