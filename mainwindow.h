#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helpwindow.h"
#include "settings.h"
#include "app_resource_viewer.h"
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
    void run_button_clicked();

    void help_button_clicked();

    void settings_button_clicked();

    void view_button_clicked();

    void setup_button_clicked();
private:
    Ui::MainWindow *ui;
    HelpWindow *helpWindow;
    Settings *settings;
    AppResourceViewer *app_resource_viewer;
};
#endif // MAINWINDOW_H
