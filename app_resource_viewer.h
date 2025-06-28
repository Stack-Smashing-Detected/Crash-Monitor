#ifndef APP_RESOURCE_VIEWER_H
#define APP_RESOURCE_VIEWER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <QDialog>
#include <QListWidget>
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

    void fillListViewer(std::vector<std::string> &appList, QListWidget *listWidget);
    void fillTableViewer(std::unordered_map<std::string, int> &appNames, QTableWidget *tableWidget);

private:
    Ui::AppResourceViewer *ui;
    QWidget* cpuTab;
    QWidget* ramTab;
    QListWidget* cpuUsageView;
    QTableWidget* ramUsageView;
};

#endif // APP_RESOURCE_VIEWER_H
