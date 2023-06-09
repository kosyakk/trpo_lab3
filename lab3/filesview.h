#ifndef FILESVIEW_H
#define FILESVIEW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>

class FilesView : public QWidget
{
    Q_OBJECT
public:
    FilesView(QWidget *parent);
    ~FilesView() {}

    QItemSelectionModel *m_selectionModel;

public slots:
    void slOnSelectionChange(QString folderPath);

private:
    QFileSystemModel* m_model;      //модель файловой системы
    QTableView* m_tableView;        //виджет таблицы
    QVBoxLayout* m_vLayout;
};

#endif // FILESVIEW_H
