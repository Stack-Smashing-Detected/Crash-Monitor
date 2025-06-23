#ifndef APP_RESOURCE_VIEWER_H
#define APP_RESOURCE_VIEWER_H

#include <string>
#include <vector>
#include <QDialog>
#include <QListWidget>
#include <QWidget>

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

private:
    Ui::AppResourceViewer *ui;
    QWidget* cpuTab;
    QWidget* ramTab;
    QListWidget* cpuUsageView;
    QListWidget* ramUsageView;
};

#endif // APP_RESOURCE_VIEWER_H
