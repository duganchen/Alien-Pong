#include "settings.h"


int Settings::getParticleCount()
{
	return 256;
}


float Settings::getParticleSize()
{
	return 0.05;
}


PlanetType Settings::getPlanetType()
{
	return PlanetType::Mirror;
}


int Settings::getWidth()
{
	return 1024;
}


int Settings::getHeight()
{
	return 768;
}
