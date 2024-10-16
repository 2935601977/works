/********************************************************************************
** Form generated from reading UI file 'Pg_SDC_GUI_LoginDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PG_SDC_GUI_LOGINDIALOG_H
#define UI_PG_SDC_GUI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QLoginDialog
{
public:

    void setupUi(QDialog *QLoginDialog)
    {
        if (QLoginDialog->objectName().isEmpty())
            QLoginDialog->setObjectName(QStringLiteral("QLoginDialog"));
        QLoginDialog->resize(400, 300);

        retranslateUi(QLoginDialog);

        QMetaObject::connectSlotsByName(QLoginDialog);
    } // setupUi

    void retranslateUi(QDialog *QLoginDialog)
    {
        QLoginDialog->setWindowTitle(QApplication::translate("QLoginDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class QLoginDialog: public Ui_QLoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PG_SDC_GUI_LOGINDIALOG_H
