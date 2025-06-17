#ifndef APP_RESOURCE_VIEWER_H
#define APP_RESOURCE_VIEWER_H

#include <QDialog>

namespace Ui {
class AppResourceViewer;
}

class AppResourceViewer : public QDialog
{
    Q_OBJECT

public:
    explicit AppResourceViewer(QWidget *parent = nullptr);
    ~AppResourceViewer();

private:
    Ui::AppResourceViewer *ui;
};

#endif // APP_RESOURCE_VIEWER_H
