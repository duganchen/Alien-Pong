#include "gui.h"
#include <QtGui>
#include <SFML/Window.hpp>
#include "game.h"
#include <iostream>

GUI::GUI(QWidget *parent)
        : QMainWindow(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *settingsLayout = new QHBoxLayout();
    QVBoxLayout *radioLayout = new QVBoxLayout();
    resolutions = new QButtonGroup(this);
    bool found = false;
    for (unsigned int i = 0; i < sf::VideoMode::GetModesCount(); ++i)
    {
        int width = sf::VideoMode::GetMode(i).Width;
        int height = sf::VideoMode::GetMode(i).Height;
        int bpp = sf::VideoMode::GetMode(i).BitsPerPixel;
        double aspect = (double)sf::VideoMode::GetMode(i).Width / sf::VideoMode::GetMode(i).Height;
        if ((1.3325 < aspect && aspect < 1.3335 && bpp == 32)
            || (1.20 < aspect && aspect < 1.30))
            {
            QString dimensions = "";
            QTextStream stream(&dimensions);
            stream << width << "x" << height;
            QRadioButton *resolution = new QRadioButton(dimensions);
            radioLayout->addWidget(resolution);
            resolutions->addButton(resolution);
            if (width == 1024)
            {
                resolution->setChecked(true);
                found = true;
            }
            if (width == 640 && found == false)
            {
                resolution->setChecked(true);
            }
        }

    }

    settingsLayout->addLayout(radioLayout);

    QFormLayout *spinLayout = new QFormLayout();
    particleCount = new QSpinBox();
    particleCount->setValue(28);
    particleCount->setMaximum(32768);
    spinLayout->addRow(tr("Particle Count"), particleCount);
    particleSize = new QDoubleSpinBox();
    particleSize->setValue(20);
    particleSize->setMaximum(32768);
    particleSize->setSingleStep(0.005);
    particleSize->setDecimals(3);
    spinLayout->addRow(tr("Particle Size"), particleSize);
    planets = new QComboBox();
    planets->addItem("Mirror");
    planets->addItem("Fire");
    planets->addItem("Gas Giant");
    planets->addItem("Sapphire");
    spinLayout->addRow("Planet", planets);
    settingsLayout->addLayout(spinLayout);
    vLayout->addLayout(settingsLayout);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    instructions = new Instructions();
    QPushButton *btnReadme = new QPushButton("Readme");
    QObject::connect(btnReadme, SIGNAL(clicked()), instructions, SLOT(exec()));
    buttonLayout->addWidget(btnReadme);
    QPushButton *btnDefaults = new QPushButton("Defaults");
    QObject::connect(btnDefaults, SIGNAL(clicked()), this, SLOT(setDefaults()));
    buttonLayout->addWidget(btnDefaults);
    QPushButton *btnPlay = new QPushButton("Play");
    btnPlay->setFocus();
    btnPlay->setDefault(true);
    btnPlay->setAutoDefault(true);
    QObject::connect(btnPlay, SIGNAL(clicked()), this, SLOT(play()));
    buttonLayout->addWidget(btnPlay);
    vLayout->addLayout(buttonLayout);
    QWidget *centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    centralWidget->setLayout(vLayout);
    setDefaults();

    setWindowTitle("Alien Pong");
}

void GUI::setDefaults()
{
    particleCount->setValue(256);
    particleSize->setValue(0.05);
    // and the defeault resolution
}

void GUI::play()
{
    QString text = resolutions->checkedButton()->text();
    Game game;
    game.play(width(text), height(text), particleCount->value(), particleSize->value(), planets->currentIndex());

    // This is a hack to get around the fact that it crashes when you try to launch another
    // game.
    exit(0);
}


unsigned int GUI::width(const QString &dimensions) const
{
    return dimensions.left(dimensions.indexOf("x")).toInt();
}

unsigned int GUI::height(const QString &dimensions) const
{
    return dimensions.right(dimensions.size() - dimensions.indexOf("x") - 1).toInt();
}

GUI::~GUI()
{
    delete instructions;
}

