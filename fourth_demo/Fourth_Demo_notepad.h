#pragma once
#include <iostream>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTextEdit>
#include <QFontDialog>
#include <QColorDialog>
#include "ui_Fourth_Demo_notepad.h"
#include "About.h"
#include "Search.h"
#include "Replace.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Fourth_Demo_notepadClass; };
QT_END_NAMESPACE

class Fourth_Demo_notepad : public QMainWindow
{
    Q_OBJECT

public:
    Fourth_Demo_notepad(QWidget *parent = nullptr);
    ~Fourth_Demo_notepad();
    /*初始化连接信号*/
    void buildSignal();
    /*初始化按钮可用情况*/
    void initButton();
private:
    //当新建或者打开一个文件时候，如果此时未保存修改会提示
    void do_textChanged();
    //当编辑器可以复制的时候
    void do_copyAvailabale(bool bt);
    //当编辑器可以撤销的时候
    void do_undoAvailabale(bool bt);
    //当编辑器可以恢复的时候
    void do_redoAvailabale(bool bt);
private slots:
    /*当前编辑器状态变更,将is_Text_Changed设置为true*/
    void do_textEdit_textChanged_triggered();
private slots:
    /*“关于”窗口*/
    void do_action_about_triggered();
    /*“查找”窗口*/
    void do_action_find_triggered();
    /*“替换”窗口*/
    void do_action_replace_triggered();
private slots:
    /*“新建”action*/
    void do_action_new_triggered();
    /*“打开”action*/
    void do_action_open_triggered();
    /*“保存”action*/
    void do_action_Save_triggered();
    /*“另存为”action*/
    void do_action_save_to_triggered();
    /*“撤销”action*/
    void do_action_backward_triggered();
    /*“恢复”action*/
    void do_action_forward_triggered();
    /*“剪切”action*/
    void do_action_cut_triggered();
    /*“复制”action*/
    void do_action_copy_triggered();
    /*“粘贴”action*/
    /*补充一个粘贴其他形式的*/
    void do_action_paste_triggered();
    /*“字体”action*/
    void do_action_font_triggered();
    /*“字体颜色”action*/
    void do_action_font_color_triggered();
    /*“字体背景色”action*/
    void do_action_font_backG_triggered();
    /*“编辑器背景色”action*/
    void do_action_EditG_triggered();
    /*自动换行*/
    void do_action_autoline_triggered();
private:
    Ui::Fourth_Demo_notepadClass *ui;
    QLabel* statusCursorLabel;
    QLabel* statusLabel;
    QLabel* authorLabel;
private:
    QString FilePath_;
    bool is_Text_Changed;
};
