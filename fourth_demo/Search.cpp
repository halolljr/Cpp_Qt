#include "Search.h"

Search::Search(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::SearchClass())
{
	ui->setupUi(this);
}

Search::~Search()
{
	delete ui;
}
