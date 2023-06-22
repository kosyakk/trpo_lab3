#ifndef BUTTONS_H
#define BUTTONS_H

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class Buttons : public QWidget
{
    Q_OBJECT
public:
    Buttons(QWidget* parent = nullptr);
    ~Buttons() {}

    QComboBox* m_chartType;
    QLabel* m_chartTypeLabel;
    QCheckBox* m_blackOrWhite;
    QLabel* m_blackOrWhiteLabel;
    QPushButton* m_print;
    QPushButton* m_openFolder;
};

#endif // BUTTONS_H
