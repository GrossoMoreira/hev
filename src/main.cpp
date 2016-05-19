#include <include/Event.hpp>
#include "include/MetaEvent.hpp"
#include "include/Listener.hpp"

#include <iostream>
#include <unordered_set>


struct BodyMovement : hev::Event<> {
	std::string person;
};

struct Play : hev::Event<> {
	std::string game;
	std::string play;
};

struct BallThrown : hev::Event<Play,BodyMovement> {
	int ballNumber;
	std::string from;
	float velocity[3];
};


struct MovementDetector : hev::Listener<BodyMovement> {
	MovementDetector(hev::MetaEvent<BodyMovement>& m) : Listener("Movement Detector", m) {
	}

	void listen(const BodyMovement& movement) {
		std::cout << movement.person << " has moved." << std::endl;
	}
};

struct GameTracker : hev::Listener<Play> {
	GameTracker (hev::MetaEvent<Play>& p) : Listener("Game Tracker", p) {
	}

	void listen(const Play& play) {
		std::cout << "A " << play.play << " is being made in a game of " << play.game << ".\n";
	}
};

struct BallTracker: hev::Listener<BallThrown> {
	BallTracker(hev::MetaEvent<BallThrown>& b) : Listener("Ball Tracker", b) {
	}

	void listen(const BallThrown& bt) {
		std::cout << "Ball number " << bt.ballNumber << " was thrown from " << bt.from << " with velocity (" << bt.velocity[0] << "," << bt.velocity[1] << "," << bt.velocity[2] << ")\n";
	}
};


int main() {

	// Create an event of type Body Movement

	hev::MetaEvent<BodyMovement> movementEvent("Body movement");
	movementEvent.addField("person", +[](const BodyMovement& m)-> const std::string& {return m.person;});

	// Create an event of type Play

	hev::MetaEvent<Play> playEvent("Play");
	playEvent.addField("game", +[](const Play& p)-> const std::string& {return p.game;});
	
	// Create an event of type Ball Thrown

	hev::MetaEvent<BallThrown> ballThrownEvent("Ball Thrown", playEvent, movementEvent);
	ballThrownEvent.addField("from", +[](const BallThrown& b)-> const std::string& {return b.from;});

	// Create three event listeners

	MovementDetector detector(movementEvent); // This one detects people moving
	GameTracker gameTracker(playEvent);	  // This one sees what is happening in the game 
	BallTracker ballTracker(ballThrownEvent); // This one tracks the movement of the ball

	// Prepare a 'Ball Thrown' event

	BallThrown bt;
	bt.ballNumber = 51;
	bt.from = "left field";
	bt.velocity[0] = 1; bt.velocity[1] = 2; bt.velocity[2] = 3;
	bt.game = "Volleyball";
	bt.play= "service";
	bt.person = "Bob";

	// Throw a ball!

	ballThrownEvent.fire(bt);	


	return 0;
}
