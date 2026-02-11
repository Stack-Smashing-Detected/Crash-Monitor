#ifndef APP_RESOURCE_VIEWER_H
#define APP_RESOURCE_VIEWER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <QDialog>
#include <QWidget>
#include <QTableWidget>

namespace Ui {
class AppResourceViewer;
}

class AppResourceViewer : public QDialog
{
    Q_OBJECT

public:
    explicit AppResourceViewer(QWidget *parent = nullptr);
    ~AppResourceViewer();

    void setCurrentApp(std::unordered_map<std::string, double> app_stats, std::string appName);

    void showApplicationStats(std::unordered_map<std::string, double> &app_stats, QTableWidget *tableWidget);

private:
    Ui::AppResourceViewer *ui;
    QWidget* processTab;
    QWidget* appTab;
    QTableWidget* ProcessStatView;
    QTableWidget* ApplicationStatView;
    std::unordered_map<std::string, double> app_stats;
    QString currentApp;
};

#endif // APP_RESOURCE_VIEWER_H
