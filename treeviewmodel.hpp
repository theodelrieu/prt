#ifndef TREEVIEWMODEL_HPP
#define TREEVIEWMODEL_HPP

#include <QStandardItemModel>

#include <prc/folder.hpp>

class TreeViewModel : public QStandardItemModel
{
    Q_OBJECT
    Q_PROPERTY(QPersistentModelIndex rootIndex READ rootIndex NOTIFY rootIndexChanged)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        IndexRole,
        LastRole,
    };
    TreeViewModel(QObject* parent = nullptr);

    QPersistentModelIndex rootIndex() const;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(QModelIndex const&, int role) const override;

signals:
    // shut up qml warning
    void rootIndexChanged();

public slots:
    void setRoot(prc::folder const&);
};

#endif // TREEVIEWMODEL_HPP
