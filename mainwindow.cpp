#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMaximumSize(1200,800);
    this->setMinimumSize(1200,800);

    QObject::connect(ui->live_btn, SIGNAL(clicked()), this, SLOT(slot_toggled_live()));
    QObject::connect(ui->meeting_btn, SIGNAL(clicked()), this, SLOT(slot_toggled_meeting()));
    SwitchPage(Page_Meeting);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_toggled_live()
{
    SwitchPage(Page_Live);
}

void MainWindow::slot_toggled_meeting()
{
    SwitchPage(Page_Meeting);
}

void MainWindow::SwitchPage(StackedPageIndex index)
{
    switch (index) {
    case Page_Meeting:
        if (ui->room_stackedWidget->currentWidget() != ui->page_meeting)
        {
            if(ui->page_live)
            {
                ui->page_live->dispost();
            }
            ui->room_stackedWidget->setCurrentWidget(ui->page_meeting);
            setWindowTitle("Meeting");
        }
        break;
    case Page_Live:
        if (ui->room_stackedWidget->currentWidget() != ui->page_live)
        {
            if(ui->page_meeting)
            {
                ui->page_meeting->dispost();
            }
            ui->room_stackedWidget->setCurrentWidget(ui->page_live);
            setWindowTitle("Live");
        }
        break;
    default:
        break;
    }
}
