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
    void slCurrentFileChanged(QModelIndex index);
    void slTypeChanged(QString type);

signals:
    void signFolderChange(QString path);
    void signUpdateChart();
    void signShowPlaceholder(QString str);
    void signUpdateChartData(const QMap<QString, QVariant>& newData);
    void signUpdateChartType(Chart *type);
    void signUpdateFileType(QFileInfo fileInfo, int maxSize = 1000000);

private:
    Window(QWidget* parent = 0);

    Buttons* m_buttons;
    FilesView* m_filesView;
    ChartsView* m_chartsView;
    Registr* m_registr;
};

#endif // MAINWINDOW_H