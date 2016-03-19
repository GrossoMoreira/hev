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

					virtual void stream(std::ostream& stream, const S& object) = 0;
			};

			/* ----- FieldImpl ----- */

			template <typename FieldT> class FieldImpl: public Field {
					FieldT (*getter)(const S&);

				public:
					FieldImpl(std::string name, FieldT (*getter)(const S&));

					virtual void stream(std::ostream& stream, const S& object);
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

			template <typename T> void addField(std::string name, T (*getter)(const S&));

			void fire(const S& e);

			template <typename T> void registerField(std::string name, const T& v);

			void addListener(Listener<S>* l);
			void removeListener(Listener<S>* l);

			const_iterator begin() const;
			const_iterator end() const;
	};

}
#endif // _HEV_META_EVENT_
