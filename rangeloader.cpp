#include "rangeloader.hpp"

#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QFutureWatcher>
#include <QtCore/QUrl>
#include <filesystem>
#include <iostream>
#include <prc/equilab/parse.hpp>
#include <prc/pio/parse.hpp>
#include <stdexcept>

namespace fs = std::filesystem;

RangeLoader::RangeLoader(TreeViewModel *tree, QObject *parent)
    : QObject(parent), _tree(tree) {
    connect(&_watcher, &decltype(_watcher)::finished, this,
            &RangeLoader::handleFinished);
    connect(&_watcher, &decltype(_watcher)::canceled, this,
            &RangeLoader::handleCanceled);
}

void RangeLoader::parseEquilab(QString const &url) {
    auto const fullpath = fs::path{QUrl(url).toLocalFile().toStdString()};
    auto fut = QtConcurrent::run(prc::equilab::parse, fullpath);
    _watcher.setFuture(std::move(fut));
    emit parseStarted();
}

void RangeLoader::parsePio(QString const &url) {
    auto fut = QtConcurrent::run([url] {
        auto const fullpath = fs::path{QUrl(url).toLocalFile().toStdString()};
        if (!fs::is_directory(fullpath)) {
            std::cerr << fullpath << " is not a directory" << std::endl;
            throw std::runtime_error(fullpath.string() + " is not a directory");
        }
        try {
            return prc::pio::parse_folder(fullpath);
        } catch (std::exception const &e) {
            std::cerr << "prc::pio::parse_folder(\"" << fullpath << "\") failed"
                      << e.what() << std::endl;
            throw;
        }
    });
    _watcher.setFuture(std::move(fut));
    emit parseStarted();
}

void RangeLoader::handleFinished() {
    try {
        _root = _watcher.result();
        _tree->setRoot(_root);
        emit parseEnded(true);
    } catch (std::exception const &e) {
        std::cerr << "parsing failed: " << e.what() << std::endl;
        emit parseEnded(false);
    }
}

void RangeLoader::handleCanceled() { emit parseEnded(false); }
