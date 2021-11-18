#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"trajet.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
 //   void on_tableWidget_cellActivated(int row, int column);

    void on_pb_ajouter_clicked();

    void on_supprimer_clicked();

  //  void on_pushButton_clicked();

    void on_modifier_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    trajet *Etmp;
};

#endif // MAINWINDOW_H
