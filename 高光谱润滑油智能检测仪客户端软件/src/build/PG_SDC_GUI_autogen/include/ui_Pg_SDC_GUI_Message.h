/********************************************************************************
** Form generated from reading UI file 'Pg_SDC_GUI_Message.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PG_SDC_GUI_MESSAGE_H
#define UI_PG_SDC_GUI_MESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QMessage
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnSure;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnCancle;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QLabel *labPic;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_4;
    QLabel *labNote;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QLabel *windowPic;
    QLabel *windowNote;
    QSpacerItem *horizontalSpacer;
    QPushButton *Cancle;

    void setupUi(QDialog *QMessage)
    {
        if (QMessage->objectName().isEmpty())
            QMessage->setObjectName(QStringLiteral("QMessage"));
        QMessage->resize(600, 400);
        QMessage->setMinimumSize(QSize(600, 400));
        gridLayout = new QGridLayout(QMessage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalSpacer = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 66, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnSure = new QPushButton(QMessage);
        btnSure->setObjectName(QStringLiteral("btnSure"));
        btnSure->setMinimumSize(QSize(100, 50));

        horizontalLayout_2->addWidget(btnSure);

        horizontalSpacer_3 = new QSpacerItem(80, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btnCancle = new QPushButton(QMessage);
        btnCancle->setObjectName(QStringLiteral("btnCancle"));
        btnCancle->setMinimumSize(QSize(100, 50));

        horizontalLayout_2->addWidget(btnCancle);

        horizontalSpacer_4 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 3);

        verticalSpacer_3 = new QSpacerItem(30, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 5, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(15, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        labPic = new QLabel(QMessage);
        labPic->setObjectName(QStringLiteral("labPic"));

        horizontalLayout_3->addWidget(labPic);

        horizontalSpacer_5 = new QSpacerItem(28, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_4);

        labNote = new QLabel(QMessage);
        labNote->setObjectName(QStringLiteral("labNote"));

        verticalLayout->addWidget(labNote);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_5);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_6 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        windowPic = new QLabel(QMessage);
        windowPic->setObjectName(QStringLiteral("windowPic"));

        horizontalLayout->addWidget(windowPic);

        windowNote = new QLabel(QMessage);
        windowNote->setObjectName(QStringLiteral("windowNote"));

        horizontalLayout->addWidget(windowNote);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Cancle = new QPushButton(QMessage);
        Cancle->setObjectName(QStringLiteral("Cancle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Cancle->sizePolicy().hasHeightForWidth());
        Cancle->setSizePolicy(sizePolicy);
        Cancle->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(Cancle);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);


        retranslateUi(QMessage);

        QMetaObject::connectSlotsByName(QMessage);
    } // setupUi

    void retranslateUi(QDialog *QMessage)
    {
        QMessage->setWindowTitle(QApplication::translate("QMessage", "QFissMessagebox", 0));
        btnSure->setText(QApplication::translate("QMessage", "\347\241\256\350\256\244", 0));
        btnCancle->setText(QApplication::translate("QMessage", "\345\217\226\346\266\210", 0));
        labPic->setText(QApplication::translate("QMessage", "TextLabel", 0));
        labNote->setText(QApplication::translate("QMessage", "TextLabel", 0));
        windowPic->setText(QString());
        windowNote->setText(QString());
        Cancle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QMessage: public Ui_QMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PG_SDC_GUI_MESSAGE_H
