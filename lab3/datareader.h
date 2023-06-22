#ifndef DATAREADER_H
#define DATAREADER_H

#include <QFileInfo>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class IDataReader
{
public:
    virtual ~IDataReader() {}
    virtual QVariant getData(const QFileInfo fileInfo) = 0;

protected:
    QVariant m_data;
};

class JsonDataReader : public IDataReader
{
public:
    JsonDataReader() {}
    QVariant getData(const QFileInfo fileInfo) override;
};

class NullReader : public IDataReader
{
public:
    NullReader() {}
    QVariant getData(const QFileInfo fileInfo) override;
};

#endif // DATAREADER_H
