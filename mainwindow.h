#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


typedef enum StackedPageIndex{
    Page_Meeting, Page_Live, Page_Max
}StackedPageIndex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void SwitchPage(StackedPageIndex index);

private slots:
    void slot_toggled_live();
    void slot_toggled_meeting();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
