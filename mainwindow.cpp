#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("RTC quickdemo ");
    connect(ui->btn_live_model, &QPushButton::clicked, this, &MainWindow::LiveModelBtnClicked);
    connect(ui->btn_meeting_model, &QPushButton::clicked, this,  &MainWindow::MeetingModelBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LiveModelBtnClicked(){
    ui->stackedWidget->setCurrentIndex(1);
    setWindowTitle("RTC quickdemo 直播模式");
}
void MainWindow::MeetingModelBtnClicked(){
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle("RTC quickdemo 普通会议模式");
}
