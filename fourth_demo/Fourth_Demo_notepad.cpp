#include "Fourth_Demo_notepad.h"

Fourth_Demo_notepad::Fourth_Demo_notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Fourth_Demo_notepadClass()),statusCursorLabel(new QLabel(this)),statusLabel(new QLabel(this)),
    authorLabel(new QLabel(this)),FilePath_(""),is_Text_Changed(false)
{
    ui->setupUi(this);
    buildSignal();
    initButton();

    statusCursorLabel->setMaximumWidth(150);
    statusCursorLabel->setText("Ln: " + QString::number(0) + "    Col: " + QString::number(1));
    ui->statusBar->addPermanentWidget(statusCursorLabel);

    statusLabel->setMaximumWidth(150);
    statusLabel->setText("length: " + QString::number(0) + "    lines: " + QString::number(1));
    ui->statusBar->addPermanentWidget(statusLabel);

    authorLabel->setMaximumHeight(150);
    authorLabel->setText(tr("梁家荣"));
    ui->statusBar->addPermanentWidget(authorLabel);
}

Fourth_Demo_notepad::~Fourth_Demo_notepad()
{
    delete ui;
}

void Fourth_Demo_notepad::buildSignal()
{
    //如果textEdit文字有改变但是我们没有保存,则弹出提示
    connect(ui->textEdit, &QTextEdit::textChanged, this, &Fourth_Demo_notepad::do_textEdit_textChanged_triggered);

    //显示新窗口
    connect(ui->action_about, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_about_triggered);
    connect(ui->action_find, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_find_triggered);
    connect(ui->action_repalce, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_replace_triggered);
    
    //普通action
    connect(ui->action_new, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_new_triggered);
    connect(ui->action_Open, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_open_triggered);
    connect(ui->action_Save, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_Save_triggered);
    connect(ui->action_save_to, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_save_to_triggered);
    
    connect(ui->textEdit, &QTextEdit::undoAvailable, this, &Fourth_Demo_notepad::do_undoAvailabale);
    connect(ui->action_backward, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_backward_triggered);
    
    connect(ui->textEdit, &QTextEdit::redoAvailable, this, &Fourth_Demo_notepad::do_redoAvailabale);
    connect(ui->action_forward, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_forward_triggered);
    
    connect(ui->action_cut, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_cut_triggered);
    
    connect(ui->textEdit, &QTextEdit::copyAvailable, this, &Fourth_Demo_notepad::do_copyAvailabale);
    connect(ui->action_copy, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_copy_triggered);
    
    connect(ui->action_paste, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_paste_triggered);

    connect(ui->action_font, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_font_triggered);
    connect(ui->action_font_color, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_font_color_triggered);
    connect(ui->action_font_backG, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_font_backG_triggered);
    connect(ui->action_EditG, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_EditG_triggered);
    connect(ui->action_autoline, &QAction::triggered, this, &Fourth_Demo_notepad::do_action_autoline_triggered);

}

void Fourth_Demo_notepad::initButton()
{
	ui->action_copy->setEnabled(false);
	ui->action_cut->setEnabled(false);
    ui->action_backward->setEnabled(false);
    ui->action_forward->setEnabled(false);
}

void Fourth_Demo_notepad::do_textChanged()
{
    do_action_save_to_triggered();
    is_Text_Changed = false;
}

void Fourth_Demo_notepad::do_copyAvailabale(bool bt)
{
    ui->action_copy->setEnabled(bt);
    ui->action_cut->setEnabled(bt);
}

void Fourth_Demo_notepad::do_undoAvailabale(bool bt)
{
    ui->action_backward->setEnabled(bt);
}

void Fourth_Demo_notepad::do_redoAvailabale(bool bt)
{
    ui->action_forward->setEnabled(bt);
}

void Fourth_Demo_notepad::do_textEdit_textChanged_triggered()
{
    this->setWindowTitle(tr("未保存更改 ") + FilePath_);
    is_Text_Changed = true;
}

void Fourth_Demo_notepad::do_action_about_triggered()
{
    //qDebug() << __func__ << " : running";
    About dlg;
    dlg.setWindowIcon(QIcon(":/Fourth_Demo_notepad/images/about_icon.png"));
    dlg.exec();
}

void Fourth_Demo_notepad::do_action_find_triggered()
{
    Search dlg;
    dlg.setWindowIcon(QIcon(":/Fourth_Demo_notepad/images/search_icon.png"));
    dlg.exec();
}

void Fourth_Demo_notepad::do_action_replace_triggered()
{
    Replace dlg;
    dlg.setWindowIcon(QIcon(":/Fourth_Demo_notepad/images/replace_icon.png"));
    dlg.exec();
}

void Fourth_Demo_notepad::do_action_new_triggered()
{
    if (is_Text_Changed) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "warning", tr("当前文件修改未保存，是否保存?"));
        if (reply == QMessageBox::Yes) {
            do_textChanged();
        }
    }
    FilePath_.clear();
    ui->textEdit->clear();
    this->setWindowTitle(tr("文本编辑器"));
}

void Fourth_Demo_notepad::do_action_open_triggered()
{
	if (is_Text_Changed) {
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, "warning", tr("当前文件修改未保存，是否保存?"));
		if (reply == QMessageBox::Yes) {
			do_textChanged();
		}
	}
    QString filename = QFileDialog::getOpenFileName(this, tr("打开文件"), ".", tr("文本文件(*.txt);;所有文件(*.*)"));
	if (filename.isEmpty()) {
		// 用户点击了关闭按钮，或者没有选择文件
		return;  // 不执行后续操作
	}
    QFile file(filename);
    if (!file.open(QFile::ReadOnly|QFile::Text)) {
        QMessageBox::warning(this, "warning", tr("打开文件失败"));
        return;
    }
    FilePath_ = filename;
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absolutePath());
}

void Fourth_Demo_notepad::do_action_Save_triggered()
{
	if (FilePath_.isEmpty()) {
		QString filename = QFileDialog::getSaveFileName(this, tr("打开文件以保存"), ".", tr("文本文件(*.txt);;所有文件(*.txt)"));
		// 检查用户是否选择了文件
		if (filename.isEmpty()) {
			return;  // 用户点击了关闭，返回
		}
		// 更新 FilePath_ 并创建新的 QFile 对象
		FilePath_ = filename;
	}
    QFile file(FilePath_);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "warning", tr("打开文件失败"));
        return;
	}
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(FilePath_).absolutePath());
    QMessageBox::information(this, "保存成功", tr("文件已成功保存"));
    is_Text_Changed = false;
}

void Fourth_Demo_notepad::do_action_save_to_triggered()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("另存为"), ".", tr("文本文件(*.txt);;所有文件(*.*)"));
	if (filename.isEmpty()) {
		return; 
	}
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, "警告", tr("无法保存文件"));
		return;
	}
    FilePath_ = filename;
	QTextStream out(&file);
	QString text = ui->textEdit->toPlainText(); 
	out << text; 
    file.flush();
	file.close();  
	this->setWindowTitle(QFileInfo(filename).fileName());
    QMessageBox::information(this, "保存成功", tr("文件已成功保存"));
    is_Text_Changed = false;
}

void Fourth_Demo_notepad::do_action_backward_triggered()
{
    ui->textEdit->undo();
}

void Fourth_Demo_notepad::do_action_forward_triggered()
{
    ui->textEdit->redo();
}

void Fourth_Demo_notepad::do_action_cut_triggered()
{
    ui->textEdit->cut();
}

void Fourth_Demo_notepad::do_action_copy_triggered()
{
    ui->textEdit->copy();
}

void Fourth_Demo_notepad::do_action_paste_triggered()
{
    ui->textEdit->paste();
}

void Fourth_Demo_notepad::do_action_font_triggered()
{
	QFont font = QFontDialog::getFont(nullptr, ui->textEdit->font(), this, tr("选择字体"));
	if (font != QFont()) {  // 检查用户是否选择了字体
		QTextCursor cursor = ui->textEdit->textCursor();

		// 检查是否有选中文本
		if (cursor.hasSelection()) {
			// 设置选中文本的字体
			QTextCharFormat format = cursor.charFormat();
			format.setFont(font);
			cursor.mergeCharFormat(format);
		}
		else {
			// 如果没有选中部分，选择整个文档并设置字体
			cursor.select(QTextCursor::Document);
			QTextCharFormat format = cursor.charFormat();
			format.setFont(font);
			cursor.mergeCharFormat(format);

			// 将光标移回到文档末尾
			cursor.movePosition(QTextCursor::End);
			ui->textEdit->setTextCursor(cursor);
		}
	}
}

void Fourth_Demo_notepad::do_action_font_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, tr("字体颜色"));
    if (color.isValid()) {
		QTextCursor cursor = ui->textEdit->textCursor();

		// 检查是否有选中文本
		if (cursor.hasSelection()) {
			// 设置选中文本的颜色
			QTextCharFormat format = cursor.charFormat();
			format.setForeground(color);
			cursor.mergeCharFormat(format);
		}
		else {
			// 如果没有选中部分，选择整个文档并设置颜色
			cursor.select(QTextCursor::Document);
			QTextCharFormat format = cursor.charFormat();
			format.setForeground(color);
			cursor.mergeCharFormat(format);

			// 将光标移回到文档末尾
			cursor.movePosition(QTextCursor::End);
			ui->textEdit->setTextCursor(cursor);
		}
    }
}

void Fourth_Demo_notepad::do_action_font_backG_triggered()
{
	QColor color = QColorDialog::getColor(Qt::white, this, tr("选择背景色"));
	if (color.isValid()) {
		QTextCursor cursor = ui->textEdit->textCursor();

		// 检查是否有选中文本
		if (cursor.hasSelection()) {
			// 设置选中文本的背景色
			QTextCharFormat format = cursor.charFormat();
			format.setBackground(color);
			cursor.mergeCharFormat(format);
		}
		else {
			// 如果没有选中部分，选择整个文档并设置背景色
			cursor.select(QTextCursor::Document);
			QTextCharFormat format = cursor.charFormat();
			format.setBackground(color);
			cursor.mergeCharFormat(format);

			// 将光标移回到文档末尾
			cursor.movePosition(QTextCursor::End);
			ui->textEdit->setTextCursor(cursor);
		}
	}
}

void Fourth_Demo_notepad::do_action_EditG_triggered()
{
	QColor color = QColorDialog::getColor(Qt::white, this, tr("选择背景色"));
	if (color.isValid()) {
		QPalette palette = ui->textEdit->palette();
		palette.setColor(QPalette::Base, color);  // 设置背景色
		ui->textEdit->setPalette(palette);
	}

}

void Fourth_Demo_notepad::do_action_autoline_triggered()
{
    QTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();
    if (mode == QTextEdit::NoWrap) {
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
        ui->action_autoline->setChecked(true);
    }
    else {
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
        ui->action_autoline->setChecked(false);
    }
}
