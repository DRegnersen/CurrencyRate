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
    chart = new DynChartWidget(idx.row(), _cash_);
    chart->show();
}
