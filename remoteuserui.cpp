#include "remoteuserui.h"
#include "ui_remoteuserui.h"

RemoteUserUI::RemoteUserUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteUserUI)
{
    ui->setupUi(this);
    ui->widget_video->setStyleSheet("background-color:black;");
}

RemoteUserUI::~RemoteUserUI()
{
    delete ui;
}

void RemoteUserUI::setItem(QListWidgetItem *item)
{
    _item = item;
}

QListWidgetItem *RemoteUserUI::getItem()
{
    return _item;
}
