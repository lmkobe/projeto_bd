#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>

#include "updateinterface.h"

UpdateInterface::UpdateInterface(QWidget *parent)
  : QWidget(parent),
    m_buttons({
              new QPushButton("Parques"),
              new QPushButton("Festas no Parque"),
              new QPushButton("Festas no Cruzeiro")
              }),
    m_checkedButton(-1),
    m_keyLineEdit(new QLineEdit),
    m_updateBox(new QGroupBox),
    m_database("UpdateConn")
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Make buttons toggleable
    for(QPushButton *but: m_buttons){
        but->setCheckable(true);
    }

    // Connect signals on the buttons
    for(QPushButton *but: m_buttons){
        connect(but, &QPushButton::clicked, this, [this, but](void){
            // Empty the delete box
            this->cleanUpdateBox();

            // Disable all buttons
            for(QPushButton *b: m_buttons)
                b->setChecked(false);

            // Enable current button
            but->setChecked(true);

            // Update m_checkedButton to reflect which button is pressed
            m_checkedButton = m_buttons.indexOf(but);
        });
    }

    // Toggle first button as default
    m_checkedButton = 0;
    m_buttons[m_checkedButton]->setChecked(true);

    // Create button box
    QGroupBox *buttonBox = new QGroupBox;
    // Rows of buttons will be placed vertically on the button box
    QVBoxLayout *mainButLayout = new QVBoxLayout(buttonBox);
    QHBoxLayout *butLayout1 = new QHBoxLayout(); // Row 1
    mainButLayout->addLayout(butLayout1);
    butLayout1->addWidget(m_buttons[0]);
    butLayout1->addWidget(m_buttons[1]);
    butLayout1->addWidget(m_buttons[2]);

    // Create the box for the LineEdit for writing the 'key' by which we will search on the database
    QFormLayout *keyInputLayout = new QFormLayout;
    keyInputLayout->addRow("Chave da busca", m_keyLineEdit);

    // Connect signal on the line edit for when the user presses enter
    connect(m_keyLineEdit, &QLineEdit::returnPressed, this, [this](){
        QString line = m_keyLineEdit->text();
        if(this->m_checkedButton == 0){
            this->beginUpdate1(line);
        }
    });

    // Create Group Box where the updating will happen
    m_updateBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_updateBox->setLayout(new QFormLayout);

    mainLayout->addWidget(buttonBox);
    mainLayout->addLayout(keyInputLayout);
    mainLayout->addWidget(m_updateBox);
}

void UpdateInterface::cleanUpdateBox(){
    delete m_updateBox->layout();

    auto children = m_updateBox->children();
    for(auto &child: children){
        delete child;
    }

    m_updateBox->setLayout(new QFormLayout);
}

void UpdateInterface::beginUpdate1(QString searchKey){
    // Clean update box
    cleanUpdateBox();

    m_updateBox->layout()->addWidget(new QLabel("Chave encontrada."));
}

void UpdateInterface::handleWrongKey(){
    // Clean update box first
    cleanUpdateBox();

    m_updateBox->layout()->addWidget(new QLabel("Chave não encontrada."));
}