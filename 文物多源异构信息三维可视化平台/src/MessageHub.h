/*
 * Copyright (c) 2014-2016 Meltytech, LLC
 * Author: Dan Dennedy <dan@dennedy.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MESSAGEHUB_H
#define MESSAGEHUB_H

#include <QObject>

class MessageHub : public QObject
{
    Q_OBJECT
// 一旦你使用 Q_ENUMS 宏注册了你的枚举类型，
// 在 QML 中就可以用 ${CLASS_NAME}.${ENUM_VALUE} 的形式来访问，比如 OpenFile.LinearIncrease
    Q_ENUMS(GenerateAlgorithm)

public:
    explicit MessageHub(QObject *parent = 0);
    ~MessageHub();

    enum GenerateAlgorithm{
           RandomRGB,
           RandomRed,
           RandomGreen,
           RandomBlue,
           LinearIncrease
       };


//    定义了 open() 信号槽， currentTime() 信号，都可以在 QML 中使用。
signals:
    void currentTime(const QString &strTime);

public slots:
    void sendCmd(const QString& cmdCode);

private:
    QString filePath;
};

#endif // MESSAGEHUB_H
