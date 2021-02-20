#include "rangeloader.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>

#include <prc/equilab/parse.hpp>

#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QUrl>
#include <QtCore/QFutureWatcher>

namespace fs = std::filesystem;

RangeLoader::RangeLoader(TreeViewModel* tree, QObject *parent) : QObject(parent), _tree(tree)
{
    connect(&_watcher, &decltype(_watcher)::finished, this, &RangeLoader::handleFinished);
    connect(&_watcher, &decltype(_watcher)::canceled, this, &RangeLoader::handleCanceled);
}

void RangeLoader::parseEquilab(QString const &url)
{
    auto const fullpath = fs::path{QUrl(url).toLocalFile().toStdString()};
    auto fut = QtConcurrent::run(prc::equilab::parse, fullpath);
    _watcher.setFuture(std::move(fut));
    emit parseStarted();
}

void RangeLoader::handleFinished()
{
    try {
        _root = _watcher.result();
        _tree->setRoot(_root);
        emit parseEnded(true);
    }  catch (std::exception const& e) {
        std::cerr << "parseEquilab failed"<< std::endl;
        emit parseEnded(false);
    }
}


void RangeLoader::handleCanceled()
{
  emit parseEnded(false);
}
