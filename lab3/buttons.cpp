#include "buttons.h"

Buttons::Buttons(QWidget* parent) : QWidget(parent)
{
    m_openFolder = new QPushButton("Открыть папку", this);
    m_openFolder->setFixedHeight(27);

    m_print = new QPushButton("Печать", this);
    m_print->setFixedHeight(25);

    m_chartTypeLabel = new QLabel("Тип диаграммы", this);
    m_chartTypeLabel->setFixedHeight(25);

    m_chartType = new QComboBox(this);
    m_chartType->addItem("Pie Chart");
    m_chartType->addItem("Bar Chart");
    m_chartType->setFixedHeight(25);

    m_blackOrWhite = new QCheckBox(this);
    m_blackOrWhite->setFixedHeight(25);

    m_blackOrWhiteLabel = new QLabel("Черно-белый график", this);
    m_blackOrWhiteLabel->setFixedHeight(25);

    QHBoxLayout* comboboxLayout = new QHBoxLayout();

    comboboxLayout->addWidget(m_chartTypeLabel);
    comboboxLayout->addWidget(m_chartType);

    QHBoxLayout* checkboxLayout = new QHBoxLayout();

    checkboxLayout->addWidget(m_blackOrWhite);
    checkboxLayout->addWidget(m_blackOrWhiteLabel);

    QHBoxLayout* hLayout = new QHBoxLayout(this);

    hLayout->addWidget(m_openFolder);
    hLayout->addWidget(m_print);
    hLayout->addLayout(comboboxLayout);
    hLayout->addLayout(checkboxLayout);
    hLayout->addStretch();
}
