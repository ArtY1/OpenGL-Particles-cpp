#include "Particle.h"

Particle::Particle()
{
	m_mass = 1;
	m_pos = sf::Vector2f(0, 0);
	m_vel = sf::Vector2f(0, 0);
	m_acc = sf::Vector2f(0, 0);

	m_frozen = false;
}

Particle::Particle(float mass, sf::Vector2f pos, sf::Vector2f vel):Particle()
{
	m_mass = mass;
	m_pos = pos;
	m_vel = vel;
}

// Get/Set

void Particle::setMass(const float& mass)
{
	m_mass = mass;
}
float Particle::GetMass() const
{
	return m_mass;
}

void Particle::SetPos(const sf::Vector2f& pos)
{
	m_pos = pos;
}
sf::Vector2f Particle::GetPos() const
{
	return m_pos;
}

void Particle::SetVel(const sf::Vector2f& vel)
{
	m_vel = vel;
}
sf::Vector2f Particle::GetVel() const
{
	return m_vel;
}
float Particle::GetSpeed() const
{
	return sqrt( pow(m_vel.x, 2) + pow(m_vel.y, 2) );
}


void Particle::setAcc(const sf::Vector2f& acc)
{
	m_acc = acc;
}
sf::Vector2f Particle::getAcc() const
{
	return m_acc;
}

void Particle::setForces(const vector<sf::Vector2f>& forces)
{
	m_forces = forces;
}
void Particle::addForce(const sf::Vector2f& force)
{
	m_forces.push_back(force);
}
void Particle::clearForces()
{
	m_forces.clear();
}
vector<sf::Vector2f> Particle::getForces() const
{
	return m_forces;
}
sf::Vector2f Particle::getTotalForce() const
{
	sf::Vector2f _totalForce(0,0);
	for (unsigned i = 0; i < m_forces.size(); ++i)
	{
		_totalForce += m_forces[i];
	}

	return _totalForce;
}

void Particle::setFreeze()
{
	m_frozen = true;
}
void Particle::setUnfreeze()
{
	m_frozen = false;
}

// Methods
void Particle::updatePos(const float& dt)
{
	sf::Vector2f _prevPos = m_pos;

	//Assuming a(t+dt) = a(t) and integrating wrt dt gives v(t+dt) = a(t)*dt + v(t) integrating again gives;
	// x(t+dt) = x(t) + v(t)*dt + 0.5*a(t)*dt*dt
	m_pos = m_pos + m_vel * dt + 0.5f * (getTotalForce() / m_mass) * float(pow(dt, 2));
	m_vel = (m_pos - _prevPos) / dt;
}














