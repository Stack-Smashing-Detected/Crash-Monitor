#ifndef DETAILS_BUTTON_DELEGATE_H
#define DETAILS_BUTTON_DELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class DetailsButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DetailsButtonDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent)
    {
    }

signals:
    void details_requested(const QString &app_name);

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                      const QStyleOptionViewItem &option, const QModelIndex &index) override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DETAILS_BUTTON_DELEGATE_H
