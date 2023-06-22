#ifndef REGISTR_H
#define REGISTR_H

#include <QObject>
#include <memory>

#include "datareader.h"

class Registr : public QObject
{
    Q_OBJECT
public:
    Registr();

    std::shared_ptr<IDataReader> getObject();

public slots:
    void slChangeFileType(QFileInfo fileInfo, int maxSize);

signals:
    void signChangeChartData(const QMap<QString, QVariant> &data);
};

#endif // REGISTR_H
