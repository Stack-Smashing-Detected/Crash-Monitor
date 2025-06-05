#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helpwindow.h"
#include "settings.h"
#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_runBtn_clicked();

    void on_helpBtn_clicked();

    void on_settingsBtn_clicked();

private:
    Ui::MainWindow *ui;
    HelpWindow *helpWindow;
    Settings *settings;
};
#endif // MAINWINDOW_H
