#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>
#include <QActionGroup>
#include <QMimeData>
#include <QDropEvent>
#include <QPixmap>
#include <QClipboard>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *labFile;//添加到状态栏里
    QLabel *labInfo;//添加到状态栏里
    QLabel *labFont;//添加到状态栏里
    QComboBox *colorcomboBox;//添加到状态栏里
    QProgressBar *progressBarl;//进度条，添加到状态栏里
    QSpinBox *spinFontSize;//字体大小，添加到工具栏里
    QFontComboBox *comboFontName;//字体名称，添加到状态栏里
    QActionGroup *actionGroup;//Action分组，用于“汉语”和“English”两个工具按钮的互斥
    QClipboard *clipboard;//粘贴图片功能
    void buildUI();//以代码化的方式创建UI
    void buildSignalSlots();//手动关联信号槽
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void do_fontSize_Changed(int fontSize);//改变字体大小的SpinBox的响应

    void do_fontSelected(const QFont&font);//选择字体的FontComboBox的响应

    void on_actFont_Bold_triggered(bool checked);

    void on_actFont_Italic_triggered(bool checked);

    void on_actFont_UnderLine_triggered(bool checked);

    void on_actFile_Save_triggered();

    void on_actSys_ToggleText_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

    void do_fontcolorChanged(int index);

    void pasteImage();

    void on_actFile_New_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
