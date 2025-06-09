#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    // getter and setter for ram.
    int getRam(){
        return ram;
    }

    void setRam(int newRam){
        this->ram = newRam;
    }



private slots:
    void onSliderChange(int change);

private:
    Ui::Settings *ui;
    int ram; // amount of ram on the slider (80 + slider value).
};

#endif // SETTINGS_H
