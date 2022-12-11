#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QDir>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_TurnOff_clicked()
{
    if(this->currentState == TURNED_OFF){
        this->currentState = WAITING_FOR_CARD;
    }else{
        this->currentState = TURNED_OFF;
    }
}

QString MainWindow::showEnterCardDialog(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Card number:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        return text;
}

void MainWindow::on_pushButton_InsertCard_clicked()
{
    if(this->currentState == WAITING_FOR_CARD){
        QString number = showEnterCardDialog();
        currentCard = ACard(number.toStdString());

    }
}

void MainWindow::on_digitButton_clicked(std::string digit){
    if(this->currentState == WAITING_FOR_PIN){
        pin.append(digit);
    }else if(this->currentState == CHOOSING_ACTION){

    }
}

void MainWindow::on_pushButton_1_clicked()
{
    on_digitButton_clicked("1");
}


void MainWindow::on_pushButton_2_clicked()
{
    on_digitButton_clicked("2");
}


void MainWindow::on_pushButton_3_clicked()
{
    on_digitButton_clicked("3");
}


void MainWindow::on_pushButton_4_clicked()
{
    on_digitButton_clicked("4");
}


void MainWindow::on_pushButton_5_clicked()
{
    on_digitButton_clicked("5");
}


void MainWindow::on_pushButton_6_clicked()
{
    on_digitButton_clicked("6");
}


void MainWindow::on_pushButton_7_clicked()
{
    on_digitButton_clicked("7");
}


void MainWindow::on_pushButton_8_clicked()
{
    on_digitButton_clicked("8");
}


void MainWindow::on_pushButton_9_clicked()
{
    on_digitButton_clicked("9");
}


void MainWindow::on_pushButton_0_clicked()
{
    on_digitButton_clicked("0");
}


void MainWindow::on_pushButton_Backspace_clicked()
{
    if(this->currentState == WAITING_FOR_PIN){
        if(pin.length()>0){
            pin.resize(pin.size()-1);
        }
    }
}


void MainWindow::on_pushButton_Ok_clicked()
{
    if(this->currentState == CARD_BLOCKED){
        this->currentState = WAITING_FOR_CARD;
    }else if(this->currentState == WAITING_FOR_PIN){

    }
}


void MainWindow::on_pushButton_Cancel_clicked()
{

}

