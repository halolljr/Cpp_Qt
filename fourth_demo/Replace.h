#pragma once

#include <QDialog>
#include "ui_Replace.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ReplaceClass; };
QT_END_NAMESPACE

class Replace : public QDialog
{
	Q_OBJECT

public:
	Replace(QWidget *parent = nullptr);
	~Replace();

private:
	Ui::ReplaceClass *ui;
};
