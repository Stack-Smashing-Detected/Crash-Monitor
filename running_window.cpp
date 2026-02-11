#include "running_window.h"
#include "ui_running_window.h"
#include "headers/application_manager.h"
#include "headers/process_algorithms.h"

RunningWindow::RunningWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunningWindow)
{
    ui->setupUi(this);
    this->am_ptr = std::make_unique<ApplicationManager>();
    std::unique_ptr<MemoryStatProcessing> msp_ptr = std::make_unique<MemoryStatProcessing>();
    std::unique_ptr<ProcessAlgorithms> pa_ptr = std::make_unique<ProcessAlgorithms>();

    std::unordered_map<std::string, std::string> processes = pa_ptr->find_processes();
    am_ptr->initial_create(processes, &msp_ptr);

    // next use the app manager's index to get a json output of all the itmes and their two most important statistics (pss and swap_pss).
    // in the display they'll be shown as "ram" and "swap". We'll of course have to seralize this into a map.
    using json = nlohmann::json;

    json full_data = am_ptr->index();

    // TODO: Display app name and total ram
    this->indexAppStats(am_ptr->index(), ui->mainStatView);

}

void RunningWindow::indexAppStats(nlohmann::json &response, QTableView *tableView)
{
    auto *memory_model = new QStandardItemModel(tableView);
    memory_model->setHorizontalHeaderLabels({
        "Application",
        "RAM (MB)"
        "Swap (MB)",
        "View Detailed",
    });

    int row = 0;




    for (auto app_key = response.begin(); app_key != response.end(); app_key++){
        std::string name = app_key.value()["Name"];
        double ram = std::stod(app_key.value()["RAM"]);
        double swap = std::stod(app_key.value()["Swap"]);

        *qt_name = new QStandardItem(QString::fromStdString(name));
        *qt_ram = new QStandardItem(QString::number(ram));
        *qt_swap = new QStandardItem(QString::number(swap));

        memory_model->setItem(row, 0, qt_name);
        memory_model->setItem(row, 1, qt_ram);
        memory_model->setItem(row, 2, qt_swap);


        row++;
    }

    auto* delegate = new DetailsButtonDelegate(tableView);
    connect(delegate, &DetailsButtonDelegate::detailsRequested, this, [this](const QString& appName){
        nlohmann::json response = this->am_ptr->read(appName.toStdString());
        this->showAppStatistics(response);
    });
}

void RunningWindow::showAppStatistics(nlohmann::json &response){
    // connect to the app resource viewer here.
    if(!this->appResourceViewer){
        this->appResourceViewer = new AppResourceViewer(this);
    }

    std::unordered_map<std::string, std::string> data;
    std::string appName = '';
    for(auto response_part = response.begin(); response_part != response.end(); app_key++){
        if(response_part.key() == "name"){
            app_name = std::move(response_part.value.dump());
        }
        else if(response_part.key() == "application data"){
            data = std::move(response_part.value().dump());
        }
        else{
            std::cout << response_part.key << std::endl;
        }
    }
    
    this->appResourceViewer->setCurrentApp(data, appName);
    this->appResourceViewer->show();
    this->appResourceViewer->raise();
    this->appResourceViewer->activateWindow();
}

RunningWindow::~RunningWindow()
{
    delete ui;
}
