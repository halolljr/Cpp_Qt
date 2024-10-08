#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QPushButton>
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;
private:
    void build_signal();

private slots:
    void do_NumBtn_clicked();
    //С����Ĳۺ��������������
    void do_period_Btn_clicked();
    //���˲ۺ���
    void do_delete_Btn_clicked();
};
