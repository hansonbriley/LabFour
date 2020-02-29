#include "todolistmodel.h"
#include <QDebug>

ToDoListModel::ToDoListModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

int ToDoListModel::rowCount(const QModelIndex &parent) const
{
    return task.size();
}

QVariant ToDoListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return task.at(index.row());
    }

    return QVariant();
}

void ToDoListModel::openFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "can't access file";
    }
    QTextStream in(&file);


    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        for (int i = 0; i < fields.length(); i++) {
            task.push_back(fields[i]);
        }
    }



    file.close();

    emit layoutChanged();
}


