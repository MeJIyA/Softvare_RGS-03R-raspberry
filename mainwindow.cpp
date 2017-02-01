/////////////////////////
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QThread"
#include "QMouseEvent"
#include "QApplication"
#include "QMessageBox"
#include "QKeyEvent"
//#include "QtTest/QtTest"
//#include "QKeySequence"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);

     tmr = new QTimer(this);
     tmr->setInterval(2000); // Задаємо інтервал таймера

     tmr2 = new QTimer(this);
     tmr2->setInterval(200);
   //
    connect(tmr, SIGNAL(timeout()), this, SLOT(test_sost())); // Подключаем сигнал таймера к нашему слоту
    connect(tmr2, SIGNAL(timeout()), this, SLOT(blink())); // Подключаем сигнал таймера к нашему слоту
    //    tmr->start(); // Запускаем таймер
    setup();
}
bool ftOpen =0,test=0,canMode=0;
FT_HANDLE ftHandle;
FT_STATUS ftStatus;

int line_nmber = 0;

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::mousePressEvent(QMouseEvent *event)  // Знаходження місця кліку мишки для того щоб збільшити попадання
{
  if (event->localPos().x()>45 && event->localPos().x()<130 && event->localPos().y()>135 && event->localPos().y()< 195)
  {
      ui->lineEdit_21->setFocus();
  }
  if (event->localPos().x()>45 && event->localPos().x()<130 && event->localPos().y()>205 && event->localPos().y()< 260)
  {
      ui->lineEdit_22->setFocus();
  }
  if (event->localPos().x()>45 && event->localPos().x()<130 && event->localPos().y()>270 && event->localPos().y()< 335)
  {
      ui->lineEdit_23->setFocus();
  }


qDebug() << "x" << event->localPos().x();

qDebug() << event;
}

void MainWindow::setup()
{
 ui->pushButton_90->setEnabled(0);
 ui->radioButton->setVisible(0);

// ui->label_3->setStyleSheet("background-color: #00BF00");
  ui->label_3->setStyleSheet("background-color: orange");
 ui->label_25->setStyleSheet("background-color: #00BF00");
 ui->label_26->setStyleSheet("background-color: #00BF00");
 ui->label_28->setStyleSheet("background-color: #00BF00");
 ui->label_27->setStyleSheet("background-color: orange");
 ui->label_39->setStyleSheet("background-color: #00BF00");
 ui->label_49->setStyleSheet("background-color: #00BF00");
 ui->label_45->setStyleSheet("background-color: red");
 ui->label_4->setStyleSheet("background-color: orange");
 ui->label_5->setStyleSheet("background-color: orange");
 ui->label_20->setStyleSheet("background-color: #00BF00");
 ui->label_85->setStyleSheet("background-color: orange");
 ui->label_86->setStyleSheet("background-color: orange");
 ui->label_87->setStyleSheet("background-color: orange");
 ui->label_88->setStyleSheet("background-color: orange");
 ui->label_89->setStyleSheet("background-color: orange");
 ui->label_90->setStyleSheet("background-color: orange");
 // Window 1
 ui->label_29->setStyleSheet("background-color: orange");
 ui->label_30->setStyleSheet("background-color: orange");
 ui->label_31->setStyleSheet("background-color: orange");
 ui->label_34->setStyleSheet("background-color: orange");
 ui->label_37->setStyleSheet("background-color: orange");
 ui->label_43->setStyleSheet("background-color: orange");

 ui->label_55->setStyleSheet("background-color: #00BF00");
// Info Zone
 ui->label_50->setStyleSheet("background-color: orange");
 ui->label_51->setStyleSheet("background-color: orange");
 ui->label_105->setStyleSheet("background-color: orange");
 ui->label_107->setStyleSheet("background-color: orange");
 ui->label_108->setStyleSheet("background-color: red");
 ui->label_106->setStyleSheet("background-color: #00BF00");

ui->pushButton_key_clear->setStyleSheet("background-color: red");
ui->pushButton_key_enter->setStyleSheet("background-color: #00BF00");
ui->pushButton_key_0->setStyleSheet("background-color: silver");
ui->pushButton_key_1->setStyleSheet("background-color: silver");
ui->pushButton_key_2->setStyleSheet("background-color: silver");
ui->pushButton_key_3->setStyleSheet("background-color: silver");
ui->pushButton_key_4->setStyleSheet("background-color: silver");
ui->pushButton_key_5->setStyleSheet("background-color: silver");
ui->pushButton_key_6->setStyleSheet("background-color: silver");
ui->pushButton_key_7->setStyleSheet("background-color: silver");
ui->pushButton_key_8->setStyleSheet("background-color: silver");
ui->pushButton_key_9->setStyleSheet("background-color: silver");
ui->groupBox_keyboard->setStyleSheet("font-size: 20px");

 //QPixmap
 //ui->label_50->setPixmap();
}

/*******************************************************************************************
                    ВИЧТКА ВСТАНОВЛЕНИХ РЕЖИМІВ
********************************************************************************************/
void MainWindow::read_mode()
{
    if (ftOpen)
    {
        QByteArray RxBuffer;
        BYTE TxBuffer[20];
        BYTE sost,mode,addr;
        TxBuffer[0] = 0x00;
        TxBuffer[1] = 0x20;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        write(TxBuffer,6);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x92; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x20;
        TxBuffer[2] = 0x08;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        addr = RxBuffer[4];
        mode = RxBuffer[7];
        qDebug() << "MODE is" << mode;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1 && addr == 0x0a) // статус байт ОК
        {
            switch (mode)
            {
            case 0:
              //  ui->comboBox_2->setCurrentIndex(0);
                ui->listWidget->setCurrentRow(0);
                ui->label_101->setText("Режим установлен");
                ui->label_101->setStyleSheet("background-color: #00BF00");
                break;
            case 1:
                //ui->comboBox_2->setCurrentIndex(1);
                ui->listWidget->setCurrentRow(1);
                ui->label_101->setText("Режим установлен");
                ui->label_101->setStyleSheet("background-color: #00BF00");
                break;
            case 2:
                //ui->comboBox_2->setCurrentIndex(2);
                ui->listWidget->setCurrentRow(2);
                ui->label_101->setText("Режим установлен");
                ui->label_101->setStyleSheet("background-color: #00BF00");
                break;
            case 3:
                //ui->comboBox_2->setCurrentIndex(3);
                ui->listWidget->setCurrentRow(3);
                ui->label_101->setText("Режим установлен");
                ui->label_101->setStyleSheet("background-color: #00BF00");
                break;

            }
         }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
        }
    }
}

/*******************************************************************************************
*******************************************************************************************/


/*#############################################################################################
 *                                РОБОТА З CAN
 * ###########################################################################################*/

void MainWindow::CanInterface()

{
   // bool canMode=0;
    QByteArray RxBuffer;
    BYTE ACK,inpData;
  //  BYTE TxBuffer[10];
    if (ftOpen)
    {

    if (!canMode)    //Перехід в режим CAN
    {
        BYTE TxBuffer[1];
        TxBuffer[0]= 0xd1;
        write(TxBuffer,1);
        TxBuffer[0]=0xa0;
        write(TxBuffer,1);
        canMode=1;
        QThread::msleep(10);
    }
    if (canMode)
    {
        //перевіримо чи є дані для вичитки за допомогою RD_PENDING_F(0x30)
        BYTE TxBuffer[5];
        TxBuffer[0]= 0x00;
        TxBuffer[1]= 0xa0;
        TxBuffer[2]= 0x01;
        TxBuffer[3]= 0x01;
        TxBuffer[4]= 0x30; //CMD
        write(TxBuffer,5);
        TxBuffer[0]= 0x9a;
        write(TxBuffer,1);
        TxBuffer[0]= 0xa0;
        write(TxBuffer,1);
        flag();
        RxBuffer = read(); /*зчитуємо дані, далі будемо парсити (має бути один байт з встановленими бітами:
          0 RRS_PENDING
          1 RCT_PENDING
          2 COS_PENDING
          3 TAR_U_PENDING – группа ПЦУ ожидает в шлюзе;
          4 PYL_U_PENDING – номер пилона ожидает в шлюзе;
          5 BARK_U_PENDING – код Баркера ожидает в шлюзе;
          6,7 – не мають значення */
        ACK = RxBuffer[2];
        inpData = RxBuffer[3]; //байт с флагами ожидающих запросов или входящих данных шлюза
        if (ACK == 0x30 ) //перевіряємо чи АСК
        {
            if (inpData &= 1)  // RRS_PENDING
            {

            }
            if (inpData &= 2) // RCT_PENDING
            {

            }
            if (inpData &= 4) // COS_PENDING
            {

            }
            if (inpData &= 8) // TAR_U_PENDING – группа ПЦУ ожидает в шлюзе, вичитуємо дані та парсимо їх;
            {
                BYTE TxBuffer[5];
                TxBuffer[0]= 0x00;
                TxBuffer[1]= 0xa0;
                TxBuffer[2]= 0x01;
                TxBuffer[3]= 0x01;
                TxBuffer[4]= 0x34; //CMD
                write(TxBuffer,5);
                TxBuffer[0]= 0x9a;
                write(TxBuffer,1);
                TxBuffer[0]= 0xa0;
                write(TxBuffer,1);
                flag();
                RxBuffer = read();
                ACK = RxBuffer[2];

              // if (ACK == 0x30 )
            }
            if (inpData &= 16) // PYL_U_PENDING – номер пилона ожидает в шлюзе, вичитуємо дані та парсимо їх;
            {

            }
            if (inpData &= 32) // BARK_U_PENDING – код Баркера ожидает в шлюзе, вичитуємо дані та парсимо їх;
            {
                BYTE TxBuffer[5];
                TxBuffer[0]= 0x00;
                TxBuffer[1]= 0xa0;
                TxBuffer[2]= 0x01;
                TxBuffer[3]= 0x01;
                TxBuffer[4]= 0x36; //CMD
                write(TxBuffer,5);
                TxBuffer[0]= 0x9a;
                write(TxBuffer,1);
                TxBuffer[0]= 0xa0;
                write(TxBuffer,1);
                flag();
                RxBuffer = read();
                ACK = RxBuffer[2];
                if (ACK == 0x36)
                {
                 ui->lineEdit_7->setText(QString::number(RxBuffer[2],2));
                }
            }
        }
        else
        {
            QMessageBox::information(0, "Information", "Ошибка чтения RD_PENDING");
        }

    }
    }
}

/*##############################################################################################
 * #############################################################################################
 * #############################################################################################*/

void MainWindow::on_pushButton_89_clicked()
{
    if (ui->pushButton_90->isEnabled()==0)
    {
        ui->pushButton_90->setEnabled(1);
        ui->pushButton_89->setEnabled(0);
    }

}

void MainWindow::on_pushButton_90_clicked()
{
    if (ui->pushButton_89->isEnabled()==0)
    {
        ui->pushButton_90->setEnabled(0);
        ui->pushButton_89->setEnabled(1);
    }
}

void MainWindow::conect_disconect()
{
    // FT_HANDLE ftHandle;
    //  FT_STATUS ftStatus;
      //UCHAR BitMode;
      UCHAR Mask = 0xff;
      UCHAR Mode = 0x40;  // FIFO mode

      if (!ftOpen)
      {
      ftStatus = FT_Open(0, &ftHandle);
        if (ftStatus==FT_OK){
            //ftOpen=1;
            ftStatus = FT_SetBitMode(ftHandle, Mask, Mode);
            if (ftStatus == FT_OK) {
            ftOpen=1;
            qDebug() << "set bit mode FIFO" ;

            ui->label_5->setStyleSheet("background-color: #00FF00");
            ui->label_85->setStyleSheet("background-color: #00FF00");
            ui->radioButton->setVisible(1);

            ui->pushButton->setText("Disconect");

            test_sost(); //. !!!!!!!!!!!!!!!!
            read_mode();


            tmr->start();
            }
            return;
           }
        else
        {
            ftOpen=0;
            ui->pushButton->setText("Connect");
        }
      }
      if (ftOpen)
      {
          FT_Close(ftHandle);
       //   tmr2->stop();
          ui->radioButton->setChecked(0);
          ftOpen =0;
          ui->pushButton->setText("Conect");
          qDebug()<< "disconected";
          setup();

          tmr->stop();
          tmr2->stop();
      }
}

QByteArray MainWindow::read() // Ф-ція вичитки даних з ФІФО
{
    //  bool ok;
      //FT_HANDLE ftHandle;
    //  FT_STATUS ftStatus;
      DWORD EventDWord;
      DWORD TxBytes;
      DWORD RxBytes;
      DWORD BytesReceived;
      QByteArray data;

      FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);
    //  while (RxBytes < 1) {FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);}

      if (RxBytes > 0)
      {
            char RxBuffer[RxBytes];
      //    QByteArray data[RxBytes];
          qDebug() << "RxBytes" << RxBytes;
          qDebug() << " RxBytes is availabel";
      ftStatus = FT_Read(ftHandle,RxBuffer,RxBytes,&BytesReceived);
      if (ftStatus == FT_OK) {
       qDebug() << "FT_Read OK" ;
       //ui->textEdit->insertPlainText("FT_read OK \n");
      data.clear();
      qDebug() << data.length();
      for (uint i= 0; i<RxBytes; i++)
       {
           data[i] = RxBuffer[i];
       }
      }
      else
      {
       qDebug() << "FT_Read Failed";
      }
      }

  return data;
}

bool MainWindow::write(BYTE TxBuffer[], int len)  // ф-ЦІЯ ЗАПИСУ В ПОРТ
{
   DWORD BytesWritten;

    if(ftOpen != 1) // FT_Open failed
    {
        qDebug() << "device NOT opening";
    }
    if (ftOpen == 1) {
    ftStatus = FT_Write(ftHandle, TxBuffer, len, &BytesWritten);
    if (ftStatus == FT_OK) // FT_Write OK
    {
      return true;
    }
    else {
    qDebug() << "FT_Write Failed";
    return false;
    }
}
   return true;
}

bool MainWindow::flag() // перевірка статусу готованості
{
    int count;
    QByteArray flag;
    BYTE TxBuffer[3],point;
    TxBuffer[0] = 0x41;
    TxBuffer[1] = 0x00;
    TxBuffer[2] = 0x01;
    while (point!= 1)
    {
    write(TxBuffer,3);
    QThread::msleep(1);
    flag = read();
    point = flag[0];
    count+=1;
    }
  //  flag = read();
    qDebug() << "count:" << count;
    return true;
}

bool MainWindow::test(BYTE address)
{
   // if (ui->radioButton->isChecked()) {ui->radioButton->setChecked(0);}
 //   else { ui->radioButton->setChecked(1);}

    BYTE sost;
    QByteArray RxBuffer;
    BYTE TxBuffer[255];

    TxBuffer[0] = 0xd0;
    write(TxBuffer,1);
    TxBuffer[0] = 0xa0;
    write(TxBuffer,1);
    QThread::msleep(50);
    canMode=0;



    TxBuffer[0] = 0x05;
    TxBuffer[1] = 0x50;
    TxBuffer[2] = address; // адрес слейва(устройства)
    TxBuffer[3] = 0x00;
    TxBuffer[4] = 0x00;
    TxBuffer[5] = 0x01; // кількість данних які відправляємо

    TxBuffer[6] = 0x00;  // дані для тесту
//    TxBuffer[7] = 0xbb;
//    TxBuffer[8] = 0xcc;
//    TxBuffer[9] = 0xaa;
    write(TxBuffer,7);
//    if (flag()) qDebug() << "flag OK";
    QThread::msleep(10);
    TxBuffer[0] = 0x95; // задання секції таблиці
    write(TxBuffer,1);
   // if (flag()) qDebug() << "flag OK";
   QThread::msleep(10);
    TxBuffer[0] = 0xa0; // команда на виконання
    write(TxBuffer,1);
  //  if (flag()) qDebug() << "flag OK";
    QThread::msleep(10);
    TxBuffer[0] = 0x40;
    TxBuffer[1] = 0x50;
    TxBuffer[2] = 0x01;
    write(TxBuffer,3);
    QThread::msleep(50);
    RxBuffer = read();
    sost = RxBuffer[0]>>2;
    sost&=1;
    qDebug()<< sost;
    if (sost == 1) // статус байт ОК
    {
     //  ui->label_89->setStyleSheet("background-color: #00FF00");
      return true;
    }
    else
    {
     //ui->label_87->setStyleSheet("background-color: orange");
       return false;
    }

// return false;

 }
bool MainWindow::test_can() // Перевірка чи є підключення по CAN
{
    BYTE sost;
    QByteArray RxBuffer;
    BYTE TxBuffer[255];
    TxBuffer[0] = 0xd1;  // переключення в режим CAN
    write(TxBuffer,1);
    QThread::msleep(10);

    TxBuffer[0] = 0x00;
    TxBuffer[1] = 0xa0;
    TxBuffer[2] = 0x01;
    TxBuffer[3] = 0x01;
    TxBuffer[4] = 0x30;
    write(TxBuffer,5);
    QThread::msleep(10);
    TxBuffer[0] = 0x9a; // задання секції таблиці
    write(TxBuffer,1);
    QThread::msleep(10);
    TxBuffer[0] = 0xa0; // команда на виконання
    write(TxBuffer,1);
  //  if (flag()) qDebug() << "flag OK";
    QThread::msleep(10);
    TxBuffer[0] = 0x40;
    TxBuffer[1] = 0xa0;
    TxBuffer[2] = 0x03;
    write(TxBuffer,3);
    QThread::msleep(50);
    RxBuffer = read();
    sost = RxBuffer[2];
    qDebug()<< sost;

    TxBuffer[0] = 0xd0; // вихід з режиму CAN
    write(TxBuffer,1);
    QThread::msleep(10);
    TxBuffer[1] = 0xa0;
    write(TxBuffer,1);
    QThread::msleep(10);

    if (sost == 0x30) // возвращенная CMD = 30
    {
         return true;
    }
    else
    {
         return false;
    }
}

void MainWindow::test_sost()
{
tmr2->start();
    if (ftOpen)
    {

        if (test_can())  //проверка CAN
        {
           ui->label_4->setStyleSheet("background-color: #00FF00");
        }
        else
        {
          ui->label_4->setStyleSheet("background-color: orange");
        }

       if (test(0x03))
       {
         ui->label_89->setStyleSheet("background-color: #00FF00");
       }
       else
       {
         ui->label_89->setStyleSheet("background-color: orange");
       }
       if (test(0x16))
       {
         ui->label_86->setStyleSheet("background-color: #00FF00");
       }
       else
       {
         ui->label_86->setStyleSheet("background-color: orange");
       }
       if (test(0x0b))
       {
         ui->label_87->setStyleSheet("background-color: #00FF00");
       }
       else
       {
         ui->label_87->setStyleSheet("background-color: orange");
       }
       if (test(0x09))
       {
         ui->label_88->setStyleSheet("background-color: #00FF00");
       }
       else
       {
         ui->label_88->setStyleSheet("background-color: orange");
       }

     CanInterface();

  }
 //    ui->radioButton->setVisible(0);
  //  tmr2->stop();


}

void MainWindow::on_pushButton_clicked() // COnect/Disconect
{
    conect_disconect();
 //   test_sost();
//    read_mode();
}

void MainWindow::blink()
{
    if (ui->radioButton->isChecked()) {ui->radioButton->setChecked(0);}
    else { ui->radioButton->setChecked(1);}
}



// ******* ПЕРЕКЛЮЧЕННЯ РЕЖИМІВ РОБОТИ СИНХРОНІЗАТОРА*********

/*void MainWindow::on_comboBox_2_currentIndexChanged(int index)  // режим роботи синхронізатора
{
    QByteArray RxBuffer;
    BYTE TxBuffer[255];
    BYTE sost;
    if (ftOpen)
    {
    if (index == 0)
    {
        ui->lineEdit_185->setText("51.2");
        ui->lineEdit_186->setText("0.4");
        ui->lineEdit_187->setText("19.5");

        TxBuffer[0] = 0x05;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        TxBuffer[6] = 0x00;  // дані для режиму роботи

        write(TxBuffer,7);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x95; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x01;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1) // статус байт ОК
        {
         ui->label_101->setStyleSheet("background-color: #00BF00");

        }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
            ui->lineEdit_185->setText("-");
            ui->lineEdit_186->setText("-");
            ui->lineEdit_187->setText("-");
        }
    }
    if (index == 1)
    {
        ui->lineEdit_185->setText("40.96");
        ui->lineEdit_186->setText("0.5");
        ui->lineEdit_187->setText("24.4");

        TxBuffer[0] = 0x05;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        TxBuffer[6] = 0x01;  // дані для режиму роботи

        write(TxBuffer,7);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x95; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x01;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1) // статус байт ОК
        {
         ui->label_101->setStyleSheet("background-color: #00BF00");
        }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
            ui->lineEdit_185->setText("-");
            ui->lineEdit_186->setText("-");
            ui->lineEdit_187->setText("-");
        }
    }
    if (index == 2)
    {
        ui->lineEdit_185->setText("20.48");
        ui->lineEdit_186->setText("0.5");
        ui->lineEdit_187->setText("48.8");

        TxBuffer[0] = 0x05;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        TxBuffer[6] = 0x02;  // дані для режиму роботи

        write(TxBuffer,7);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x95; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x01;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1) // статус байт ОК
        {
         ui->label_101->setStyleSheet("background-color: #00BF00");
        }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
            ui->lineEdit_185->setText("-");
            ui->lineEdit_186->setText("-");
            ui->lineEdit_187->setText("-");
        }
    }
    if (index == 3)
    {
        ui->lineEdit_185->setText("10.24");
        ui->lineEdit_186->setText("0.5");
        ui->lineEdit_187->setText("97.7");

        TxBuffer[0] = 0x05;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        TxBuffer[6] = 0x03;  // дані для режиму роботи

        write(TxBuffer,7);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x95; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x01;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1) // статус байт ОК
        {
           ui->label_101->setStyleSheet("background-color: #00BF00");
        }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
        }
    }
    }
    ui->comboBox_2->setCurrentIndex(index);

} */

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    QByteArray RxBuffer;
    BYTE TxBuffer[255];
    BYTE sost;
    if (ftOpen)
    {
    if (currentRow == 0)
    {
        ui->lineEdit_185->setText("51.2");
        ui->lineEdit_186->setText("0.4");
        ui->lineEdit_187->setText("19.5");

        TxBuffer[0] = 0x05;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        TxBuffer[6] = 0x00;  // дані для режиму роботи

        write(TxBuffer,7);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x95; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x01;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1) // статус байт ОК
        {
         ui->label_101->setStyleSheet("background-color: #00BF00");

        }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
            ui->lineEdit_185->setText("-");
            ui->lineEdit_186->setText("-");
            ui->lineEdit_187->setText("-");
        }
    }
    if (currentRow == 1)
    {
        ui->lineEdit_185->setText("40.96");
        ui->lineEdit_186->setText("0.5");
        ui->lineEdit_187->setText("24.4");

        TxBuffer[0] = 0x05;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        TxBuffer[6] = 0x01;  // дані для режиму роботи

        write(TxBuffer,7);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x95; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x01;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1) // статус байт ОК
        {
         ui->label_101->setStyleSheet("background-color: #00BF00");
        }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
            ui->lineEdit_185->setText("-");
            ui->lineEdit_186->setText("-");
            ui->lineEdit_187->setText("-");
        }
    }
    if (currentRow == 2)
    {
        ui->lineEdit_185->setText("20.48");
        ui->lineEdit_186->setText("0.5");
        ui->lineEdit_187->setText("48.8");

        TxBuffer[0] = 0x05;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        TxBuffer[6] = 0x02;  // дані для режиму роботи

        write(TxBuffer,7);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x95; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x01;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1) // статус байт ОК
        {
         ui->label_101->setStyleSheet("background-color: #00BF00");
        }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
            ui->lineEdit_185->setText("-");
            ui->lineEdit_186->setText("-");
            ui->lineEdit_187->setText("-");
        }
    }
    if (currentRow == 3)
    {
        ui->lineEdit_185->setText("10.24");
        ui->lineEdit_186->setText("0.5");
        ui->lineEdit_187->setText("97.7");

        TxBuffer[0] = 0x05;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x0b; // адрес слейва(синхронизатор)
        TxBuffer[3] = 0x0a; // ADDR младший байт
        TxBuffer[4] = 0x00; // ADDR старший байт
        TxBuffer[5] = 0x01; // кількість данних які відправляємо
        TxBuffer[6] = 0x03;  // дані для режиму роботи

        write(TxBuffer,7);  // записуємо буфер (буфер, к-сть даних (байт))
    //    if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x95; // задання секції таблиці
        write(TxBuffer,1);
       // if (flag()) qDebug() << "flag OK";
       QThread::msleep(10);
        TxBuffer[0] = 0xa0; // команда на виконання
        write(TxBuffer,1);
      //  if (flag()) qDebug() << "flag OK";
        QThread::msleep(10);
        TxBuffer[0] = 0x40;
        TxBuffer[1] = 0x50;
        TxBuffer[2] = 0x01;
        write(TxBuffer,3);
        QThread::msleep(50);
        RxBuffer = read();
        sost = RxBuffer[0]>>2;
        sost&=1;
        qDebug()<< sost;
        if (sost == 1) // статус байт ОК
        {
           ui->label_101->setStyleSheet("background-color: #00BF00");
        }
        else
        {
            ui->label_101->setText("ОШИБКА!");
            ui->label_101->setStyleSheet("background-color: red");
        }
    }
    }

}

//************************************************************



void MainWindow::setFocus(int numb) // возврат фокуса лайн едиту та вставка значення
{
    switch(line_nmber)
    {
        case 1:
             if (numb==55)
             {
                ui->lineEdit->setText("");
                ui->lineEdit->setFocus();
             }
             else
             {
             ui->lineEdit->setText(ui->lineEdit->text() + QString::number(numb));
             ui->lineEdit->setFocus();
             }
             break;
        case 2:
            if (numb==55)
            {
               ui->lineEdit_2->setText("");
               ui->lineEdit_2->setFocus();
            }
            else
            {
             ui->lineEdit_2->setText(ui->lineEdit_2->text() + QString::number(numb));
             ui->lineEdit_2->setFocus();
            }
             break;
        case 3:
            if (numb==55)
            {
               ui->lineEdit_3->setText("");
               ui->lineEdit_3->setFocus();
            }
            else
            {
             ui->lineEdit_3->setText(ui->lineEdit_3->text() + QString::number(numb));
             ui->lineEdit_3->setFocus();
            }
             break;
        case 4:
            if (numb==55)
            {
               ui->lineEdit_4->setText("");
               ui->lineEdit_4->setFocus();
            }
            else
            {
             ui->lineEdit_4->setText(ui->lineEdit_4->text() + QString::number(numb));
             ui->lineEdit_4->setFocus();
            }
             break;
        case 5:
            if (numb==55)
            {
               ui->lineEdit_5->setText("");
               ui->lineEdit_5->setFocus();
            }
            else
            {
             ui->lineEdit_5->setText(ui->lineEdit_5->text() + QString::number(numb));
             ui->lineEdit_5->setFocus();
            }
             break;
        case 6:
            if (numb==55)
            {
               ui->lineEdit_6->setText("");
               ui->lineEdit_6->setFocus();
            }
            else
            {
             ui->lineEdit_6->setText(ui->lineEdit_6->text() + QString::number(numb));
             ui->lineEdit_6->setFocus();
            }
             break;
        case 7:
            if (numb==55)
            {
               ui->lineEdit_7->setText("");
               ui->lineEdit_7->setFocus();
            }
            else
            {
             ui->lineEdit_7->setText(ui->lineEdit_7->text() + QString::number(numb));
             ui->lineEdit_7->setFocus();
            }
             break;
        case 8:
            if (numb==55)
            {
               ui->lineEdit_8->setText("");
               ui->lineEdit_8->setFocus();
            }
            else
            {
             ui->lineEdit_8->setText(ui->lineEdit_8->text() + QString::number(numb));
             ui->lineEdit_8->setFocus();
            }
             break;
        case 9:
            if (numb==55)
            {
               ui->lineEdit_9->setText("");
               ui->lineEdit_9->setFocus();
            }
            else
            {
             ui->lineEdit_9->setText(ui->lineEdit_9->text() + QString::number(numb));
             ui->lineEdit_9->setFocus();
            }
             break;
        case 10:
            if (numb==55)
            {
               ui->lineEdit_10->setText("");
               ui->lineEdit_10->setFocus();
            }
            else
            {
             ui->lineEdit_10->setText(ui->lineEdit_10->text() + QString::number(numb));
             ui->lineEdit_10->setFocus();
            }
             break;
        case 11:
            if (numb==55)
            {
               ui->lineEdit_11->setText("");
               ui->lineEdit_12->setFocus();
            }
            else
            {
             ui->lineEdit_11->setText(ui->lineEdit_11->text() + QString::number(numb));
             ui->lineEdit_11->setFocus();
            }
             break;
        case 12:
            if (numb==55)
            {
               ui->lineEdit_12->setText(" ");
               ui->lineEdit_12->setFocus();
            }
            else
            {
             ui->lineEdit_12->setText(ui->lineEdit_12->text() + QString::number(numb));
             ui->lineEdit_12->setFocus();
            }
             break;
        case 13:
            if (numb==55)
            {
               ui->lineEdit_13->setText("");
               ui->lineEdit_13->setFocus();
            }
            else
            {
             ui->lineEdit_13->setText(ui->lineEdit_13->text() + QString::number(numb));
             ui->lineEdit_13->setFocus();
            }
             break;
        case 14:
            if (numb==55)
            {
               ui->lineEdit_14->setText("");
               ui->lineEdit_14->setFocus();
            }
            else
            {
             ui->lineEdit_14->setText(ui->lineEdit_14->text() + QString::number(numb));
             ui->lineEdit_14->setFocus();
            }
             break;
        case 15:
            if (numb==55)
            {
               ui->lineEdit_15->setText("");
               ui->lineEdit_15->setFocus();
            }
            else
            {
             ui->lineEdit_15->setText(ui->lineEdit_15->text() + QString::number(numb));
             ui->lineEdit_15->setFocus();
            }
             break;
        case 16:
            if (numb==55)
            {
               ui->lineEdit_16->setText("");
               ui->lineEdit_16->setFocus();
            }
            else
            {
             ui->lineEdit_16->setText(ui->lineEdit_16->text() + QString::number(numb));
             ui->lineEdit_16->setFocus();
            }
             break;
        case 17:
            if (numb==55)
            {
               ui->lineEdit_17->setText("");
               ui->lineEdit_17->setFocus();
            }
            else
            {
             ui->lineEdit_17->setText(ui->lineEdit_17->text() + QString::number(numb));
             ui->lineEdit_17->setFocus();
            }
             break;
        case 18:
            if (numb==55)
            {
               ui->lineEdit_18->setText("");
               ui->lineEdit_18->setFocus();
            }
            else
            {
             ui->lineEdit_18->setText(ui->lineEdit_18->text() + QString::number(numb));
             ui->lineEdit_18->setFocus();
            }
             break;
        case 19:
            if (numb==55)
            {
               ui->lineEdit_19->setText("");
               ui->lineEdit_19->setFocus();
            }
            else
            {
             ui->lineEdit_19->setText(ui->lineEdit_19->text() + QString::number(numb));
             ui->lineEdit_19->setFocus();
            }
             break;
        case 20:
            if (numb==55)
            {
               ui->lineEdit_20->setText("");
               ui->lineEdit_20->setFocus();
            }
            else
            {
             ui->lineEdit_20->setText(ui->lineEdit_20->text() + QString::number(numb));
             ui->lineEdit_20->setFocus();
            }
             break;
        case 21:
            if (numb==55)
            {
               ui->lineEdit_21->setText("");
               ui->lineEdit_21->setFocus();
            }
            else
            {
             ui->lineEdit_21->setText(ui->lineEdit_21->text() + QString::number(numb));
             ui->lineEdit_21->setFocus();
            }
             break;
        case 22:
            if (numb==55)
            {
               ui->lineEdit_22->setText("");
               ui->lineEdit_22->setFocus();
            }
            else
            {
             ui->lineEdit_22->setText(ui->lineEdit_22->text() + QString::number(numb));
             ui->lineEdit_22->setFocus();
            }
             break;
        case 23:
            if (numb==55)
            {
               ui->lineEdit_23->setText("");
               ui->lineEdit_23->setFocus();
            }
            else
            {
             ui->lineEdit_23->setText(ui->lineEdit_23->text() + QString::number(numb));
             ui->lineEdit_23->setFocus();
            }
             break;
        case 24:
            if (numb==55)
            {
               ui->lineEdit_24->setText("");
               ui->lineEdit_24->setFocus();
            }
            else
            {
             ui->lineEdit_24->setText(ui->lineEdit_24->text() + QString::number(numb));
             ui->lineEdit_24->setFocus();
            }
             break;
        case 25:
            if (numb==55)
            {
               ui->lineEdit_25->setText("");
               ui->lineEdit_25->setFocus();
            }
            else
            {
             ui->lineEdit_25->setText(ui->lineEdit_25->text() + QString::number(numb));
             ui->lineEdit_25->setFocus();
            }
             break;
        case 26:
            if (numb==55)
            {
               ui->lineEdit_26->setText("");
               ui->lineEdit_26->setFocus();
            }
            else
            {
             ui->lineEdit_26->setText(ui->lineEdit_26->text() + QString::number(numb));
             ui->lineEdit_26->setFocus();
            }
             break;
        case 27:
            if (numb==55)
            {
               ui->lineEdit_27->setText("");
               ui->lineEdit_27->setFocus();
            }
            else
            {
             ui->lineEdit_27->setText(ui->lineEdit_27->text() + QString::number(numb));
             ui->lineEdit_27->setFocus();
            }
             break;
        case 28:
            if (numb==55)
            {
               ui->lineEdit_28->setText("");
               ui->lineEdit_28->setFocus();
            }
            else
            {
             ui->lineEdit_28->setText(ui->lineEdit_28->text() + QString::number(numb));
             ui->lineEdit_28->setFocus();
            }
             break;
        case 29:
            if (numb==55)
            {
               ui->lineEdit_29->setText("");
               ui->lineEdit_29->setFocus();
            }
            else
            {
             ui->lineEdit_29->setText(ui->lineEdit_29->text() + QString::number(numb));
             ui->lineEdit_29->setFocus();
            }
             break;
        case 30:
            if (numb==55)
            {
               ui->lineEdit_30->setText("");
               ui->lineEdit_30->setFocus();
            }
            else
            {
             ui->lineEdit_30->setText(ui->lineEdit_30->text() + QString::number(numb));
             ui->lineEdit_30->setFocus();
            }
             break;
        case 31:
            if (numb==55)
            {
               ui->lineEdit_31->setText("");
               ui->lineEdit_31->setFocus();
            }
            else
            {
             ui->lineEdit_31->setText(ui->lineEdit_31->text() + QString::number(numb));
             ui->lineEdit_31->setFocus();
            }
             break;
        case 32:
            if (numb==55)
            {
               ui->lineEdit_32->setText("");
               ui->lineEdit_32->setFocus();
            }
            else
            {
             ui->lineEdit_32->setText(ui->lineEdit_32->text() + QString::number(numb));
             ui->lineEdit_32->setFocus();
            }
             break;
        case 33:
            if (numb==55)
            {
               ui->lineEdit_33->setText("");
               ui->lineEdit_33->setFocus();
            }
            else
            {
             ui->lineEdit_33->setText(ui->lineEdit_33->text() + QString::number(numb));
             ui->lineEdit_33->setFocus();
            }
             break;
        case 34:
            if (numb==55)
            {
               ui->lineEdit_34->setText("");
               ui->lineEdit_34->setFocus();
            }
            else
            {
             ui->lineEdit_34->setText(ui->lineEdit_34->text() + QString::number(numb));
             ui->lineEdit_34->setFocus();
            }
             break;
        case 35:
            if (numb==55)
            {
               ui->lineEdit_35->setText("");
               ui->lineEdit_35->setFocus();
            }
            else
            {
             ui->lineEdit_35->setText(ui->lineEdit_35->text() + QString::number(numb));
             ui->lineEdit_35->setFocus();
            }
             break;
        case 36:
            if (numb==55)
            {
               ui->lineEdit_36->setText("");
               ui->lineEdit_36->setFocus();
            }
            else
            {
             ui->lineEdit_36->setText(ui->lineEdit_36->text() + QString::number(numb));
             ui->lineEdit_36->setFocus();
            }
             break;
        case 37:
            if (numb==55)
            {
               ui->lineEdit_37->setText("");
               ui->lineEdit_37->setFocus();
            }
            else
            {
             ui->lineEdit_37->setText(ui->lineEdit_37->text() + QString::number(numb));
             ui->lineEdit_37->setFocus();
            }
             break;
        case 38:
            if (numb==55)
            {
               ui->lineEdit_38->setText("");
               ui->lineEdit_38->setFocus();
            }
            else
            {
             ui->lineEdit_38->setText(ui->lineEdit_38->text() + QString::number(numb));
             ui->lineEdit_38->setFocus();
            }
             break;
        case 39:
            if (numb==55)
            {
               ui->lineEdit_39->setText("");
               ui->lineEdit_39->setFocus();
            }
            else
            {
             ui->lineEdit_39->setText(ui->lineEdit_39->text() + QString::number(numb));
             ui->lineEdit_39->setFocus();
            }
             break;
        case 40:
            if (numb==55)
            {
               ui->lineEdit_40->setText("");
               ui->lineEdit_40->setFocus();
            }
            else
            {
             ui->lineEdit_40->setText(ui->lineEdit_40->text() + QString::number(numb));
             ui->lineEdit_40->setFocus();
            }
             break;
        case 51:
            if (numb==55)
            {
               ui->lineEdit_51->setText("");
               ui->lineEdit_51->setFocus();
            }
            else
            {
             ui->lineEdit_31->setText(ui->lineEdit_51->text() + QString::number(numb));
             ui->lineEdit_31->setFocus();
            }
             break;
        case 52:
            if (numb==55)
            {
               ui->lineEdit_52->setText("");
               ui->lineEdit_52->setFocus();
            }
            else
            {
             ui->lineEdit_52->setText(ui->lineEdit_52->text() + QString::number(numb));
             ui->lineEdit_52->setFocus();
            }
             break;
        case 53:
            if (numb==55)
            {
               ui->lineEdit_53->setText("");
               ui->lineEdit_53->setFocus();
            }
            else
            {
             ui->lineEdit_53->setText(ui->lineEdit_53->text() + QString::number(numb));
             ui->lineEdit_53->setFocus();
            }
             break;
        case 54:
            if (numb==55)
            {
               ui->lineEdit_54->setText("");
               ui->lineEdit_54->setFocus();
            }
            else
            {
             ui->lineEdit_54->setText(ui->lineEdit_54->text() + QString::number(numb));
             ui->lineEdit_54->setFocus();
            }
             break;
        case 55:
            if (numb==55)
            {
               ui->lineEdit_55->setText("");
               ui->lineEdit_55->setFocus();
            }
            else
            {
             ui->lineEdit_55->setText(ui->lineEdit_55->text() + QString::number(numb));
             ui->lineEdit_55->setFocus();
            }
             break;
        case 56:
            if (numb==55)
            {
               ui->lineEdit_56->setText("");
               ui->lineEdit_56->setFocus();
            }
            else
            {
             ui->lineEdit_56->setText(ui->lineEdit_56->text() + QString::number(numb));
             ui->lineEdit_56->setFocus();
            }
             break;
        case 57:
            if (numb==55)
            {
               ui->lineEdit_57->setText("");
               ui->lineEdit_57->setFocus();
            }
            else
            {
             ui->lineEdit_57->setText(ui->lineEdit_57->text() + QString::number(numb));
             ui->lineEdit_57->setFocus();
            }
             break;
        case 58:
            if (numb==55)
            {
               ui->lineEdit_58->setText("");
               ui->lineEdit_58->setFocus();
            }
            else
            {
             ui->lineEdit_58->setText(ui->lineEdit_58->text() + QString::number(numb));
             ui->lineEdit_58->setFocus();
            }
             break;
        case 59:
            if (numb==55)
            {
               ui->lineEdit_59->setText("");
               ui->lineEdit_59->setFocus();
            }
            else
            {
             ui->lineEdit_59->setText(ui->lineEdit_59->text() + QString::number(numb));
             ui->lineEdit_59->setFocus();
            }
             break;
        case 60:
            if (numb==55)
            {
         //      ui->lineEdit_60->setText("");
        //       ui->lineEdit_60->setFocus();
            }
            else
            {
         //    ui->lineEdit_60->setText(ui->lineEdit_60->text() + QString::number(numb));
        //     ui->lineEdit_60->setFocus();
            }
             break;

    }
}

void MainWindow::on_pushButton_key_1_clicked()
{
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier, "1", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_1, Qt::NoModifier, "1", true, 1));
   //  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier, 0);
  //   QApplication::postEvent(this, event);
    //QGuiApplication::focusObject()
//     QKeyEvent keyPressed(QKeyEvent::KeyPress, '1', Qt::NoModifier);
 //       QWidget::keyPressEvent(&keyPressed);
}

void MainWindow::on_pushButton_key_2_clicked()
{
   // setFocus(2);
 //   keybd_event('2',0,0,0);
 //   keybd_event('2',0,KEYEVENTF_KEYUP,0);  // for windows
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_2, Qt::NoModifier, "2", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_2, Qt::NoModifier, "2", true, 1));
}

void MainWindow::on_pushButton_key_3_clicked()
{
   // setFocus(3);
 //   keybd_event('3',0,0,0);
 //   keybd_event('3',0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_3, Qt::NoModifier, "3", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_3, Qt::NoModifier, "3", true, 1));
}

void MainWindow::on_pushButton_key_4_clicked()
{
   //  setFocus(4);
//   keybd_event('4',0,0,0);
  //  keybd_event('4',0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_4, Qt::NoModifier, "4", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_4, Qt::NoModifier, "4", true, 1));
}

void MainWindow::on_pushButton_key_5_clicked()
{
    //setFocus(5);
 //   keybd_event('5',0,0,0);
 //   keybd_event('5',0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_5, Qt::NoModifier, "5", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_5, Qt::NoModifier, "5", true, 1));
}

void MainWindow::on_pushButton_key_6_clicked()
{
    //setFocus(6);
   // keybd_event('6',0,0,0);
  //  keybd_event('6',0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_6, Qt::NoModifier, "6", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_6, Qt::NoModifier, "6", true, 1));
}
void MainWindow::on_pushButton_key_7_clicked()
{
    //setFocus(7);
  //  keybd_event('7',0,0,0);
 //  keybd_event('7',0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_7, Qt::NoModifier, "7", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_7, Qt::NoModifier, "7", true, 1));
}

void MainWindow::on_pushButton_key_8_clicked()
{
   // setFocus(8);
  //  keybd_event('8',0,0,0);
  //  keybd_event('8',0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_8, Qt::NoModifier, "8", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_8, Qt::NoModifier, "8", true, 1));
}
void MainWindow::on_pushButton_key_9_clicked()
{
  // setFocus(9);
 //   keybd_event('9',0,0,0);
  // keybd_event('9',0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_9, Qt::NoModifier, "9", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_9, Qt::NoModifier, "9", true, 1));
}

void MainWindow::on_pushButton_key_0_clicked()
{
    //setFocus(0);
    //keybd_event('0',0,0,0);
  //  keybd_event('0',0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_0, Qt::NoModifier, "0", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_0, Qt::NoModifier, "0", true, 1));
}

void MainWindow::on_pushButton_key_clear_clicked()
{
  // setFocus(55);
 //   keybd_event(VK_CONTROL,0,0,0);
 //   keybd_event('A',0,0,0);
 //   keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
 //   keybd_event('A',0,KEYEVENTF_KEYUP,0);
 //   keybd_event(VK_DELETE,0,0,0);
 //   keybd_event(VK_DELETE,0,KEYEVENTF_KEYUP,0);
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, "", true, 1));
    QCoreApplication::sendEvent(QApplication::focusWidget(), new QKeyEvent(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier, "", true, 1));
}

void MainWindow::on_pushButton_key_enter_clicked()
{
   // setFocus(4);
}

/*
void MainWindow::on_lineEdit_10_editingFinished()
{
    line_nmber = 10;
}

void MainWindow::on_lineEdit_21_editingFinished()
{
    line_nmber = 21;
}

void MainWindow::on_lineEdit_22_editingFinished()
{
    line_nmber = 22;
}

void MainWindow::on_lineEdit_23_editingFinished()
{
    line_nmber = 23;
}

void MainWindow::on_lineEdit_11_editingFinished()
{
    line_nmber = 11;
}

void MainWindow::on_lineEdit_14_editingFinished()
{
    line_nmber = 14;
}

void MainWindow::on_lineEdit_9_editingFinished()
{
    line_nmber = 9;
}

void MainWindow::on_lineEdit_12_editingFinished()
{
    line_nmber = 12;
}

void MainWindow::on_lineEdit_16_editingFinished()
{
    line_nmber = 16;
}

void MainWindow::on_lineEdit_13_editingFinished()
{
    line_nmber = 13;
}

void MainWindow::on_lineEdit_15_editingFinished()
{
    line_nmber = 15;
}

void MainWindow::on_lineEdit_18_editingFinished()
{
    line_nmber = 18;
}

void MainWindow::on_lineEdit_20_editingFinished()
{
    line_nmber = 20;
}

void MainWindow::on_lineEdit_17_editingFinished()
{
    line_nmber = 17;
}

void MainWindow::on_lineEdit_19_editingFinished()
{
    line_nmber = 19;
}

void MainWindow::on_lineEdit_editingFinished()
{
     line_nmber = 1;
}

void MainWindow::on_lineEdit_2_editingFinished()
{
     line_nmber = 2;
}

void MainWindow::on_lineEdit_3_editingFinished()
{
     line_nmber = 3;
}

void MainWindow::on_lineEdit_4_editingFinished()
{
     line_nmber = 4;
}

void MainWindow::on_lineEdit_24_editingFinished()
{
    line_nmber = 24;
}


void MainWindow::on_lineEdit_58_editingFinished()
{
     line_nmber = 58;
}

void MainWindow::on_lineEdit_59_editingFinished()
{
    line_nmber = 59;
}
void MainWindow::on_lineEdit_5_editingFinished()
{
    line_nmber = 5;
}
*/

void MainWindow::on_pushButton_81_clicked()
{
    bool ok;
    int num;
    QString str;
    str = ui->lineEdit_57->text();
    num = str.toInt(&ok);
    if (num < 15){ num +=1;}
    ui->lineEdit_57->setText(QString::number(num));
}

void MainWindow::on_pushButton_80_clicked()
{
    bool ok;
    int num;
    QString str;
    str = ui->lineEdit_57->text();
    num = str.toInt(&ok);
    if (num > 0){  num -=1;}
    ui->lineEdit_57->setText(QString::number(num));
}

void MainWindow::on_pushButton_84_clicked()
{
    bool ok;
    int num;
    QString str;
    str = ui->lineEdit_188->text();
    num = str.toInt(&ok);
    if (num < 9){ num +=1;}
    ui->lineEdit_188->setText(QString::number(num));
}

void MainWindow::on_pushButton_85_clicked()
{
    bool ok;
    int num;
    QString str;
    str = ui->lineEdit_188->text();
    num = str.toInt(&ok);
    if (num > 0){  num -=1;}
    ui->lineEdit_188->setText(QString::number(num));
}






void MainWindow::on_pushButton_87_clicked() // запись литер подсвета синтезатора и частоты
{
    bool ok;
    int num1,num2,disc;
    double freq;
    QString str;
    BYTE data, data2;
   // QByteArray RxBuffer;
    BYTE TxBuffer[255];
    str = ui->lineEdit_57->text(); // litera obzora
    num1 = str.toInt(&ok);
    str = ui->lineEdit_188->text(); // litera podsveta
    num2 = str.toInt(&ok);
 if (ftOpen && !canMode){
    data = num1;
    TxBuffer[0] = 0x05;
    TxBuffer[1] = 0x50;
    TxBuffer[2] = 0x16; // адрес слейва(synth)
    TxBuffer[3] = 0x01;  // адрес регистра
    TxBuffer[4] = 0x00;
    TxBuffer[5] = 0x02; // кількість данних які відправляємо
    TxBuffer[6] = data;  // дані
    TxBuffer[7] = 0x00;
    write(TxBuffer,8);
   //QThread::msleep(10);
    TxBuffer[0] = 0x95; // задання секції таблиці
    write(TxBuffer,1);
    TxBuffer[0] = 0xa0; // команда на виконання
    write(TxBuffer,1);
    QThread::msleep(10);

    data = num2;
    TxBuffer[0] = 0x05;
    TxBuffer[1] = 0x50;
    TxBuffer[2] = 0x16; // адрес слейва(synth)
    TxBuffer[3] = 0x02;  // адрес регистра
    TxBuffer[4] = 0x00;
    TxBuffer[5] = 0x02; // кількість данних які відправляємо
    TxBuffer[6] = data;  // дані
    TxBuffer[7] = 0x00;
    write(TxBuffer,8);

//    QThread::msleep(10);
    TxBuffer[0] = 0x95; // задання секції таблиці
    write(TxBuffer,1);
    TxBuffer[0] = 0xa0; // команда на виконання
    write(TxBuffer,1);
    QThread::msleep(10);

    str = ui->lineEdit_189->text(); // litera podsveta
    freq = str.toDouble(&ok);
    disc = freq/12.5;

    data = disc; // msb
    data2 = disc>>8; //lsb
    TxBuffer[0] = 0x05;
    TxBuffer[1] = 0x50;
    TxBuffer[2] = 0x16; // адрес слейва(synth)
    TxBuffer[3] = 0x03;  // адрес регистра
    TxBuffer[4] = 0x00;
    TxBuffer[5] = 0x02; // кількість данних які відправляємо
    TxBuffer[6] = data;  // дані
    TxBuffer[7] = data2;
    write(TxBuffer,8);
    TxBuffer[0] = 0x95; // задання секції таблиці
    write(TxBuffer,1);
    TxBuffer[0] = 0xa0; // команда на виконання
    write(TxBuffer,1);
    QThread::msleep(10);

    qDebug() << "disc:" << disc;
    qDebug() << "lsb:" << data;
    qDebug() << "msb:" << data2;

}

}
