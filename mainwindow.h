#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"metro.h"
#include "arduino.h"

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
     void on_ajouter_clicked();

   void on_pb_supprimer_clicked();

   void on_pb_modifier_clicked();

   void on_pb_trier_matricule_clicked();





   void on_pb_rechercher_clicked();

   void on_tabWidget_currentChanged(int index);


   void on_pb_pdf_2_clicked();

   void on_AFFECTER_clicked();
   void update_label();


private:
   Ui::MainWindow *ui;
   Metro M ;
   arduino a;
   QByteArray data;
};

#endif // MAINWINDOW_H
