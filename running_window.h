#ifndef RUNNING_WINDOW_H
#define RUNNING_WINDOW_H

#include <QDialog>
#include <QTableView>
#include "nlohmann/json.hpp"

namespace Ui {
class RunningWindow;
}

class RunningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RunningWindow(QWidget *parent = nullptr);
    ~RunningWindow();

    void indexAppStats(nlohman::json &all_stats, QTableView *tableView);

private:
    Ui::RunningWindow *ui;
    QTableView* GeneralAppStats;
};

#endif // RUNNING_WINDOW_H
