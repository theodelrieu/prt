#include "rangeloader.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>

#include <prc/equilab/parse.hpp>

#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QUrl>
#include <QMetaObject>

namespace fs = std::filesystem;

RangeLoader::RangeLoader(TreeModel* tree, QObject *parent) : QObject(parent), _tree(tree)
{
}

void RangeLoader::parseEquilab(QString const &url)
{
    auto const fullpath = QUrl(url).toLocalFile();
    emit parseStarted();
    QtConcurrent::run(prc::equilab::parse, fs::path{fullpath.toStdString()}).then([this](prc::folder const& f){
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
}
