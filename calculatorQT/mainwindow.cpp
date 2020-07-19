#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcValue = 0.0;
bool divTrigger = false;
bool multiTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->displayLE->setText(QString::number(calcValue));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; ++i)
    {
        QString btnName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(btnName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(numPressed()));
    }
    connect(ui->btnPlus, SIGNAL(released()), this,
            SLOT(mathBtnPressed()));
    connect(ui->btnSubtract, SIGNAL(released()), this,
            SLOT(mathBtnPressed()));
    connect(ui->btnMultiply, SIGNAL(released()), this,
            SLOT(mathBtnPressed()));
    connect(ui->btnDevide, SIGNAL(released()), this,
            SLOT(mathBtnPressed()));
    connect(ui->btnEqual, SIGNAL(released()), this,
            SLOT(mathBtnPressed()));
    connect(ui->btnChangeSign, SIGNAL(released()), this,
            SLOT(mathBtnPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();
    QString displayValue = ui->displayLE->text();
    if (displayValue.toDouble() == 0 || (displayValue.toDouble() == 0.0))
    {
        ui->displayLE->setText(btnVal);
    }
    else
    {
        QString newVal = displayValue + btnVal;
        double dblNewValue = newVal.toDouble();
        ui->displayLE->setText(QString::number(dblNewValue, 'g', 16));
    }
}

void MainWindow::mathBtnPressed()
{
    divTrigger = false;
    multiTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->displayLE->text();
    calcValue = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString btnValue = button->text();

    if(QString::compare(btnValue, "/", Qt::CaseSensitive)==0)
    {
        divTrigger = true;
    } else if(QString::compare(btnValue, "*", Qt::CaseSensitive)==0)
    {
        multiTrigger = true;
    } else if(QString::compare(btnValue, "+", Qt::CaseSensitive)==0)
    {
        addTrigger = true;
    } else
    {
        subTrigger = true;
    }
    ui->displayLE->setText("");
}

void MainWindow::equalBtn()
{
    double result = 0.0;
    QString displayVal = ui->displayLE->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multiTrigger || divTrigger)
    {
        if(addTrigger)
        {
            result = calcValue + displayVal;
        } else if(subTrigger)
        {
            result = calcValue - displayVal;
        } else if(multiTrigger)
        {
            result = calcValue * displayVal;
        }
        else
        {
            result = calcValue / dblDisplayVal;
        }
    }
    ui->displayLE->setText(QString::number(result));
}

void MainWindow::changeNumSign()
{
    QString displayVal = ui->displayLE->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->displayLE->setText(QString::number(dblDisplayValSign));
    }
}































