#ifndef REMOTEUSERUI_H
#define REMOTEUSERUI_H

#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class RemoteUserUI;
}

class RemoteUserUI : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteUserUI(QWidget *parent = nullptr);
    ~RemoteUserUI();
    void setItem(QListWidgetItem *item);
    QListWidgetItem* getItem();

private:
    Ui::RemoteUserUI *ui;
    QListWidgetItem *_item;
};

#endif // REMOTEUSERUI_H
