#include <include/Event.hpp>
#include "include/MetaEvent.hpp"
#include "include/Listener.hpp"

#include <iostream>
#include <unordered_set>

struct Pedro: hev::Event<> {
		int skill;

		Pedro() :
				skill(1337) {
		}
};

struct Joana: hev::Event<Pedro> {
		int power;

		Joana() :
				power(24) {
		}
};

struct Rosendo: hev::Event<Pedro, Joana> {

};

struct OuvidoJoana: hev::Listener<Joana> {
		OuvidoJoana(hev::MetaEvent<Joana>& j) :
				Listener("Ouvido", j) {
		}

		void listen(const Joana& j) {
			std::cout << "OMG! Joana has happened!\n";

			for (auto f : getMeta()) {
				f->stream(std::cout, j);
			}
		}
};

struct OuvidoPedro: hev::Listener<Pedro> {
		OuvidoPedro(hev::MetaEvent<Pedro>& p) :
				Listener("Pedro", p) {
		}

		void listen(const Pedro& j) {
			std::cout << "OMG! Joana has happened!\n";

			for (auto f : getMeta()) {
				f->stream(std::cout, j);
			}
		}
};

int main() {

	auto p = hev::MetaEvent<Pedro>("Pedro");
	p.addField("skill", +[](const Pedro& p)->int {return p.skill;});

	hev::MetaEvent<Joana> j = hev::MetaEvent<Joana>("Joana", p);
	j.addField("power", +[](const Joana& j)->int { return j.power;});

	hev::MetaEvent<Rosendo>("Rosendo", p, j);

	OuvidoJoana ouvidoDaJoana(j);
	OuvidoPedro ouvidoDoPedro(p);

	j.fire(Joana());

	return 0;
}
