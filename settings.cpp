#include "settings.h"
#include "ui_settings.h"
#include <QFont>
#include <QObject>
#include <QGridLayout>
#include <QSlider>
#include <QPalette>
#include <sstream>

#define MIN_RAM 80
#define TERMINATE 98

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    // Style the font
    ui->title->setAlignment(Qt::AlignCenter);
    QFont titleFont = ui->title->font();
    titleFont.setBold(true);
    titleFont.setPointSize(16);
    ui->title->setFont(titleFont);

    // style the slider & display grid.
    QGridLayout *settingsGrid = qobject_cast<QGridLayout *>(ui->ramSettings->layout());
    settingsGrid->setColumnStretch(0, 4);
    settingsGrid->setColumnStretch(1, 1);

    // modify backgrounds for slider and text for display.

    // setup QSlider values
    ui->ramValueController->setMinimum(0);
    ui->ramValueController->setMaximum(15);
    ui->ramValueController->setTickInterval(1);
    ui->ramValueController->setTickPosition(QSlider::TicksBothSides);
    ui->ramValueController->setSingleStep(1);

    // Setup slot connection for both the slider and the text input
    connect(ui->ramValueController, &QSlider::valueChanged, this, &Settings::onSliderChange);

}

Settings::~Settings()
{
    delete ui;
}


void Settings::onSliderChange(int change)
{
    // on slider change calculate the RAM value, this will be need to be passed throughout the
    // application.

    int newRam = MIN_RAM + change;
    Settings::setRam(newRam);

    // display RAM value in label.
    std::stringstream ss;
    ss << newRam;
    ss << "%";

    // get the output as a QString
    QString ramDisplay = QString::fromStdString(ss.str());
    ui->warningPoint->setText(ramDisplay);
}


