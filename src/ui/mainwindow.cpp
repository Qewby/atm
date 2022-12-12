#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QDir>
#include <server/services/ServiceFactory.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->incorrectTries = 0;
    this->pin="";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_TurnOff_clicked()
{
    if(this->currentState == TURNED_OFF){
        this->currentState = WAITING_FOR_CARD;
        ui->pushButton_TurnOff->setText("TurnOff");
        ui->textBrowser_Info->setText("ATM turned on. Please insert card");
    }else{
        this->currentState = TURNED_OFF;
        ui->pushButton_TurnOff->setText("TurnOn");
        ui->textBrowser_Info->setText("ATM turned off");
    }
}

QString MainWindow::showEnterCardDialog(){
    bool ok;
    QString text;
    do
    text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Card number:"), QLineEdit::Normal,
                                         "", &ok);
    while (!(ok && !text.isEmpty()));
    return text;
}

double MainWindow::showMoneyAmountDialog(QString msg, double min, double max){
    bool ok = false;
    double amount;
    do
    amount = QInputDialog::getDouble(this, tr("QInputDialog::getText()"),
                                         msg, QLineEdit::Normal,
                                     min, max, 0, &ok);
    while (!ok);
    return amount;
}

void MainWindow::on_pushButton_InsertCard_clicked()
{
    if(this->currentState == WAITING_FOR_CARD){
        QString number = showEnterCardDialog();
        currentCard = ReadedCardInfo(number.toStdString());
        ValidStatus res = server.validate(currentCard);
        if(res == ValidStatus::Valid){
            this->currentState = WAITING_FOR_PIN;
            ui->textBrowser_Info->setText("Please enter your pin and press Ok\nTo delete last digit press <-\nTo retrieve card press Cancel");
        }else if (res == ValidStatus::InvalidCardInfo){
            ui->textBrowser_Info->setText("Incorrect card number. Insert correct card");
        }else{
            ui->textBrowser_Info->setText("Not compatible card network. Insert correct card");
        }
    }
}

void MainWindow::digitButtonClickedAny(std::string digit)
{
    if(this->currentState == WAITING_FOR_PIN||currentState == WAITING_FOR_NEW_PIN){
            pin.append(digit);
            ui->textBrowser_Info->setText("Your pin\n"+QString(pin.length(), QChar('*')));
        }else if(this->currentState == CHOOSING_ACTION){
            if(digit.compare("1")==0){
                double amount = server.getBalance();
                ui->textBrowser_PrintOut->setText(QString::fromStdString("Your card " + currentCard.getNumber()+"\nYour balance: "+ std::to_string(amount)));
                this->currentState = ASKING_FOR_MORE_ACTIONS;
                ui->textBrowser_Info->setText("Do you want to do more actions? Press Ok/Cancel");
            }else if(digit.compare("2")==0){
                amountToWithdraw = showMoneyAmountDialog("Enter amount of cash to withdraw", 0, 150000);
                if(server.canWithdraw(amountToWithdraw)){
                    this->currentState = ASKING_TO_CONFIRM_WITHDRAW;
                    ui->textBrowser_Info->setText(QString::fromStdString("Amount "+std::to_string(amountToWithdraw)+"\nFee "+std::to_string(server.getWithdrawalFee(amountToWithdraw))+"\nAre you sure to withdraw?"));
                }else{
                    this->currentState = ASKING_FOR_MORE_ACTIONS;
                    ui->textBrowser_Info->setText("Not enough balance to do withdraw.\nDo you want to do more actions? Press Ok/Cancel");
                }
                ServiceFactory::getCardService() ;
            }else if(digit.compare("3")==0){
                currentState = WAITING_FOR_NEW_PIN;
                pin.clear();
                ui->textBrowser_Info->setText("Enter your new pin"+QString(pin.length(), QChar('*')));
            }
        }
}


void MainWindow::on_pushButton_1_clicked()
{
    digitButtonClickedAny("1");
}


void MainWindow::on_pushButton_2_clicked()
{
    digitButtonClickedAny("2");
}


void MainWindow::on_pushButton_3_clicked()
{
    digitButtonClickedAny("3");
}


void MainWindow::on_pushButton_4_clicked()
{
    digitButtonClickedAny("4");
}


void MainWindow::on_pushButton_5_clicked()
{
    digitButtonClickedAny("5");
}


void MainWindow::on_pushButton_6_clicked()
{
    digitButtonClickedAny("6");
}


void MainWindow::on_pushButton_7_clicked()
{
    digitButtonClickedAny("7");
}


void MainWindow::on_pushButton_8_clicked()
{
    digitButtonClickedAny("8");
}


void MainWindow::on_pushButton_9_clicked()
{
    digitButtonClickedAny("9");
}


void MainWindow::on_pushButton_0_clicked()
{
    digitButtonClickedAny("0");
}


void MainWindow::on_pushButton_Backspace_clicked()
{
    if(this->currentState == WAITING_FOR_PIN){
        if(pin.length()>0){
            pin.resize(pin.size()-1);
            ui->textBrowser_Info->setText("Your pin\n"+QString(pin.length(), QChar('*')));
        }
    }else if(this->currentState == WAITING_FOR_NEW_PIN){
        if(pin.length()>0){
            pin.resize(pin.size()-1);
            ui->textBrowser_Info->setText("Your new pin\n"+QString(pin.length(), QChar('*')));
        }
    }
}


void MainWindow::on_pushButton_Ok_clicked()
{
    if(this->currentState == CARD_BLOCKED){
        this->currentState = WAITING_FOR_CARD;
        ui->textBrowser_Info->setText("Card unblocked. Insert card please");
    }else if(this->currentState == WAITING_FOR_PIN){
        bool res = server.authenticate(currentCard, pin);
        this->pin.clear();
        if(res){
            this->currentState = CHOOSING_ACTION;
            ui->textBrowser_Info->setText("Choose action:\n1. Check balance\n2. Withdraw cash\n3. Change pin\nPress Cancel to get your card back");
            incorrectTries = 0;
        }else{
            ui->textBrowser_Info->setText("Incorrect pin\nTry again.");
            if(++incorrectTries >= 3){
                this->currentState = CARD_BLOCKED;
                ui->textBrowser_Info->setText("Card blocked. To unblock press Ok");
            }
        }
    }else if(this->currentState == WAITING_FOR_NEW_PIN){
        bool res = server.changePinCode(pin);
        this->pin.clear();
        this->currentState = ASKING_FOR_MORE_ACTIONS;
        if(res){
            ui->textBrowser_Info->setText("Successfully changed pin.\nDo you want to do more actions? Press Ok/Cancel");
        }else{
            ui->textBrowser_Info->setText("Failed attempt to change pin.\nDo you want to do more actions? Press Ok/Cancel");
        }
    }else if(this->currentState == ASKING_FOR_MORE_ACTIONS){
        this->currentState = WAITING_FOR_PIN;
        this->pin.clear();
        ui->textBrowser_Info->setText("Please enter your pin and press Ok\nTo delete last digit press <-\nTo retrieve card press Cancel");
    }else if(this->currentState == ASKING_TO_CONFIRM_WITHDRAW){
        server.withdraw(amountToWithdraw);
        ui->textBrowser_PrintOut->setText("You successfully withdraw " + QString::fromStdString(std::to_string(amountToWithdraw)));
        this->currentState = ASKING_FOR_MORE_ACTIONS;
        ui->textBrowser_Info->setText("Do you want to do more actions? Press Ok/Cancel");
    }
}


void MainWindow::on_pushButton_Cancel_clicked()
{
    if(this->currentState == WAITING_FOR_PIN){
        this->currentState = WAITING_FOR_CARD;
        this->pin.clear();
        this->incorrectTries = 0;
        ui->textBrowser_Info->setText("Card retrieved. Please insert new card");
    }else if(currentState == WAITING_FOR_NEW_PIN||currentState == ASKING_TO_CONFIRM_WITHDRAW){
        currentState = ASKING_FOR_MORE_ACTIONS;
        ui->textBrowser_Info->setText("Choose action:\n1. Check balance\n2. Withdraw cash\n3. Change pin\nPress Cancel to get your card back");
    }else if(currentState == ASKING_FOR_MORE_ACTIONS||currentState == CHOOSING_ACTION){
        server.finishSession();
        this->currentState = WAITING_FOR_CARD;
        ui->textBrowser_Info->setText("Card retrieved. Press insert card");
    }
}

