#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clipboard=QApplication::clipboard();
    buildUI();//为动态创建界面组件
    buildSignalSlots();//为动态创建的组件关联信号与槽
    this->setCentralWidget(ui->textEdit);//textEdit填满工作区
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildUI(){
    //创建状态栏上的组件
    labFile=new QLabel(this);//用于显示当前文件名
    labFile->setMaximumWidth(150);
    labFile->setText("文件名:");
    ui->statusbar->addWidget(labFile);//添加到状态栏

    progressBarl=new QProgressBar(this);//状态栏上的进度条
    progressBarl->setMaximumWidth(200);
    progressBarl->setMinimum(5);
    progressBarl->setMaximum(50);
    progressBarl->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(progressBarl);//添加到状态栏

    labFont=new QLabel(this);//用于显示字体大小
    labFont->setText("当前字体大小:");
    ui->statusbar->addWidget(labFont);
    labInfo=new QLabel(this);//用于显示字体名称
    labInfo->setText("选择字体名称:");
    ui->statusbar->addWidget(labInfo);

    //为actLang_CN(汉语)和actLang-EN(英语)创建ActionGroup,实现互斥选择
    actionGroup=new QActionGroup(this);
    actionGroup->addAction(ui->actLang_CN);
    actionGroup->addAction(ui->actLang_EN);
    actionGroup->setExclusive(true);//实现互斥选择
    ui->actLang_CN->setChecked(true);//初始默认

    //创建工具栏上无法可视化设计的一些组件
    spinFontSize=new QSpinBox(this);//设置字体大小的SpinBox
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->textEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);
    ui->toolBar->addWidget(spinFontSize);//添加到工具栏

    comboFontName=new QFontComboBox(this);//字体下拉列表框
    comboFontName->setMinimumWidth(150);
    ui->toolBar->addWidget(comboFontName);//添加到工具栏

    colorcomboBox=new QComboBox(this);
    colorcomboBox->addItem("红色",QColor(Qt::red));
    colorcomboBox->addItem("蓝色",QColor(Qt::blue));
    colorcomboBox->addItem("绿色",QColor(Qt::green));
    colorcomboBox->addItem("黄色",QColor(Qt::yellow));
    colorcomboBox->addItem("紫色",QColor(128,100,162));
    ui->toolBar->addWidget(colorcomboBox);

    ui->toolBar->addSeparator();//工具栏上增加分割条
    ui->toolBar->addAction(ui->actClose);//“退出”按钮
}

void MainWindow::buildSignalSlots(){
    connect(spinFontSize,SIGNAL(valueChanged(int)),this,SLOT(do_fontSize_Changed(int)));
    connect(comboFontName,&QFontComboBox::currentFontChanged,this,&MainWindow::do_fontSelected);
    connect(colorcomboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::do_fontcolorChanged);
     connect(ui->textEdit, &QTextEdit::paste, this, &MainWindow::pasteImage);
}

void MainWindow::do_fontSize_Changed(int fontsize){
    //设置字体大小的SpinBox
    labFont->setText("字体大小:"+QString::number(fontsize));
    QTextCharFormat fmt=ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(fontsize);//设置字体大小
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBarl->setValue(fontsize);//状态栏上显示
}


void MainWindow::do_fontcolorChanged(int index){
    QColor selectedColor=colorcomboBox->itemData(index).value<QColor>();
    QTextCharFormat fmt=ui->textEdit->currentCharFormat();
    fmt.setForeground(selectedColor);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::do_fontSelected(const QFont &font){
    //选择字体的FontComboBox
    labInfo->setText("字体名称："+font.family());//状态栏上显示
    QTextCharFormat fmt=ui->textEdit->currentCharFormat();
    fmt.setFont(font);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actFont_Bold_triggered(bool checked)
{
    //粗体
    QTextCharFormat fmt=ui->textEdit->currentCharFormat();
    if(checked){
        fmt.setFontWeight(QFont::Bold);
    }
    else{
        fmt.setFontWeight(QFont::Normal);
    }
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actFont_Italic_triggered(bool checked)
{
    //斜体
    QTextCharFormat fmt=ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actFont_UnderLine_triggered(bool checked)
{
    //下划线
    QTextCharFormat fmt=ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actFile_Save_triggered()
{
    //保存文件
    ui->textEdit->document()->setModified(false);//表示已经保存过了，改变修改状态
    labFile->setText("文件已保存");//状态栏上显示
}


void MainWindow::on_actSys_ToggleText_triggered(bool checked)
{
    //是否显示工具按钮文字
    if(checked){
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    else{
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    }
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    //copyAvailable的槽函数，更新3个Action的enabled状态
    ui->actEdit_Cut->setEnabled(b);
    ui->actEdit_Copy->setEnabled(b);
    ui->actEdit_Paste->setEnabled(ui->textEdit->canPaste());
}


void MainWindow::on_textEdit_selectionChanged()
{
    //selectionChanged()信号的槽函数，更新3种字体样式的checked状态
    QTextCharFormat fmt=ui->textEdit->currentCharFormat();
    ui->actFont_Bold->setChecked(fmt.font().bold());//粗体
    ui->actFont_Italic->setChecked(fmt.fontItalic());//斜体
    ui->actFont_UnderLine->setChecked(fmt.fontUnderline());//下划线
}

void MainWindow::pasteImage(){
    const QMimeData* mimedata = QApplication::clipboard()->mimeData();
    if(mimedata->hasImage()){
        QPixmap pixmap=qvariant_cast<QPixmap>(mimedata->imageData());
        ui->textEdit->clear();
        ui->textEdit->append(pixmap.toImage().text());
    }
}

void MainWindow::on_actFile_New_triggered()
{
    QString dlgTitle="second_demo";
    QString strInfo="开发人员：梁家荣";
    QMessageBox::about(this,dlgTitle,strInfo);
}

