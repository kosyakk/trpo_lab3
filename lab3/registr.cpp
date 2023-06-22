#include "registr.h"
#include "ioccontainer.h"

Registr::Registr()
{
    gContainer.RegisterFactory<IDataReader, NullReader>();
}

std::shared_ptr<IDataReader> Registr::getObject()
{
    return gContainer.GetObject<IDataReader>();
}

void Registr::slChangeFileType(QFileInfo fileInfo, int maxSize)
{
    if (fileInfo.size() > maxSize)
    {
        emit signChangeChartData(QMap<QString, QVariant>());

        gContainer.RegisterFactory<IDataReader, NullReader>();

        return;
    }

    QString suffix = fileInfo.suffix();
    if (suffix == "json")
    {
        gContainer.RegisterFactory<IDataReader, JsonDataReader>();
    }
    else
    {
        gContainer.RegisterFactory<IDataReader, NullReader>();
    }
}
