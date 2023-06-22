#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

Window::Window(QWidget *parent)
{
    Q_UNUSED(parent);

    setWindowTitle("Charts");
    this->setGeometry(0, 0, 1500, 800);

    m_filesView = new FilesView(this);
    m_buttons = new Buttons(this);
    m_chartsView = new ChartsView(this);
    m_registr = new Registr();

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    QSplitter *splitter = new QSplitter(this);

    m_filesView->setMaximumWidth(800);
    m_buttons->setMaximumHeight(50);
    m_chartsView->setMinimumSize(200, 200);

    splitter->addWidget(m_filesView);
    splitter->addWidget(m_chartsView);

    vLayout->addWidget(m_buttons);
    vLayout->addWidget(splitter);

    connect(this, &Window::signFolderChange, m_filesView, &FilesView::slOnSelectionChange);
    connect(this, &Window::signUpdateChart, m_chartsView, &ChartsView::slUpdateChart);
    connect(this, &Window::signUpdateChartData, m_chartsView, &ChartsView::slSetData);
    connect(this, &Window::signUpdateChartType, m_chartsView, &ChartsView::slSetChartType);
    connect(this, &Window::signUpdateFileType, m_registr, &Registr::slChangeFileType);

    connect(m_registr, &Registr::signChangeChartData, m_chartsView, &ChartsView::slSetData);

    connect(m_filesView->selectionModel, &QItemSelectionModel::currentChanged, this, &Window::slCurrentFileChanged);

    connect(m_buttons->m_openFolder, &QPushButton::clicked, this, &Window::slChooseFolder);
    connect(m_buttons->m_print, &QPushButton::clicked, m_chartsView, &ChartsView::slPrint);

    connect(m_buttons->m_blackOrWhite, &QCheckBox::stateChanged, m_chartsView, &ChartsView::slChangeColorPalette);
    connect(m_buttons->m_chartType, &QComboBox::currentTextChanged, this, &Window::slTypeChanged);
}

void Window::slChooseFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "", QDir::homePath(), QFileDialog::ShowDirsOnly);
    if (folderPath != "")
    {
        emit signFolderChange(folderPath);
    }
}

void Window::slCurrentFileChanged(QModelIndex index)
{
    QFileSystemModel *fileModel = new QFileSystemModel(this);

    emit signUpdateFileType(fileModel->fileInfo(index));

    QVariant data = m_registr->getObject()->getData(fileModel->fileInfo(index));
    QMap<QString, QVariant> temp = data.toMap();

    if (temp.size() > 0)
    {
        emit signUpdateChartData(temp);
    }

    delete fileModel;
}

void Window::slTypeChanged(QString type)
{
    if (type == "Bar Chart")
    {
        emit signUpdateChartType(new BarChart());
    }
    else if (type == "Pie Chart")
    {
        emit signUpdateChartType(new PieChart());
    }
}
