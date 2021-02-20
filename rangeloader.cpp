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
    /*QFutureWatcher<prc::folder> watcher;
    connect(&watcher, &decltype(watcher)::finished, this, &RangeLoader::)*/
            /*
        std::cout << "before invoke" << std::endl;
        QMetaObject::invokeMethod(_tree, "setRoot", Qt::BlockingQueuedConnection, Q_ARG(prc::folder, f));
        std::cout << "after invoke" << std::endl;
        emit parseEnded(true);})
    .onFailed([this](std::exception const& e){
        std::cerr << "parseEquilab failed with " << e.what() << std::endl;
        emit parseEnded(false);})
    .onFailed([this]{
        std::cerr << "parseEquilab failed"<< std::endl;
        emit parseEnded(false);})
            .onCanceled([this]{
        std::cerr << "parseEquilab canceled"<< std::endl;
        emit parseEnded(false);});
        */
}

void RangeLoader::handleFinished()
{
    try {
        _root = _watcher.result();
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
