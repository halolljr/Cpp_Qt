#pragma once

#include <QDialog>
#include "ui_About.h"

class About : public QDialog
{
	Q_OBJECT

public:
	About(QWidget *parent = nullptr);
	~About();

private:
	Ui::AboutClass ui;
};
