#ifndef ALIENPONG_SETTINGS_H
#define ALIENPONG_SETTINGS_H

enum class PlanetType {Fire, Gas, Mirror,  Sapphire};

class ISettings
{
public:
	virtual int getParticleCount() = 0;
	virtual float getParticleSize() = 0;
	virtual PlanetType getPlanetType() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
};

#endif


class Settings: ISettings
{
public:
	int getParticleCount();
	float getParticleSize();
	PlanetType getPlanetType();
	int getHeight();
	int getWidth();
};
