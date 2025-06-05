#include "settings.h"
#include "ui_settings.h"
#include <QFont>
#include <QGridLayout>

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
}

Settings::~Settings()
{
    delete ui;
}

