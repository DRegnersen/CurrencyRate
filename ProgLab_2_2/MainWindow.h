#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAINURL QUrl("https://www.cbr-xml-daily.ru/daily_json.js")
#include <QMainWindow>

#include "DynChartWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   public slots:

    void showDynamics(const QModelIndex &idx);

   private:
    Ui::MainWindow *ui;
    DynChartWidget *chart = nullptr;
};
#endif  // MAINWINDOW_H
