#include "paddle.h"
#include "ball.h"
#include "game.h"
#include "audio.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <FTGL/ftgl.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <sstream>
#include <ctime>
#include <cstdlib>


void Game::play(int width, int height, int particleCount, float particleSize, int planetType)
{
	srand((unsigned)time(0));

	FTGLPixmapFont font("resources/BlackHoleBB.ttf");
	font.FaceSize(72);

	sf::Clock clock;

	// We begin by creating the planet
	GLUquadricObj *planet = gluNewQuadric();
	// Create Smooth Normals (NEW)
	gluQuadricNormals(planet, GLU_SMOOTH);
	// Create Texture Coords (NEW)
	gluQuadricTexture(planet, GL_TRUE);

	float bottomWallHeight;
	float topWallHeight;

	int leftScore = 0;
	int rightScore = 0;

	float planetAngle = 0;
	const float ARENA_TOP = 1;
	const float ARENA_BOTTOM = -1;
	const float ARENA_LEFT = 0.1f;
	const float ARENA_RIGHT = 2.9f;
	const GLuint TEXTURE_COUNT = 5;
	const int TEXTURE_NEBULA = 0;
	const int TEXTURE_MOON = 1;
	const int TEXTURE_FIREBALL = 2;
	const int TEXTURE_BALL = 3;
	const int TEXTURE_GAS = 4;


	const float ARENA_LEVEL = 3;
	const float SPRITE_WIDTH = 0.1f;


	GLuint textures[TEXTURE_COUNT];


	// Display lists
	static const int DISPLAY_LIST_COUNT = 5;
	int background;
	int cube;
	int planetIndex;
	int arena;

	Paddle leftPaddle(0, 0.5f);;
	Paddle rightPaddle(2.9f, 0.5f);

	Ball ball;

	sf::Image images[TEXTURE_COUNT];

	bottomWallHeight = -1;
	topWallHeight = 1;

	sf::RenderWindow app;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;
	app.create(sf::VideoMode(width, height, 32), "Alien Pong", sf::Style::Fullscreen, settings);



	glGenTextures(TEXTURE_COUNT, textures);
	if (!images[TEXTURE_NEBULA].loadFromFile("resources/bg.jpg"))
	{
		std::cout << "Unable to load bg.jpg" << std::endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_NEBULA]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, images[TEXTURE_NEBULA].getSize().x, images[TEXTURE_NEBULA].getSize().y,
			GL_RGBA, GL_UNSIGNED_BYTE, images[TEXTURE_NEBULA].getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (!images[TEXTURE_MOON].loadFromFile("resources/sapphire.jpg"))
	{
		std::cout << "Unable to load Moon.jpg" << std::endl;
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_MOON]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, images[TEXTURE_MOON].getSize().x, images[TEXTURE_MOON].getSize().y,
			GL_RGBA, GL_UNSIGNED_BYTE, images[TEXTURE_MOON].getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (!images[TEXTURE_FIREBALL].loadFromFile("resources/fireball.jpg"))
	{
		std::cout << "Unable to load fireball.jpg" << std::endl;
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FIREBALL]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, images[TEXTURE_FIREBALL].getSize().x, images[TEXTURE_FIREBALL].getSize().y,
			GL_RGBA, GL_UNSIGNED_BYTE, images[TEXTURE_FIREBALL].getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


	if (!images[TEXTURE_BALL].loadFromFile("resources/ball.jpg"))
	{
		std::cout << "Unable to load ball.jpg" << std::endl;
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BALL]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, images[TEXTURE_BALL].getSize().x, images[TEXTURE_BALL].getSize().y,
			GL_RGBA, GL_UNSIGNED_BYTE, images[TEXTURE_BALL].getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (!images[TEXTURE_GAS].loadFromFile("resources/gasgiant.jpg"))
	{
		std::cout << "Unable to load resources/gasgiant.jpg" << std::endl;
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_GAS]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, images[TEXTURE_GAS].getSize().x, images[TEXTURE_GAS].getSize().y,
			GL_RGBA, GL_UNSIGNED_BYTE, images[TEXTURE_GAS].getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	Audio audio;

	if (!audio.loadBounce())
	{
		std::cout << "Unable to load resources/Bounce.ogg" << std::endl;
		return;
	}

	if (!audio.loadWhoosh())
	{
		std::cout << "Unable to load resources/AI_FIRE2.ogg" << std::endl;
		return;
	}

	if (!audio.loadBGM())
	{
		std::cout << "Unable to load resources/AI_FIRE2.ogg" << std::endl;
		return;
	}

	audio.playBGM();

	// Begin contents of initGL

	// Enable Smooth Shading
	glShadeModel(GL_SMOOTH);
	// Black Background
	glClearColor(0.0F, 0.0F, 0.0F, 0.5F);
	// Depth Buffer Setup
	glClearDepth(1.0F);
	// Enables Depth Testing
	glEnable(GL_DEPTH_TEST);
	// The Type Of Depth Testing To Do
	glDepthFunc(GL_LEQUAL);
	// Really Nice Perspective Calculations
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0F, (width / (float)height), 0.1F, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.5f, 0, -6);


	glEnable(GL_CULL_FACE); // Enable Culling
	glCullFace(GL_BACK);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);

	glEnable(GL_LINE_SMOOTH);
	//   glEnable(GL_POINT_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_NORMALIZE);

	// Here we initialize the particle trail
	// For the particle trail
	const int DIMENSION_COUNT = 3;
	const int COMPONENT_COUNT = 4;
	const float DEAD = -1;
	const int DEPTH = 2;

	float particleLives[particleCount];
	float particleVertices[particleCount * 4][DIMENSION_COUNT];
	float particleVelocities[particleCount][DIMENSION_COUNT];
	float particleTextures[particleCount * 4][2];
	GLfloat particleColors[particleCount * 4][COMPONENT_COUNT];


	for (int particleIndex = 0; particleIndex < particleCount; particleIndex++)
	{
		// Particles are already dead
		particleLives[particleIndex] = DEAD;

		for (int j = 0; j < 4; j++)
		{
			// They appear at the same depth as the ball
			particleVertices[particleIndex * 4 + j][DEPTH] = ARENA_LEVEL;

			for (int color = 0; color < COMPONENT_COUNT; color++)
			{
				particleColors[particleIndex * 4 + j][color] = 1;
			}

		}

		// And they're not going anywhere.
		particleVelocities[particleIndex][0] = 0;
		particleVelocities[particleIndex][1] = 0;
		particleVelocities[particleIndex][2] = 0;

		// Texture coordinates are the same all the time.
		particleTextures[particleIndex * 4][0] = 0.0f;
		particleTextures[particleIndex * 4][1] = 1.0f;
		particleTextures[particleIndex * 4 + 1][0] = 1.0f;
		particleTextures[particleIndex * 4 + 1][1] = 1.0f;
		particleTextures[particleIndex * 4 + 2][0] = 1.0f;
		particleTextures[particleIndex * 4 + 2][1] = 0.0f;
		particleTextures[particleIndex * 4 + 3][0] = 0.0f;
		particleTextures[particleIndex * 4 + 3][1] = 0.0f;
	}

	glPointSize(particleSize);

	// buildLists();

	// Begin contents of BuildLists

	background = glGenLists(DISPLAY_LIST_COUNT);

	glNewList(background, GL_COMPILE);

	// Clear Screen And Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_NEBULA]);


	// Put in the lights

	float lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1 };
	float lightDiffuse[] = { 1, 1, 1, 1 };
	float lightPosition[] = { 0, 0, 2, 1 };
	float specular[] = { 1, 1, 1, 1 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);


	glDisable(GL_BLEND);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	// Top Right
	glTexCoord2f(1, 1);
	glVertex3f(7.6f, 4.58f, -5);
	// Top Left
	glTexCoord2f(0, 1);
	glVertex3f(-4.6f, 4.58f, -5);
	// Bottom Left
	glTexCoord2f(0, 0);
	glVertex3f(-4.6f, -4.57f, -5);
	// Bottom Right
	glTexCoord2f(1, 0);
	glVertex3f(7.6f, -4.57f, -5);
	// Done Drawing The Quad
	glEnd();


	// And we prepare to do the next thing
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glEnable(GL_LIGHT1);


	float specRef[] = { 1, 1, 1, 1 };
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specRef);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glPushMatrix();
	// Center it

	glTranslatef(1.5f, 0, 0);

	glEndList();

	planetIndex = background + 1;
	glNewList(planetIndex, GL_COMPILE);
	// And now we draw the planet
	glTranslatef(1, 0, 0);

	glEnable(GL_TEXTURE_GEN_S);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	gluSphere(planet, 1.3f, 128, 128);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	// End planet drawing code
	glEndList();

	cube = planetIndex + 1;
	glNewList(cube, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_MOON]);
	// Draw a cube
	glColor4f(1, 1, 1, 0.5f);
	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.2f,  0.2f);
	glTexCoord2f(0.2f, 0.0f); glVertex3f( 0.2f, -0.2f,  0.2f);
	glTexCoord2f(0.2f, 0.2f); glVertex3f( 0.2f,  0.2f,  0.2f);
	glTexCoord2f(0.0f, 0.2f); glVertex3f(-0.2f,  0.2f,  0.2f);
	// Back Face
	glNormal3f( 0.0f, 0.0f,-0.5f);
	glTexCoord2f(0.2f, 0.0f); glVertex3f(-0.2f, -0.2f, -0.2f);
	glTexCoord2f(0.2f, 0.2f); glVertex3f(-0.2f,  0.2f, -0.2f);
	glTexCoord2f(0.0f, 0.2f); glVertex3f( 0.2f,  0.2f, -0.2f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.2f, -0.2f, -0.2f);
	// Top Face
	glNormal3f( 0.0f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 0.2f); glVertex3f(-0.2f,  0.2f, -0.2f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f,  0.2f,  0.2f);
	glTexCoord2f(0.2f, 0.0f); glVertex3f( 0.2f,  0.2f,  0.2f);
	glTexCoord2f(0.2f, 0.2f); glVertex3f( 0.2f,  0.2f, -0.2f);
	// Bottom Face
	glNormal3f( 0.0f,-0.5f, 0.0f);
	glTexCoord2f(0.2f, 0.2f); glVertex3f(-0.2f, -0.2f, -0.2f);
	glTexCoord2f(0.0f, 0.2f); glVertex3f( 0.2f, -0.2f, -0.2f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.2f, -0.2f,  0.2f);
	glTexCoord2f(0.2f, 0.0f); glVertex3f(-0.2f, -0.2f,  0.2f);
	// Right Face
	glNormal3f( 0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.2f, 0.0f); glVertex3f( 0.2f, -0.2f, -0.2f);
	glTexCoord2f(0.2f, 0.2f); glVertex3f( 0.2f,  0.2f, -0.2f);
	glTexCoord2f(0.0f, 0.2f); glVertex3f( 0.2f,  0.2f,  0.2f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.2f, -0.2f,  0.2f);
	// Left Face
	glNormal3f(-0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.2f, -0.2f);
	glTexCoord2f(0.2f, 0.0f); glVertex3f(-0.2f, -0.2f,  0.2f);
	glTexCoord2f(0.2f, 0.2f); glVertex3f(-0.2f,  0.2f,  0.2f);
	glTexCoord2f(0.0f, 0.2f); glVertex3f(-0.2f,  0.2f, -0.2f);


	glEnd();
	glEndList();

	arena = cube + 1;
	glNewList(arena, GL_COMPILE);

	// A nice view of the arena
	glRotatef(-5, 1, 0, 0);
	glTranslatef(0, -0.1f, 0);

	// Everything that needs to be texture now has been.
	glDisable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the arena
	glBegin(GL_LINES);

	glColor4f(1, 0, 1, 1);
	glVertex3f(ARENA_LEFT, ARENA_TOP, ARENA_LEVEL);
	glVertex3f(ARENA_RIGHT, ARENA_TOP, ARENA_LEVEL);
	glVertex3f(ARENA_LEFT, ARENA_BOTTOM, ARENA_LEVEL);
	glVertex3f(ARENA_RIGHT, ARENA_BOTTOM, ARENA_LEVEL);

	glColor4f(1, 0, 1, 0.3f);

	for (float x = ARENA_LEFT; x < ARENA_RIGHT + SPRITE_WIDTH / 2; x += SPRITE_WIDTH)
	{
		glVertex3f(x, ARENA_TOP, 3);
		glVertex3f(x, ARENA_BOTTOM, 3);
	}

	for (float y = ARENA_BOTTOM + SPRITE_WIDTH; y < ARENA_TOP - SPRITE_WIDTH / 2; y += SPRITE_WIDTH)
	{
		glVertex3f(ARENA_LEFT, y, 3);
		glVertex3f(ARENA_RIGHT, y, 3);
	}

	glEnd();
	glEndList();

	// End contents of BuildLists




	// End contents of initGL

	float frameTime = 0;


	while (app.isOpen())
	{

		frameTime = clock.restart().asSeconds();


		//    app.Draw(text);
		sf::Event event;
		while (app.pollEvent(event))
		{
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				app.close();
				return;
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			leftPaddle.pushDown(frameTime);
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		{
			leftPaddle.pushUp(frameTime);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			rightPaddle.pushDown(frameTime);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			rightPaddle.pushUp(frameTime);
		}


		glCallList(background);


		// Let's have a cool orbiting planet

		// Rotate it
		glRotatef(planetAngle, 0, 0, 1);
		planetAngle = planetAngle + 30 * frameTime;

		switch (planetType)
		{
			case FIRE:
				glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BALL]);
				break;
			case GAS:
				glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_GAS]);
				break;
			case SAPPHIRE:
				glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_MOON]);
				break;
			default:
				break;

		}

		glCallList(planetIndex);



		glPushMatrix();

		glRotatef(2 * planetAngle, 0, 1, 0);
		glTranslatef(0, 0, 2);
		glRotatef(4 * planetAngle, 1, 0, 0);


		glCallList(cube);

		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
		glDisable(GL_LIGHTING);

		glPopMatrix();


		glPopMatrix();


		// The background is drawn. The rest is tilted.

		glPushMatrix();

		glCallList(arena);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BALL]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		ball.draw();

		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);

		leftPaddle.draw();
		rightPaddle.draw();

		if (ball.top() > topWallHeight)
		{
			audio.playBounce();
			ball.bounceVertically();
		}

		if (ball.bottom() <= bottomWallHeight)
		{
			audio.playBounce();
			ball.bounceVertically();
		}

		if (ball.left() < leftPaddle.right() || ball.left() + SPRITE_WIDTH > rightPaddle.left())
		{
			if (ball.isLeftBound() && ball.bottom() < leftPaddle.top() && ball.top() > leftPaddle.bottom())
			{
				audio.playBounce();
				ball.bounceHorizontally();
			}
			else if (ball.isRightBound() && ball.bottom() < rightPaddle.top() && ball.top() > rightPaddle.bottom())
			{
				audio.playBounce();
				ball.bounceHorizontally();
			}
			else
			{
				if (ball.isLeftBound())
				{
					rightScore++;
				}
				else
				{
					leftScore++;
				}
				audio.playWhoosh();
				ball.moveToCenter();
			}
		}

		ball.updateFrame(frameTime);

		// And here we draw the particle trail

		for (int i = 0; i < particleCount; i++)
		{
			if (particleLives[i] <= 0)
			{

				float centerX = ball.left() + ((float)rand() / (float) RAND_MAX) * SPRITE_WIDTH;
                float centerY = ball.top() - ((float)rand() / (float) RAND_MAX) * SPRITE_WIDTH;
                particleLives[i] = 1.0f - ((float)rand() / (float) RAND_MAX);
                particleVelocities[i][0] = ((float)rand() / (float) RAND_MAX) - 0.5f;
                particleVelocities[i][1] = ((float)rand() / (float) RAND_MAX) - 0.5f;

				particleVertices[i * 4][0] = centerX - particleSize;
				particleVertices[i * 4][1] = centerY - particleSize;
				particleVertices[i * 4 + 1][0] = centerX + particleSize;
				particleVertices[i * 4 + 1][1] = centerY - particleSize;
				particleVertices[i * 4 + 2][0] = centerX + particleSize;
				particleVertices[i * 4 + 2][1] = centerY + particleSize;
				particleVertices[i * 4 + 3][0] = centerX - particleSize;
				particleVertices[i * 4 + 3][1] = centerY + particleSize;

				for (int j = 0; j < 4; j++)
				{
					particleColors[i * 4 + j][3] = particleLives[i];
				}

			}
			else
			{
				float decrease = frameTime;

				particleLives[i] -= decrease;

				for (int j = 0; j < 4; j++)
				{
					particleVertices[i * 4 + j][0] += particleVelocities[i][0] *frameTime;
					particleVertices[i * 4 + j][1] += particleVelocities[i][1] * frameTime;

					particleColors[i * 4 + j][3] -= decrease;
				}

			}
		}


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FIREBALL]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glDisable(GL_DEPTH_TEST);

		glVertexPointer(3, GL_FLOAT, 0, particleVertices);
		glColorPointer(4, GL_FLOAT, 0, particleColors);
		glTexCoordPointer(2, GL_FLOAT, 0, particleTextures);
		glDrawArrays(GL_QUADS, 0, particleCount * 4);

		glEnable(GL_DEPTH_TEST);
		glPopMatrix();


		std::ostringstream s;
		s << "Player 1: " << leftScore << "   Player 2: " << rightScore;

		font.Render(s.str().c_str());
		app.display();



		// End contents of loop


	}

	glDeleteTextures(TEXTURE_COUNT, textures);
	audio.stopBGM();
}



