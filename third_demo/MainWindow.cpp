#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
{
    ui->setupUi(this);
    build_signal();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build_signal() {

    connect(ui->num0_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num1_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num2_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num3_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num4_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num5_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num6_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num7_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num8_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
    connect(ui->num9_Btn, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);


    connect(ui->period_Btn, &QPushButton::clicked, this, &MainWindow::do_period_Btn_clicked);
    connect(ui->delete_Btn, &QPushButton::clicked, this, &MainWindow::do_delete_Btn_clicked);
}

void MainWindow::do_NumBtn_clicked() {
    QString str_src = ui->lineEdit->text();
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    ui->statusBar->showMessage(btn->text() + "  button been clicked...");
    ui->lineEdit->setText(str_src + btn->text());
}

void MainWindow::do_period_Btn_clicked() {
    QString str = ui->lineEdit->text();
    if (str.contains(ui->period_Btn->text())) {
        return;
    }
    else {
        str += ui->period_Btn->text();
        ui->statusBar->showMessage(ui->period_Btn->text() + "  button been clicked...");
        ui->lineEdit->setText(str);
    }
}

void MainWindow::do_delete_Btn_clicked() {
    QString str = ui->lineEdit->text();
    str = str.left(str.length() - 1);
    ui->lineEdit->setText(str);
    ui->statusBar->showMessage(ui->delete_Btn->text() + "  button been clicked...");
}
