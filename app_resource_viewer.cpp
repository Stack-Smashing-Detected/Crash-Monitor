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
}
AppResourceViewer::~AppResourceViewer()
{
    delete ui;
}

void AppResourceViewer::setCurrentApp(std::unordered_map<std::string, double> &app_stats, std::string appName){
    if(!app_stats){
        this->appName = appName;
        ui->appName->setText(QString(this->appName));
        this->app_stats = std::move(app_stats);
        this->showApplicationStats(app_stats, ui->appStatistics);
        return;
    }

    this->appName = appName;
    ui->appName->setText(QString(this->appName));
    this->app_stats->clear();
    this->app_stats = std::move(app_stats);
    ui->appStatistics->clearContents();
    this->showApplicationStats(this->app_stats, ui->appStatistics);

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
