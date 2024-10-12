#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QStringList>
#include <QKeyEvent>
#include <vector>
#include <regex>
#include <string>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <memory>
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
    QString src_str;//获取lineEdit的字符串
    bool is_consecutive_operators = false;//判断是否连续输入运算符
    bool is_plus = true;    //切换正负号
    bool is_lowdown = false;    //如果是负数开头的
    int operator_num = 0;  //记录运算符个数用于截取数字
    //std::shared_ptr<std::string> ptr_auto;
    std::unordered_map<int, QPushButton*> btn_Map;  //将Qt::Key与按钮绑定，在connect时候
    std::vector<std::string> src_stack;//数字
    std::vector<std::string> src_operator;//运算符
private:
    //绑定键盘按键与按钮
    void build_board_button();
    //链接信号与槽
    void build_signal(); 
    //获得字符串
    QString get_src_str() {
        return ui->lineEdit->text();
    }
    //判断是否连续输入运算符
    bool is_has_consecutive_operators(const std::string& str);
    //处理乘除法的运算
    void process_mul_div(std::vector<std::string>& src_stack,std::vector<std::string>& src_operator,bool& is_lowdown);
    //处理加减法的运算
    double process_add_sub(std::vector<std::string>& src_stack,std::vector<std::string>& src_operator,bool& is_lowdown);
	//传入正则表达式截取最后一个数字
	std::string find_the_last_string(const std::regex& num_regex, const std::string str);
	//收尾函数
	void do_theEnd();
private slots:
    void do_NumBtn_clicked();
    //小数点的槽函数处理是特殊的
    void do_period_Btn_clicked();
    //回退槽函数
    void do_delete_Btn_clicked();
    //清除槽函数
    void do_clear_Btn_clicked();
    //双操作符槽函数
    void do_Binary_Btn_clicked();
    //取倒数槽函数
    void do_inverse_Btn_clicked();
    //取平方的槽函数
    void do_square_Btn_clicked();
    //开根号的槽函数
    void do_sqrt_Btn_clicked();
    //取百分号的槽函数
    void do_percentage_Btn_clicked();
    //正负号的槽函数
    void do_sign_Btn_clicked();
    //处理结果槽函数
    void do_result_Btn_clicked();
    //键盘绑定
    virtual void keyPressEvent(QKeyEvent* event);
private:
    //只需要调用以下封装的函数即可
    void build_setBackGroundUI();
    void build_setBtnUI();
    void build_setLineUI();
    //设置按钮的FlatUI
    //正常状态+鼠标悬停状态+鼠标按下的前后景颜色
    void setBtnQss(QPushButton* btn,
        QString normalColor, QString normalTextColor,
        QString hoverColor, QString hoverTextColor,
        QString pressedColor, QString pressedTextColor);
    void setLineQss(QLineEdit* txt, QString normalColor, QString focusColor);
};
