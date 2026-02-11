#ifndef RUNNING_WINDOW_H
#define RUNNING_WINDOW_H

#include <QDialog>
#include <QTableView>
#include "nlohmann/json.hpp"
#include "headers/application_manager.h"
#include "app_resource_viewer.h"

namespace Ui {
class RunningWindow;
}

class RunningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RunningWindow(QWidget *parent = nullptr);
    ~RunningWindow();

    void indexAppStats(nlohmann::json &response, QTableView *tableView);

    void drawMemoryGraph();
    void checkForUpdates();

public slots:
    void showAppStatistics(nlohmann::json &response);

private:
    Ui::RunningWindow *ui;
    QTableView* GeneralAppStats;
    std::unique_ptr<ApplicationManager> am_ptr = nullptr;
    AppResourceViewer* appResourceViewer = nullptr;
};

#endif // RUNNING_WINDOW_H
