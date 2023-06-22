#include "filesview.h"

FilesView::FilesView(QWidget *parent) : QWidget(parent) {

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    QString homePath =  QDir::homePath();

    m_model = new QFileSystemModel(this);
    m_model->setFilter(QDir::Files);

    QStringList filters;
    filters << "*.json";

    m_model->setNameFilters(filters);
    m_model->setNameFilterDisables(false);

    m_model->setRootPath(homePath);

    m_tableView = new QTableView;
    m_tableView->setModel(m_model);

    vLayout->addWidget(m_tableView);

    selectionModel = m_tableView->selectionModel();

    m_tableView->setRootIndex(m_model->setRootPath(homePath));
}

void FilesView::slOnSelectionChange(QString path)
{
    QString filePath = path;

    m_tableView->setRootIndex(m_model->setRootPath(filePath));
}
