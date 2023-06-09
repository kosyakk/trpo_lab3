#include "chartsview.h"

ChartsView::ChartsView(QWidget*)
{
    m_chartLayout = new QVBoxLayout(this);

    m_chartView = new QtCharts::QChartView();

    m_chartView->setRenderHint(QPainter::Antialiasing);

    m_chart = m_chartView->chart();

    m_chart->setTheme(QtCharts::QChart::ChartThemeLight);

    m_chart->legend()->hide();
    m_chartType = new PieChart();
}

void ChartsView::slSetChartType(Chart *newType)
{
    if (newType != nullptr)
    {
        m_chartType = newType;
        if (m_currentData.size() > 0)
        {
            slUpdateChart();
        }
    }
}

void ChartsView::slSetData(const QMap<QString, QVariant>& data)
{
    if(data.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("Error"));
        return;
    }

    m_currentData = data;
    slUpdateChart();
}

void ChartsView::slUpdateChart()
{
    m_chart->removeAllSeries();

    QtCharts::QAbstractSeries *series = m_chartType->getSeries(m_currentData);
    m_chart->addSeries(series);

    m_chart->createDefaultAxes();

    m_chartLayout->addWidget(m_chartView);
    m_chartView->show();
}

void ChartsView::slChangeColorPalette(bool blackOrWhite)
{
    if (blackOrWhite == true)
    {
        m_chart->setTheme(QtCharts::QChart::ChartThemeHighContrast);
    }
    else
    {
        m_chart->setTheme(QtCharts::QChart::ChartThemeLight);
    }

    if (m_currentData.size() > 0)
    {
        slUpdateChart();
    }
}

void ChartsView::slPrint()
{
    if (m_currentData.size() == 0)
    {
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), QDir::homePath(), tr("PDF Files (*.pdf)"));

    QPdfWriter writer(fileName);

    writer.setCreator("Charts");

    writer.setPageSize(QPagedPaintDevice::A4);

    QPainter painter(&writer);

    m_chartView->render(&painter);
    painter.end();
}

QtCharts::QAbstractSeries *PieChart::getSeries(const QMap<QString, QVariant>& data)
{
    m_series = new QtCharts::QPieSeries();
    QMapIterator<QString, QVariant> i(data);
    while (i.hasNext())
    {
        i.next();
        m_series->append(i.key(), i.value().toDouble());
    }
    return m_series;
}

QtCharts::QAbstractSeries *BarChart::getSeries(const QMap<QString, QVariant>& data)
{
    m_series = new QtCharts::QStackedBarSeries();
    QMapIterator<QString, QVariant> i(data);
    QtCharts::QBarSet *set = new QtCharts::QBarSet("");
    while (i.hasNext())
    {
        i.next();
        *set << i.value().toDouble();
    }
    m_series->append(set);

    return m_series;
}
