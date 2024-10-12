#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass()),src_str(QString("0"))    //初始为0
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
	build_board_button();
    build_signal();
    build_setBtnUI();
    build_setLineUI();
    build_setBackGroundUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build_board_button()
{
	btn_Map = { {Qt::Key_0,ui->num0_Btn},
				{Qt::Key_1,ui->num1_Btn},
				{Qt::Key_2,ui->num2_Btn} ,
				{Qt::Key_3,ui->num3_Btn} ,
				{Qt::Key_4,ui->num4_Btn} ,
				{Qt::Key_5,ui->num5_Btn} ,
				{Qt::Key_6,ui->num6_Btn} ,
				{Qt::Key_7,ui->num7_Btn} ,
				{Qt::Key_8,ui->num8_Btn} ,
				{Qt::Key_9,ui->num9_Btn} ,
				{Qt::Key_Period,ui->period_Btn},
				{Qt::Key_Backspace,ui->delete_Btn},
				{Qt::Key_Plus,ui->plus_Btn},
				{Qt::Key_Minus,ui->minus_Btn},
				{Qt::Key_Asterisk,ui->multiply_Btn},
				{Qt::Key_Slash,ui->divide_Btn},
				{Qt::Key_Return,ui->result_Btn} };
}

void MainWindow::build_signal() {
    //[0,9]数字点击
	for (auto& it : btn_Map) {
		if (it.first >= Qt::Key_0 && it.first <= Qt::Key_9) {	//Qt::Key_0 <= it.first <= Qt::Key_9错误写法，典型
			connect(it.second, &QPushButton::clicked, this, &MainWindow::do_NumBtn_clicked);
		}
		else if (it.first == Qt::Key_Period) {
			//.按钮点击
			connect(it.second, &QPushButton::clicked, this, &MainWindow::do_period_Btn_clicked);
		}
		else if (it.first == Qt::Key_Backspace) {
			//回退按钮点击
			connect(it.second, &QPushButton::clicked, this, &MainWindow::do_delete_Btn_clicked);
		}
		else if (it.first == Qt::Key_Return) {
			//结果按钮点击
			connect(it.second, &QPushButton::clicked, this, &MainWindow::do_result_Btn_clicked);
		}
		else if (it.first == Qt::Key_Plus || it.first == Qt::Key_Minus ||
			it.first == Qt::Key_Asterisk || it.first == Qt::Key_Slash) {
			//双操作符按钮点击
			connect(it.second, &QPushButton::clicked, this, &MainWindow::do_Binary_Btn_clicked);
		}
	}
    
    //清空按钮点击
    connect(ui->clear_Btn, &QPushButton::clicked, this, &MainWindow::do_clear_Btn_clicked);
    
    //取倒数按钮点击
    connect(ui->inverse_Btn, &QPushButton::clicked, this, &MainWindow::do_inverse_Btn_clicked);

    //平方按钮点击
    connect(ui->square_Btn, &QPushButton::clicked, this, &MainWindow::do_square_Btn_clicked);

    //开根按钮点击
    connect(ui->sqrt_Btn, &QPushButton::clicked, this, &MainWindow::do_sqrt_Btn_clicked);

    //取百分号
    connect(ui->percentage_Btn, &QPushButton::clicked, this, &MainWindow::do_percentage_Btn_clicked);

	//正负号
    connect(ui->sign_Btn, &QPushButton::clicked, this, &MainWindow::do_sign_Btn_clicked);
    
}

void MainWindow::do_NumBtn_clicked() {
    MainWindow::src_str = get_src_str();
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
	ui->statusBar->showMessage(btn->text() + "  button been clicked...");
	ui->lineEdit->setText(src_str + btn->text());
    is_consecutive_operators = false;
}

void MainWindow::do_period_Btn_clicked() {
    
    
    MainWindow::src_str = get_src_str();
    std::string std_src = src_str.toStdString();
	//"×"、"÷"非标准ASCII码，不能用于char
	std::string str_1 = "+";
	std::string str_2 = "-";
	std::string str_3 = "×";
	std::string str_4 = "÷";
   
    if (std_src.empty()) {
		//为防止多次输入"."或者出现形如"16.88.66"这样子不合规的数字
        //ui->period_Btn->setEnabled(false);
        return;
    }
    //为防止输入".87"之类的数字
    if (std_src.at(std_src.length() - 1) == str_1.at(str_1.length() - 1) ||
        std_src.at(std_src.length() - 1) == str_2.at(str_2.length() - 1) ||
        std_src.at(std_src.length() - 1) == str_3.at(str_3.length() - 1) ||
        std_src.at(std_src.length() - 1) == str_4.at(str_4.length() - 1)) {
        
        src_str += "0"+ui->period_Btn->text();
    }
    else {
        src_str += ui->period_Btn->text();
    }
    ui->statusBar->showMessage(ui->period_Btn->text() + "  button been clicked...");
    ui->lineEdit->setText(src_str);

    //为防止多次输入"."或者出现形如"16.88.66"这样子不合规的数字
    //必须输入完整的数字之后才设置为可用
    ui->period_Btn->setEnabled(false);
}

void MainWindow::do_delete_Btn_clicked() {
    MainWindow::src_str = get_src_str();
	if (src_str.isEmpty()) {
		ui->period_Btn->setEnabled(true);
		return;
	}
    std::string std_src = src_str.toStdString();

    std::string std_btn_text = ui->period_Btn->text().toStdString();
    if (std_src[std_src.length()-1]==std_btn_text[std_btn_text.length()-1]) {
        ui->period_Btn->setEnabled(true);//如果回退的是“.”则使其可用
    }

    src_str = src_str.left(src_str.length() - 1);
    ui->lineEdit->setText(src_str);
    ui->statusBar->showMessage(ui->delete_Btn->text() + "  button been clicked...");
}

void MainWindow::do_clear_Btn_clicked() {
    MainWindow::src_str = get_src_str();
	do_theEnd();
    ui->lineEdit->setText(src_str);
    ui->statusBar->showMessage(ui->clear_Btn->text() + "  button been clicked...");
}

void MainWindow::do_Binary_Btn_clicked() {
    
    //判断是否连续输入了运算符
	if (is_consecutive_operators) {
		QMessageBox::information(this, tr("Info"), tr("不可以输入连续运算符"), QMessageBox::Ok, QMessageBox::NoButton);
		is_consecutive_operators = false;
		return;
	}
    //如果没有输入数字
    MainWindow::src_str = get_src_str();
    if (src_str.isEmpty()) {
        QMessageBox::information(this, tr("Info"), tr("请先输入数字"), QMessageBox::Ok, QMessageBox::NoButton);
        is_consecutive_operators = false;
        return;
    }
	//读取最后一个数字
	std::regex num_regex("\\d+(\\.\\d+)?");
	std::string std_str = src_str.toStdString();
	std::string last_match = find_the_last_string(num_regex, std_str);
	std::stringstream ss(last_match);
	double temp = 0;
	ss >> temp;
	ss.clear();
	//如果是÷号判断被除数是否为0
	QPushButton* btn = static_cast<QPushButton*>(sender());
	std::string btn_str = btn->text().toStdString();
	std::string temp_str = "÷";
    if (btn_str==temp_str) {
        if (temp == 0 ) {
			QMessageBox::information(this, tr("Info"), tr("被除数不能为0"), QMessageBox::Ok, QMessageBox::NoButton);
			is_consecutive_operators = false;
			return;
        }
    }
	//如果是单个运算符并且是负数开头
	if (src_operator.empty()) {
		if (std_str[0] == '-') {
			is_lowdown = true;
		}
	}
    //运算符入数组
    src_operator.push_back(btn_str);
    src_str += btn->text();
    //截取数字（匹配整数和小数）
    std::regex num_regex_2("\\d+(\\.\\d+)?");
    std_str = src_str.toStdString();
    std::sregex_iterator iter_begin_2(std_str.begin(), std_str.end(), num_regex_2);
    std::sregex_iterator iter_end_2;
    size_t i = 0;
    while (iter_begin_2 != iter_end_2) {
        //防止多次压入重复的数据
        if (i == MainWindow::operator_num) {
            src_stack.push_back((*iter_begin_2).str());
        }
        i++;
        iter_begin_2++;
    }
    MainWindow::operator_num++;

    ui->lineEdit->setText(src_str);
    ui->statusBar->showMessage(btn->text() + "  button been clicked...");
    is_consecutive_operators = true;
	/*for (auto it : src_stack) {
		 qDebug() << it;
	}*/
    //必须按下一次操作符才可以让"."按钮可用
    ui->period_Btn->setEnabled(true);
}

void MainWindow::do_inverse_Btn_clicked()
{
    MainWindow::src_str = get_src_str();
    std::string std_str = src_str.toStdString();
    if (src_str.isEmpty()) {
        QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
	if (src_str[0] == '-') {
		is_lowdown = true;
	}
    //符合先输入数字再按操作符号格式
    char str_1 = '+', str_2 = ' - ', str_3 = '×', str_4 = '÷';
    if (std_str[std_str.length() - 1] == str_1 ||
        std_str[std_str.length() - 1] == str_2 ||
        std_str[std_str.length() - 1] == str_3 ||
        std_str[std_str.length() - 1] == str_4) {

		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
    }
    //取操作数
	std::regex num_regex("\\d+(\\.\\d+)?");
	std::string tacket = find_the_last_string(num_regex, std_str);

    //qDebug() << tacket;
    if (tacket == "0") {
        QMessageBox::warning(this, "Warning", "0不可以作为分母", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    //取倒数操作
    std::stringstream ss(tacket);   //记得clear（如果你要在未结束的时候多次使用）
    double tacket_num = 0;
    ss >> tacket_num;
	double result = 0;
	if (is_lowdown) {
		result = -1.0 / tacket_num;
	}
	else {
		result = 1.0 / tacket_num;
	}
    ss.clear();
    ss << std::fixed << std::setprecision(6) << result;
    
    //入数组
    //先别入数组，因为在等于号这里会处理的
    // 形如65 + 9 =
    //src_stack.push_back(ss.str());
    
    //更新显示
	{
		std::regex num_regex("\\d+(\\.\\d+)?");
		std::sregex_iterator iter_begin(std_str.begin(), std_str.end(), num_regex);
		std::sregex_iterator iter_end;
        size_t i = 0;
		while (iter_begin != iter_end) {
            if (tacket == (*iter_begin).str()) {
                break;
            }
            i++;
			iter_begin++;
		}
        std::string temp;
        for (int t = 0; t < i; ++t) {
            temp += src_stack[t] + src_operator[t];
        }
        temp += ss.str();
        src_str = QString::fromStdString(temp);
        ui->lineEdit->setText(src_str);
	}
    ss.clear();
	QPushButton* btn = static_cast<QPushButton*>(sender());
	ui->statusBar->showMessage(btn->text() + "  button been clicked...");
}

void MainWindow::do_square_Btn_clicked()
{
	MainWindow::src_str = get_src_str();
	std::string std_str = src_str.toStdString();
	if (src_str.isEmpty()) {
		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//符合先输入数字再按操作符号格式
	char str_1 = '+', str_2 = ' - ', str_3 = '×', str_4 = '÷';
	if (std_str[std_str.length() - 1] == str_1 ||
		std_str[std_str.length() - 1] == str_2 ||
		std_str[std_str.length() - 1] == str_3 ||
		std_str[std_str.length() - 1] == str_4) {

		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//取操作数
	std::regex num_regex("\\d+(\\.\\d+)?");
	std::string tacket = find_the_last_string(num_regex, std_str);
	//qDebug() << tacket;
	
	//取平方操作
	std::stringstream ss(tacket);   //记得clear（如果你要在未结束的时候多次使用）
	double tacket_num = 0;
	ss >> tacket_num;
    double result = tacket_num * tacket_num;
	ss.clear();
	ss << std::fixed << std::setprecision(6) << result;
	
    //入数组
	//先别入数组，因为在等于号这里会处理的
	// 形如65 + 9 =
	//src_stack.push_back(ss.str());
	
    //更新显示
	{
		std::regex num_regex("\\d+(\\.\\d+)?");
		std::sregex_iterator iter_begin(std_str.begin(), std_str.end(), num_regex);
		std::sregex_iterator iter_end;
		size_t i = 0;
		while (iter_begin != iter_end) {
			if (tacket == (*iter_begin).str()) {
				break;
			}
			i++;
			iter_begin++;
		}
		std::string temp;
		for (int t = 0; t < i; ++t) {
			temp += src_stack[t] + src_operator[t];
		}
		temp += ss.str();
		src_str = QString::fromStdString(temp);
		ui->lineEdit->setText(src_str);
	}
	ss.clear();
	QPushButton* btn = static_cast<QPushButton*>(sender());
	ui->statusBar->showMessage(btn->text() + "  button been clicked...");
}

void MainWindow::do_sqrt_Btn_clicked()
{
	MainWindow::src_str = get_src_str();
	std::string std_str = src_str.toStdString();
	if (src_str.isEmpty()) {
		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//符合先输入数字再按操作符号格式
	char str_1 = '+', str_2 = ' - ', str_3 = '×', str_4 = '÷';
	if (std_str[std_str.length() - 1] == str_1 ||
		std_str[std_str.length() - 1] == str_2 ||
		std_str[std_str.length() - 1] == str_3 ||
		std_str[std_str.length() - 1] == str_4) {

		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//取操作数
	std::regex num_regex("\\d+(\\.\\d+)?");
	std::string tacket = find_the_last_string(num_regex, std_str);
	//qDebug() << tacket;
	std::stringstream ss(tacket);   //记得clear（如果你要在未结束的时候多次使用）
	double tacket_num = 0;
	ss >> tacket_num;
	ss.clear();
	if (tacket_num < 0) {
		QMessageBox::warning(this, "Warning", "底数不能小于0", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//开平方操作操作
    double result = std::sqrt(tacket_num);
	ss << std::fixed << std::setprecision(6) << result;
	
    //入数组
	//先别入数组，因为在等于号这里会处理的
	// 形如65 + 9 =
	//src_stack.push_back(ss.str());
	
    //更新显示
	{
		std::regex num_regex("\\d+(\\.\\d+)?");
		std::sregex_iterator iter_begin(std_str.begin(), std_str.end(), num_regex);
		std::sregex_iterator iter_end;
		size_t i = 0;
		while (iter_begin != iter_end) {
			if (tacket == (*iter_begin).str()) {
				break;
			}
			i++;
			iter_begin++;
		}
		std::string temp;
		for (int t = 0; t < i; ++t) {
			temp += src_stack[t] + src_operator[t];
		}
		temp += ss.str();
		src_str = QString::fromStdString(temp);
		ui->lineEdit->setText(src_str);
	}
	ss.clear();
	QPushButton* btn = static_cast<QPushButton*>(sender());
	ui->statusBar->showMessage(btn->text() + "  button been clicked...");
}

void MainWindow::do_percentage_Btn_clicked()
{
	MainWindow::src_str = get_src_str();
	std::string std_str = src_str.toStdString();
	if (src_str.isEmpty()) {
		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//符合先输入数字再按操作符号格式
	char str_1 = '+', str_2 = ' - ', str_3 = '×', str_4 = '÷';
	if (std_str[std_str.length() - 1] == str_1 ||
		std_str[std_str.length() - 1] == str_2 ||
		std_str[std_str.length() - 1] == str_3 ||
		std_str[std_str.length() - 1] == str_4) {

		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//取操作数
	std::regex num_regex("\\d+(\\.\\d+)?");
	std::string tacket = find_the_last_string(num_regex, std_str);
	//qDebug() << tacket;
	std::stringstream ss(tacket);   //记得clear（如果你要在未结束的时候多次使用）
	double tacket_num = 0;
	ss >> tacket_num;
	ss.clear();
	
	//开平方操作操作
    double result = tacket_num / 100.0;
	ss << std::fixed << std::setprecision(6) << result;

	//入数组
	//先别入数组，因为在等于号这里会处理的
	// 形如65 + 9 =
	//src_stack.push_back(ss.str());

	//更新显示
	{
		std::regex num_regex("\\d+(\\.\\d+)?");
		std::sregex_iterator iter_begin(std_str.begin(), std_str.end(), num_regex);
		std::sregex_iterator iter_end;
		size_t i = 0;
		while (iter_begin != iter_end) {
			if (tacket == (*iter_begin).str()) {
				break;
			}
			i++;
			iter_begin++;
		}
		std::string temp;
		for (int t = 0; t < i; ++t) {
			temp += src_stack[t] + src_operator[t];
		}
		temp += ss.str();
		src_str = QString::fromStdString(temp);
		ui->lineEdit->setText(src_str);
	}
	ss.clear();
	QPushButton* btn = static_cast<QPushButton*>(sender());
	ui->statusBar->showMessage(btn->text() + "  button been clicked...");
}

void MainWindow::do_sign_Btn_clicked()
{
    //空数字
	MainWindow::src_str = get_src_str();
	std::string std_str = src_str.toStdString();
	if (src_str.isEmpty()) {
		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//符合先输入数字再按操作符号格式
	char str_1 = '+', str_2 = ' - ', str_3 = '×', str_4 = '÷';
	if (std_str[std_str.length() - 1] == str_1 ||
		std_str[std_str.length() - 1] == str_2 ||
		std_str[std_str.length() - 1] == str_3 ||
		std_str[std_str.length() - 1] == str_4) {

		QMessageBox::warning(this, "Warning", "请先输入数字", QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	//取操作数
    //如果是单操作数
    //改变的符号的格式得变成成0+/-（同时将0与+/-操作符入数组）
	if (src_operator.empty()) {
        if (is_plus) {
            src_stack.push_back("0");
            src_operator.push_back("-");
			MainWindow::operator_num++;
            src_str = "0-" + src_str;
            //改变符号
            is_plus = false;
        }
        else
        {
			src_stack.push_back("0");
			src_operator.push_back("+");
			MainWindow::operator_num++;
			src_str = "0-" + src_str;
			//改变符号
			is_plus = true;
        }
        ui->lineEdit->setText(src_str);
		QPushButton* btn = static_cast<QPushButton*>(sender());
		ui->statusBar->showMessage(btn->text() + "  button been clicked...");
        return;
	}
    else {
		//定位要改变正负号的数字的符号
		size_t count = 0;
		//定位最后一个数字
		std::string tacket;
		{
			std::regex num_regex("\\d+(\\.\\d+)?");
			std::sregex_iterator iter_begin(std_str.begin(), std_str.end(), num_regex);
			std::sregex_iterator iter_end;
			while (iter_begin != iter_end) {
				tacket = (*iter_begin).str();
				count++;
				iter_begin++;
			}
		}
		//判断是否是+-号
		if (src_operator[count - 2] == "×" || src_operator[count - 2] == "÷") {
			return;
		}
		//改变正负号
		if (is_plus) {
			src_operator[count - 2] = "-";
			is_plus = false;
		}
		else {
			src_operator[count - 2] = "+";
			is_plus = true;
		}
		//更新显示
		{
			std::stringstream ss(tacket);
			std::regex num_regex("\\d+(\\.\\d+)?");
			std::sregex_iterator iter_begin(std_str.begin(), std_str.end(), num_regex);
			std::sregex_iterator iter_end;
			size_t i = 0;
			while (iter_begin != iter_end) {
				if (tacket == (*iter_begin).str()) {
					break;
				}
				i++;
				iter_begin++;
			}
			std::string temp;
			for (int t = 0; t < i; ++t) {
				temp += src_stack[t] + src_operator[t];
			}
			temp += ss.str();
			src_str = QString::fromStdString(temp);
			ui->lineEdit->setText(src_str);
			ss.clear();
		}
    }
	QPushButton* btn = static_cast<QPushButton*>(sender());
	ui->statusBar->showMessage(btn->text() + "  button been clicked...");
}

bool MainWindow::is_has_consecutive_operators(const std::string& str) {
    std::string operators = "+-×÷";
    for (size_t i = 1; i < str.length(); ++i) {
        if (operators.find(str[i - 1]) != std::string::npos && //当前字符是运算符
            operators.find(str[i]) != std::string::npos) {  //上一个字符也是运算符
            return true;
        }
    }
    return false;
}

void MainWindow::process_mul_div(std::vector<std::string>& src_stack, std::vector<std::string>& src_operator,bool& is_lowdown)
{
    double left = 0;
	double right = 0;
	double result = 0;
    for (size_t i = 0; i < src_operator.size(); ++i) {
        if (src_operator[i] == "÷" || src_operator[i] == "×") {
            //为什么不用stringstream
            //------因为其定义及初始化
			if (0 == i && is_lowdown) {
				left = std::stod(src_stack[i]) * (- 1.0);
				is_lowdown = false;
			}
			else {
				left = std::stod(src_stack[i]);
			}
            right = std::stod(src_stack[i + 1]);
            if (src_operator[i] == "÷") {
                result = left / right;
            }
            else if (src_operator[i] == "×") {
                result = left * right;
            }
            //更新数组
            std::stringstream ss;
            ss << std::fixed << std::setprecision(6) << result;
            src_stack[i] = ss.str();
            ss.clear();
            //删除右侧的数字
            src_stack.erase(src_stack.begin() + i + 1);
            //删除对应的操作符
            src_operator.erase(src_operator.begin() + i);
            //因为数组缩短了
            //调整索引
            --i;
        }
    }
}

double MainWindow::process_add_sub(std::vector<std::string>& src_stack, std::vector<std::string>& src_operator,bool& is_lowdown)
{
	double result = 0;
	if (is_lowdown) {
		result = std::stod(src_stack[0]) * (-1.0);
		is_lowdown = false;
	}
	else {
		result = std::stod(src_stack[0]);
	}
    for (size_t i = 0; i < src_operator.size(); ++i) {
        if (src_operator[i] == "+") {

            result += std::stod(src_stack[i + 1]);
        }
        else if (src_operator[i] == "-") {
            result -= std::stod(src_stack[i + 1]);
        }
    }
    return result;
}

void MainWindow::do_result_Btn_clicked() {
    //读取"最后"一个数字
    //形如 89 =
	std::regex num_regex("\\d+(\\.\\d+)?");
    MainWindow::src_str = get_src_str();
	std::string std_str = src_str.toStdString();
	std::string last_match = find_the_last_string(num_regex, std_str);
    //qDebug() << last_match;
    src_stack.push_back(last_match);
	double result = 0;
    //进行计算
    if (src_stack.empty()) {    //没有数据做一个空处理
        QPushButton* btn = static_cast<QPushButton*>(sender());
        ui->statusBar->showMessage(btn->text() + "  button been clicked...");
    }
    else {
        process_mul_div(src_stack, src_operator,is_lowdown);
		result = process_add_sub(src_stack, src_operator,is_lowdown);
		if (is_lowdown) {
			result = result * (-1.0);
		}
        ui->lineEdit->setText(QString::number(result, 'f', 6));
		QPushButton* btn = static_cast<QPushButton*>(sender());
		ui->statusBar->showMessage(btn->text() + "  button been clicked...");
    }

	do_theEnd();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	for (auto it : btn_Map) {
		if (event->key() == it.first) {
			btn_Map[it.first]->animateClick();
		}
	}
}

void MainWindow::build_setBackGroundUI()
{
	this->setStyleSheet(
		"QMainWindow {"
		"background-color: #F5F5F5;"  // 背景颜色为浅灰色，柔和不刺眼
		"border: none;"               // 去除边框，保持简洁
		"}"
		"QStatusBar {"
		"background-color: #FFFFFF;"  // 底部状态栏为纯白色
		"border-top: 1px solid #DADADA;"  // 状态栏上方有细线分隔
		"}"
		"QToolBar {"
		"background-color: #FFFFFF;"  // 工具栏背景色为白色
		"border-bottom: 1px solid #DADADA;"  // 底部有一条浅色边框
		"padding: 5px;"               // 工具栏中的内容有些许内边距
		"}"
		"QMenuBar {"
		"background-color: #F9F9F9;"  // 菜单栏背景为略深的灰色
		"border-bottom: 1px solid #DADADA;"  // 边框分隔感
		"}"
		"QMenu {"
		"background-color: #FFFFFF;"  // 菜单项为白色
		"border: 1px solid #DADADA;"  // 菜单项的边框为浅灰色
		"}"
	);
}

void MainWindow::build_setBtnUI()
{
	for (auto it : btn_Map) {
		if (it.first >= Qt::Key_0 && it.first <= Qt::Key_9) {
			setBtnQss(it.second, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
		}
	}
}

void MainWindow::build_setLineUI()
{
    setLineQss(ui->lineEdit, "#DCE4EC", "#1ABC9C");
}

void MainWindow::setBtnQss(QPushButton* btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
	QStringList qss;
	qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
	qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
	qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
	btn->setStyleSheet(qss.join(""));
}

void MainWindow::setLineQss(QLineEdit* txt, QString normalColor, QString focusColor)
{
	QStringList qss;
	qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));
	qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));
	txt->setStyleSheet(qss.join(""));
}

std::string MainWindow::find_the_last_string(const std::regex& num_regex, const std::string str)
{
	std::string temp;
	std::sregex_iterator iter_begin(str.begin(), str.end(), num_regex);
	std::sregex_iterator iter_end;
	while (iter_begin != iter_end) {
		temp = (*iter_begin).str();
		iter_begin++;
	}
	return temp;
}

void MainWindow::do_theEnd()
{
	src_str.clear();    //初始为0
	src_stack.clear();
	src_operator.clear();
	operator_num = 0;
	is_lowdown = false;
	is_consecutive_operators = false;
	//“.”可用了
	ui->period_Btn->setEnabled(true);
}

