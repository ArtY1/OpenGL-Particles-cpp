#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Particle
{
public:
	Particle(void);
	Particle(float mass, sf::Vector2f pos, sf::Vector2f vel);

	// Set/Get
	float GetMass(void) const;
	void setMass(const float &mass);
	sf::Vector2f GetPos(void) const;
	void SetPos(const sf::Vector2f &pos);
	sf::Vector2f GetVel(void) const;
	float GetSpeed(void) const;
	void SetVel(const sf::Vector2f &vel);

	vector<sf::Vector2f> getForces(void) const;
	sf::Vector2f getTotalForce(void) const;
	void addForce(const sf::Vector2f &force);
	void setForces(const vector<sf::Vector2f> &forces);
	void clearForces(void);

	sf::Vector2f getAcc(void) const;
	void setAcc(const sf::Vector2f &acc);

	void setFreeze(void);
	void setUnfreeze(void);

	bool getFreeze(void);

	//Methods
	void updatePos(const float &dt);


private:
	float m_mass;
	sf::Vector2f m_pos;
	sf::Vector2f m_vel; // v = dx/dt = ( x(t+dt) - x(t) ) / dt

	vector<sf::Vector2f> m_forces; // F = ma
	sf::Vector2f m_acc; // a = F/m = dv/dt = ( v(t+dt) - v(t) ) / dt

	bool m_frozen;
};
