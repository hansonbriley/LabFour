#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QAbstractListModel>
#include <QFile>
#include <QTextStream>
#include <vector>

class ToDoListModel: public QAbstractListModel
{
public:
    ToDoListModel(QObject *parent);
    std::vector<QString> task;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void openFile(QString filePath);
};

#endif // TODOLISTMODEL_H
