#include "app_resource_viewer.h"
#include "ui_app_resource_viewer.h"
#include "headers/process_algorithms.h"
#include "headers/memory_stat_processing.h"

#include <memory>

#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>


AppResourceViewer::AppResourceViewer(QWidget *parent)
    : QDialog(parent), ui(new Ui::AppResourceViewer)
{
    ui->setupUi(this);

    // setup
    std::unique_ptr<MemoryStatProcessing> msp_testing = std::make_unique<MemoryStatProcessing>();
    std::string path = "../../mem_stats/3348.json";
    std::string path_2 = "../../mem_stats/3349.json";

    std::unordered_map<std::string, double> process_stats_a = msp_testing->evaluate_memory_stat_sheet(path);
    std::unordered_map<std::string, double> process_stats_b = msp_testing->evaluate_memory_stat_sheet(path_2);

    this->showProcessStats(process_stats_a, ui->processStats);
    this->showProcessStats(process_stats_b, ui->appStats);
}
AppResourceViewer::~AppResourceViewer()
{
    delete ui;
}

void AppResourceViewer::showProcessStats(std::unordered_map<std::string, double> &process_stats , QTableWidget *tableWidget)
{
    int row = 0;
    tableWidget->insertRow(row);
    tableWidget->insertColumn(0);
    tableWidget->insertColumn(1);

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(const auto &[key, value] : process_stats)
    {
        QTableWidgetItem *process_stat = new QTableWidgetItem(QString::fromStdString(key));
        tableWidget->setItem(row, 0, process_stat);

        QTableWidgetItem *stat_value = new QTableWidgetItem(QString::number(value));
        tableWidget->setItem(row, 1, stat_value);

        row++;
        tableWidget->insertRow(row);
    }
}

void AppResourceViewer::showApplicationStats(std::unordered_map<std::string, double> &app_stats, QTableWidget *tableWidget)
{
    // here the items in the map need to be extracted and converted into QTableWidget Items
    int row = 0;
    tableWidget->insertRow(row);
    tableWidget->insertColumn(0);
    tableWidget->insertColumn(1);

    // resize the table view
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (const auto &[key, value] : app_stats)
    {
        // create table widget items

        QTableWidgetItem *app_stat_identifier = new QTableWidgetItem(QString::fromStdString(key));
        tableWidget->setItem(row, 0, app_stat_identifier);

        QTableWidgetItem *app_stat_value = new QTableWidgetItem(QString::number(value));
        tableWidget->setItem(row, 1, app_stat_value);

        // finally insert new row premptively
        row++;
        tableWidget->insertRow(row);
    }
}
