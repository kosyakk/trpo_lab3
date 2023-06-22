#include "datareader.h"

QVariant JsonDataReader::getData(const QFileInfo fileInfo)
{
    QFile file(fileInfo.filePath());
    QString jsonString;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        jsonString = file.readAll();
        file.close();
    }
    else
    {
        qDebug() << "Error: file not found.";
        m_data = QVariant::fromValue(nullptr);
        return m_data;
    }

    QJsonParseError jsonError;
    auto jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8(), &jsonError);

    if (jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "Error parsing JSON:" << jsonError.errorString();
        m_data = QVariant::fromValue(nullptr);
        return m_data;
    }

    if (!jsonDocument.isArray())
    {
        qDebug() << "Error: JSON document is not an array.";
        m_data = QVariant::fromValue(nullptr);
        return m_data;
    }

    QJsonArray jArr = jsonDocument.array();
    QJsonValue val;

    QString key;
    QMap<QString, QVariant> keyValue;

    for (auto jsonObj : jArr)
    {
        val = jsonObj.toObject().value("Time");
        key = val.toString();

        val = jsonObj.toObject().value("Value");
        keyValue[key] = val;
    }

    m_data = QVariant::fromValue(keyValue);
    return m_data;
}

QVariant NullReader::getData(const QFileInfo fileInfo)
{
    Q_UNUSED(fileInfo);
    return QVariant::fromValue(QMap<QString, QVariant>());
}

