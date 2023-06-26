#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSplitter>

#include "filesview.h"
#include "buttons.h"
#include "chartsview.h"
#include "registr.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    static Window& getInstance()
    {
        static Window instance;
        return instance;
    }

public slots:
    void slChooseFolder();
    void slCurrentFileChanged(QModelIndex index);  //QMI - инд модели данных(содержит ном стр и столб, указ на род инд)
    void slTypeChanged(QString type);

signals:
    void signFolderChange(QString path);
    void signUpdateChart();
    void signUpdateChartData(const QMap<QString, QVariant>& newData);
    void signUpdateChartType(Chart *type);
    void signUpdateFileType(QFileInfo fileInfo, int maxSize = 1000000);

private:
    Window(QWidget* parent = nullptr);

    Buttons* m_buttons;
    FilesView* m_filesView;
    ChartsView* m_chartsView;
    Registr* m_registr;
};

#endif // MAINWINDOW_H
