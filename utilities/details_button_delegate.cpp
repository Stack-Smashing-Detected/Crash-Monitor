#include "../headers/details_button_delegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QStyle>


DetailsButtonDelegate::DetailsButtonDelegate(QObject *parent): QStyledItemDelegate(parent)
{

}

void DetailsButtonDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionButton button;
    button.rect = option.rect.adjusted(4, 4, -4, -4);
    button.text = "More Details";
    button.state = QStyle::State_Enabled;
    if(option.state & QStyle::State_MouseOver){
        button.state |= QStyle::State_MouseOver;
    }

    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}


bool DetailsButtonDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if(event->type() != QEvent::MouseButtonRelease)
        return false;

    auto* mouseEvent = static_cast<QMouseEvent*>(event);

    QRect buttonRect = option.rect.adjusted(4, 4, -4, -4);
    if(!buttonRect.contains(mouseEvent->pos()))
        return false;

    QModelIndex appIndex = model->index(index.row(), 0);
    QString appName = appIndex.data(Qt::DisplayRole).toString();

    emit detailsRequested(appName);
    return true;
}


