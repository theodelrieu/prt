#ifndef RANGEDISPLAYER_HPP
#define RANGEDISPLAYER_HPP

#include <QObject>
#include <QList>
#include <QStandardItemModel>

#include "handinfo.hpp"
#include "treeviewmodel.hpp"

class RangeDisplayer : public QStandardItemModel
{
    Q_OBJECT
public:
    enum Roles {
      NameRole = Qt::UserRole + 1,
      ParentRangeRole,
      SubrangesRole,
      LastRole,
    };

    explicit RangeDisplayer(TreeViewModel* treeView, QObject *parent = nullptr);

    QVariant data(QModelIndex const&, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void setRange(QModelIndex const&);

private:
    TreeViewModel* _treeView;
    QModelIndex _lastIndex;
    QList<HandInfo> _handInfo;
};

#endif // RANGEDISPLAYER_HPP
