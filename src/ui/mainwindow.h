#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <server/local/LocalServer.h>
#include <utils/ReadedCardInfo.h>
enum State{
        TURNED_OFF,
        WAITING_FOR_CARD,
        WAITING_FOR_PIN,
        CARD_BLOCKED,
        CHOOSING_ACTION,
        ENTERING_AMOUNT_TO_WITHDRAW,
        ASKING_FOR_MORE_ACTIONS,
        ASKING_TO_CONFIRM_WITHDRAW,
        WAITING_FOR_NEW_PIN,
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_TurnOff_clicked();

    void on_pushButton_InsertCard_clicked();

    void digitButtonClickedAny(std::string digit);

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_Backspace_clicked();

    void on_pushButton_Ok_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::MainWindow *ui;
    State currentState = TURNED_OFF;
    ReadedCardInfo currentCard;
    double amountToWithdraw;
    std::string pin;
    size_t incorrectTries;
    LocalServer server;

    QString showEnterCardDialog();
    double showMoneyAmountDialog(QString msg, double min, double max);
};

#endif // MAINWINDOW_H
