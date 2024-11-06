#include "Replace.h"

Replace::Replace(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::ReplaceClass())
{
	ui->setupUi(this);
}

Replace::~Replace()
{
	delete ui;
}
