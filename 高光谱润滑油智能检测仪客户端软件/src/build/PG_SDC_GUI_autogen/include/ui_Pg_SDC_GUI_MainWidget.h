/********************************************************************************
** Form generated from reading UI file 'Pg_SDC_GUI_MainWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PG_SDC_GUI_MAINWIDGET_H
#define UI_PG_SDC_GUI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMainWidget
{
public:

    void setupUi(QWidget *QMainWidget)
    {
        if (QMainWidget->objectName().isEmpty())
            QMainWidget->setObjectName(QStringLiteral("QMainWidget"));
        QMainWidget->resize(1280, 800);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QMainWidget->sizePolicy().hasHeightForWidth());
        QMainWidget->setSizePolicy(sizePolicy);
        QMainWidget->setMaximumSize(QSize(1280, 800));

        retranslateUi(QMainWidget);

        QMetaObject::connectSlotsByName(QMainWidget);
    } // setupUi

    void retranslateUi(QWidget *QMainWidget)
    {
        QMainWidget->setWindowTitle(QApplication::translate("QMainWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class QMainWidget: public Ui_QMainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PG_SDC_GUI_MAINWIDGET_H
