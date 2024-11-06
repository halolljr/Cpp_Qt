#pragma once

#include <QDialog>
#include "ui_Search.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SearchClass; };
QT_END_NAMESPACE

class Search : public QDialog
{
	Q_OBJECT

public:
	Search(QWidget *parent = nullptr);
	~Search();

private:
	Ui::SearchClass *ui;
};
