#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"metro.h"
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

   void on_pb_trier_nbrplaces_clicked();



   void on_pb_trier_kilometrage_clicked();

private:
   Ui::MainWindow *ui;
   Metro M ;
};

#endif // MAINWINDOW_H
