#include "range.hpp"

Range::Range(prc::range const& range, QObject* parent) : QObject(parent), QStandardItem(), _range(range)
{
    setText(QString::fromStdString(range.name()));
}
