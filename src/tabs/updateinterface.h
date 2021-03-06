#ifndef DELETIONINTERFACE_H
#define DELETIONINTERFACE_H

#include <QWidget>
#include <QVector>
#include <QString>
#include "database/eisedatabase.h"

class QPushButton;
class QLineEdit;
class QGroupBox;

class UpdateInterface: public QWidget
{
    Q_OBJECT

    QVector<QPushButton *> m_buttons;
    int m_checkedButton;
    QLineEdit *m_keyLineEdit;
    QGroupBox *m_updateBox;
    EISEDatabase m_database;

    // Removes all widgets from the update box
    void cleanUpdateBox();

public:
    explicit UpdateInterface(QWidget *parent = 0);

public slots:
    void beginUpdate1(QString searchKey);
    void handleWrongKey();
};

#endif // DELETIONINTERFACE_H
