#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAINURL QUrl("https://www.cbr-xml-daily.ru/daily_json.js")
#define PERIOD 30

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

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

    void updateChart();

   private:
    Ui::MainWindow *ui;

    DynChartWidget *chart = nullptr;
    QSpinBox *spin_box = nullptr;
    QVBoxLayout *layout = nullptr;
    QWidget *widget = nullptr;

    Archive _cash_;
};
#endif  // MAINWINDOW_H
