#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>

/*template <typename Head, typename Tail...> class ChildOf : Head {
	virtual void prepare(Head& e) = 0;
};*/

class IEvent {
	public:
		virtual void fire() = 0;
};

template <typename EventType, typename Parents...> class Event : IEvent, EventType, Parents... {
	private:
		Event* parents[];

	public:
		Event(Parents... p) {
			for(Event* e : p) {
				parents[i++] = e;
			}
		}

		virtual void fire() {
			prepare(static_cast<EventType*>(this));

			for(Listener* l : listeners)
				l->handle(static_cast<EventType*>(this));
		}
};

template <typename EventType> class Listener {
	private:
		std::vector<Event<EventType>*> listening;

	public:
		void handle(timeType time, EventType*);
};

class Hierarchy {
	private:
		std::unordered_map<std::string, Event*> nameMap;

	public:
		typedef std::unordered_map<std::string, Event*>::iterator iterator;
}


class Pai : public Event<Pai> {
	virtual void setup(Pai&);
};

class Mae : public Event<Mae> {
	public:
		int m;

		virtual void setup(Mae&);
};

class Pedro : Event<Pai,Mae> {
	int power = 0;

}
