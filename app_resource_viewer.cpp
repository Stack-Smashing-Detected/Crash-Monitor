#include "app_resource_viewer.h"
#include "ui_app_resource_viewer.h"
#include "headers/process_algorithms.h"

#include <memory>

#include <QVBoxLayout>
#include <QTableWidgetItem>


AppResourceViewer::AppResourceViewer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppResourceViewer)
{
    ui->setupUi(this);

    // Create a diectory pointer to pass to the process finder
    DIR *dirp;
    // create an instance of the process finder object, eventually this will be used as a shared pointer.
    std::unique_ptr<ProcessAlgorithms> processDataPtr = std::make_unique<ProcessAlgorithms>(dirp);
    std::vector<std::string> appList = processDataPtr->getProcessList();



    // set up list viewers
    cpuTab = ui->tabWidget->widget(0);
    ramTab = ui->tabWidget->widget(1);

    cpuUsageView = new QListWidget(cpuTab);
    ramUsageView = new QTableWidget(ramTab);

    // style lists
    QVBoxLayout *qvBoxLayoutT1 = new QVBoxLayout;
    qvBoxLayoutT1->addWidget(cpuUsageView);

    QVBoxLayout *qvBoxLayoutT2 = new QVBoxLayout;
    qvBoxLayoutT2->addWidget(ramUsageView);

    cpuTab->setLayout(qvBoxLayoutT1);
    ramTab->setLayout(qvBoxLayoutT2);

    // fill list
    fillListViewer(appList, cpuUsageView);

    // fill table
    std::unordered_map<std::string, int> appNames = processDataPtr->getApplicationNames(appList);
    fillTableViewer(appNames, ramUsageView);

}
AppResourceViewer::~AppResourceViewer()
{
    delete ui;
}

void AppResourceViewer::fillListViewer(std::vector<std::string> &appList, QListWidget *listWidget){
    for (const std::string &item: appList){
        listWidget->addItem(QString::fromStdString(item));
    }
}

void AppResourceViewer::fillTableViewer(std::unordered_map<std::string, int> &appNames, QTableWidget *tableWidget){
    // here the items in the map need to be extracted and converted into QTableWidget Items
    int row = 0;
    tableWidget->insertRow(row);
    tableWidget->insertColumn(0);
    tableWidget->insertColumn(1);

    for(const auto &[key, value] : appNames){
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


