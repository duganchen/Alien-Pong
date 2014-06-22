#include "settings.h"


const int Settings::getParticleCount() const
{
	return 256;
}


const float Settings::getParticleSize() const
{
	return 0.05;
}


const PlanetType Settings::getPlanetType() const
{
	return PlanetType::Mirror;
}


const int Settings::getWidth() const
{
	return 1024;
}


const int Settings::getHeight() const
{
	return 768;
}
