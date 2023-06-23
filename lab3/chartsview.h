#ifndef CHARTSVIEW_H
#define CHARTSVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QVBoxLayout>
#include <QLabel>
#include <QPdfWriter>
#include <QFileDialog>
#include <QMessageBox>

class Chart
{
public:
    Chart() {}
    virtual ~Chart() = default;

    virtual QtCharts::QAbstractSeries* getSeries(const QMap<QString, QVariant>& data) = 0;
};

class PieChart : public Chart
{
public:
    ~PieChart() { delete m_series; }

    QtCharts::QAbstractSeries* getSeries(const QMap<QString, QVariant>& data) override;
    QtCharts::QPieSeries *m_series;
};

class BarChart : public Chart
{
public:
    ~BarChart() { delete m_series; }

    QtCharts::QAbstractSeries* getSeries(const QMap<QString, QVariant>& data) override;
    QtCharts::QStackedBarSeries* m_series;
};

class ChartsView : public QWidget
{
    Q_OBJECT
public:
    ChartsView(QWidget *parent = nullptr);
    ~ChartsView() {}

public slots:
    void slUpdateChart();
    void slChangeColorPalette(bool blackOrWhite);
    void slPrint();
    void slSetChartType(Chart* newType);
    void slSetData(const QMap<QString, QVariant>& data);

private:
    QtCharts::QChartView *m_chartView;
    QVBoxLayout *m_chartLayout;
    QtCharts::QChart *m_chart;
    Chart *m_chartType;
    QMap<QString, QVariant> m_currentData;
};

#endif // CHARTSVIEW_H
