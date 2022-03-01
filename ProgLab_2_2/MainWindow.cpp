#include "MainWindow.h"

#include "Archive.h"
#include "CurrencyRate.h"
#include "CurrencyTableModel.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    CurrencyRate main_rate(MAINURL);
    main_rate.validateRate();

    CurrencyTableModel *model = new CurrencyTableModel();

    model->populate(main_rate);
    this->ui->tableView->setModel(model);

    connect(ui->tableView, &QTableView::clicked, this,
            &MainWindow::showDynamics);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showDynamics(const QModelIndex &idx) {
    if (idx.column() != 6) {
        return;
    }

    delete chart;

    QWidget *widget = new QWidget;
    widget->setWindowTitle("Dynamics");

    chart = new DynChartWidget(idx.row(), _cash_);
    spin_box = new QSpinBox;
    spin_box->setMinimum(7);
    spin_box->setMaximum(365);
    spin_box->setValue(PERIOD);

    connect(spin_box, &QSpinBox::editingFinished, this,
            &MainWindow::updateChart);

    layout = new QVBoxLayout;
    layout->addWidget(chart);
    layout->addWidget(spin_box);

    widget->setLayout(layout);
    widget->show();
}

void MainWindow::updateChart() { chart->refresh(spin_box->value(), _cash_); }
