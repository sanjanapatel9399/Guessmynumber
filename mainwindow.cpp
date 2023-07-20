#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    foreach (QAbstractButton *temp, ui->buttonGroup->buttons()) {

        connect(temp, SIGNAL(clicked()), SLOT(enable()));

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->label_3->setText("0 ile "+ QString::number(arg1)+" The number guessing game between 0 and 10 is starting...");
}


void MainWindow::on_pushButton_clicked()
{
    ran = rand() % ui->spinBox->value();
    ui->label_6->setText(QString::number(ran));

}

void MainWindow::enable(){

    QObject *ob = sender();

    foreach(QAbstractButton *btn, ui->buttonGroup->buttons()){

        if(ob==btn){

            if(btn->text()=="Single-player"){
                ui->listWidget_2->setEnabled(false);
                ui->listWidget->setEnabled(true);
            }

            else{
                ui->listWidget->setEnabled(true);
                ui->listWidget_2->setEnabled(true);
            }

        }

    }


}

void MainWindow::tahmin(int rn, int max, int id, QListWidget *widget){

    int temp;
    int count = 0;

    for (;;) {

        count+=1;
        temp = rand() % max;
        widget->addItem(QString::number(temp));

        if(temp==rn){

            widget->addItem("Number of attempts: "+QString::number(count));

            if(id==1){

                oyuncu1 = count;
            }
            else if(id==2){
                oyuncu2 = count;
            }

            return;

        }

    }

}

void MainWindow::on_pushButton_2_clicked()
{

    ui->listWidget->clear();
    ui->listWidget_2->clear();
    oyuncu1=-99;
    oyuncu2=-99;

    if(ran==-1){
        QMessageBox *mg;
        mg->critical(0,"Warning!!","Please select a random number!!");
        return;
    }

    else if(!ui->listWidget->isEnabled() && !(ui->listWidget_2->isEnabled())){

        QMessageBox *mg;
        mg->critical(0,"Warning!!","Please enter the number of players!!");

        return;

    }

    else if(ui->listWidget->isEnabled() && !(ui->listWidget_2->isEnabled())){

        std::thread oyuncu1(tahmin,ran,ui->spinBox->value(),1, ui->listWidget);
        oyuncu1.detach();
        oyuncu2=-88;

    }

    else if(ui->listWidget->isEnabled() && ui->listWidget_2->isEnabled()){

        std::thread oyuncu1(tahmin,ran,ui->spinBox->value(),1, ui->listWidget);
        oyuncu1.detach();

        std::thread oyuncu2(tahmin,ran,ui->spinBox->value(),2, ui->listWidget_2);
        oyuncu2.detach();

    }

    for (;;) {

        if(oyuncu1!=-99 && oyuncu2!=-99){

            if(oyuncu2==-88 || oyuncu1<oyuncu2){

                QMessageBox *mg;
                mg->information(0,"Congratulations!","Congratulations Oyuncu 1, "+QString::number(oyuncu1)+" YOU WON on your attempt!!");
                break;
            }

            else{

                QMessageBox *mg;
                mg->information(0,"Congratulations!","Congratulations Oyuncu 2, "+QString::number(oyuncu2)+"YOU WON on your attempt!!!!!");
                break;

            }

        }
    }

}
