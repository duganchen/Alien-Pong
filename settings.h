#ifndef ALIENPONG_SETTINGS_H
#define ALIENPONG_SETTINGS_H

enum class PlanetType {Fire, Gas, Mirror,  Sapphire};

class ISettings
{
public:
	virtual const int getParticleCount() const = 0;
	virtual const float getParticleSize() const = 0;
	virtual const PlanetType getPlanetType() const = 0;
	virtual const int getWidth() const = 0;
	virtual const int getHeight() const = 0;
};


class Settings: public ISettings
{
public:
	int const getParticleCount() const;
	float const getParticleSize() const;
	const PlanetType getPlanetType() const;
	const int getHeight() const;
	const int getWidth() const;
};


#endif
