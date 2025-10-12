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

    void showProcessStats(std::unordered_map<std::string, double> &process_stats, QTableWidget *tableWidget);
    void showApplicationStats(std::unordered_map<std::string, double> &app_stats, QTableWidget *tableWidget);

private:
    Ui::AppResourceViewer *ui;
    QWidget* processTab;
    QWidget* appTab;
    QTableWidget* ProcessStatView;
    QTableWidget* ApplicationStatView;
};

#endif // APP_RESOURCE_VIEWER_H
