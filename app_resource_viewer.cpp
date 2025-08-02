#include "app_resource_viewer.h"
#include "ui_app_resource_viewer.h"
#include "headers/process_algorithms.h"

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

void AppResourceViewer::fillListViewer(std::vector<std::string> &appList, QListWidget *listWidget)
{
    for (const std::string &item : appList)
    {
        listWidget->addItem(QString::fromStdString(item));
    }
}

void AppResourceViewer::fillTableViewer(std::unordered_map<std::string, int> &appNames, QTableWidget *tableWidget)
{
    // here the items in the map need to be extracted and converted into QTableWidget Items
    int row = 0;
    tableWidget->insertRow(row);
    tableWidget->insertColumn(0);
    tableWidget->insertColumn(1);

    // resize the table view
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (const auto &[key, value] : appNames)
    {
        // create table widget items

        QTableWidgetItem *appName = new QTableWidgetItem(QString::fromStdString(key));
        tableWidget->setItem(row, 0, appName);

        QTableWidgetItem *procCount = new QTableWidgetItem(QString::number(value));
        tableWidget->setItem(row, 1, procCount);

        // finally insert new row premptively
        row++;
        tableWidget->insertRow(row);
    }
}
