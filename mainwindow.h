#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qdebug.h"
#include <QMainWindow>
#include <QTimer>
#ifdef _WIN32
#include "ftd2xx.h"
#else
    #include "ftd2xx.h"
#endif


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void mousePressEvent(QMouseEvent *event);

private slots:
 //  void mousePressEvent(QMouseEvent *event);

   void setup();
   void read_mode();

   void on_pushButton_89_clicked();
   void on_pushButton_90_clicked();

   void conect_disconect();
   void test_sost();
   bool test(BYTE address);
   bool test_can();
   bool write(BYTE TxBuffer[], int len);
   QByteArray read();
   bool flag();

   void on_pushButton_clicked();
   void blink();

   void setFocus(int numb);



   void on_pushButton_key_1_clicked();

 /*  void on_lineEdit_10_editingFinished();

   void on_lineEdit_21_editingFinished();

   void on_lineEdit_22_editingFinished();

   void on_lineEdit_23_editingFinished();

   void on_lineEdit_11_editingFinished();

   void on_lineEdit_14_editingFinished();

   void on_lineEdit_9_editingFinished();

   void on_lineEdit_12_editingFinished();

   void on_lineEdit_16_editingFinished();

   void on_lineEdit_13_editingFinished();

   void on_lineEdit_15_editingFinished();

   void on_lineEdit_18_editingFinished();

   void on_lineEdit_20_editingFinished();

   void on_lineEdit_17_editingFinished();

   void on_lineEdit_19_editingFinished();

   void on_lineEdit_editingFinished();

   void on_lineEdit_2_editingFinished();

   void on_lineEdit_3_editingFinished();

   void on_lineEdit_4_editingFinished();
   void on_lineEdit_24_editingFinished();
   void on_lineEdit_58_editingFinished();

   void on_lineEdit_59_editingFinished();
   void on_lineEdit_5_editingFinished();

*/

   void on_pushButton_key_2_clicked();

   void on_pushButton_key_3_clicked();

   void on_pushButton_key_4_clicked();

   void on_pushButton_key_5_clicked();

   void on_pushButton_key_6_clicked();

   void on_pushButton_key_7_clicked();

   void on_pushButton_key_8_clicked();

   void on_pushButton_key_9_clicked();

   void on_pushButton_key_clear_clicked();

   void on_pushButton_key_0_clicked();

   void on_pushButton_key_enter_clicked();


 //  void on_comboBox_2_currentIndexChanged(int index);


   void on_pushButton_81_clicked();

   void on_pushButton_80_clicked();

   void on_pushButton_84_clicked();

   void on_pushButton_85_clicked();

 //  void on_listView_clicked(const QModelIndex &index);

   void on_listWidget_currentRowChanged(int currentRow);




   void CanInterface();

   void on_pushButton_87_clicked();

private:
    QTimer *tmr;
    QTimer *tmr2;
    Ui::MainWindow *ui;
#ifdef _WIN32
    FT_HANDLE ftHandle;
#else
    struct ftdi_context *ftdic;
#endif
};


#endif // MAINWINDOW_H
