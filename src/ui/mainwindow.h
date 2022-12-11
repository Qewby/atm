#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <server/cards/ACard.h>
enum State{
        TURNED_OFF,
        WAITING_FOR_CARD,
        WAITING_FOR_PIN,
        CARD_BLOCKED,
        CHOOSING_ACTION,
        CHOOSING_MONEY_FOR_WITHDRAWING,
        WAITING_FOR_CARD_TO_TRANSFER_TO,
        WAITING_FOR_MONEY_TO_TOP_UP,
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

    void on_pushButton_1_clicked();
    void on_digitButton_clicked(std::string);
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
    State currentState;
    ACard currentCard;
    ACard cardForTransfer;
    std::string pin;


    QString showEnterCardDialog();
};

#endif // MAINWINDOW_H
