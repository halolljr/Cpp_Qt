#include "About.h"

About::About(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QImage image("./images/OIP.jpg");
	ui.label_8->setPixmap(QPixmap::fromImage(image));
	ui.label_8->show();
}

About::~About()
{}
