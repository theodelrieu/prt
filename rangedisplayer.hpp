#ifndef RANGEDISPLAYER_HPP
#define RANGEDISPLAYER_HPP

#include <QObject>
#include <QList>
#include <QStandardItemModel>

#include "handinfo.hpp"
#include "treeviewmodel.hpp"
#include "quizsettingsmodel.hpp"

class Range;

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

    // TODO move in quizer
    explicit RangeDisplayer(TreeViewModel* treeView, QuizSettingsModel* settings, QObject *parent = nullptr);
    ~RangeDisplayer();

    QVariant data(QModelIndex const&, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QList<HandInfo> const& handInfo() const;
    Range const* currentRange() const;
    QuizSettingsModel const* quizSettings() const;

signals:
    void rangeLoaded(QString const&);

public slots:
    void setRange(QModelIndex const&);

private:
    TreeViewModel* _treeView;
    QModelIndex _lastTreeIndex;
    QList<HandInfo> _handInfo;
    Range* _currentRange;
    QuizSettingsModel* _quizSettings;
};

#endif // RANGEDISPLAYER_HPP
