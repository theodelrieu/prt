#include "rangeloader.hpp"

#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QFutureWatcher>
#include <QtCore/QUrl>
#include <QStandardPaths>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <prc/equilab/parse.hpp>
#include <prc/equilab/serialize.hpp>
#include <prc/pio/parse.hpp>
#include <stdexcept>

namespace fs = std::filesystem;

RangeLoader::RangeLoader(TreeViewModel *tree, QObject *parent)
    : QObject(parent), _tree(tree), _hasLocalRanges(false) {
    auto const rangesPath = QStandardPaths::locate(QStandardPaths::AppLocalDataLocation, "ranges.hr");
    if (!rangesPath.isEmpty())
    {
        try {
            _root = prc::equilab::parse(fs::path{rangesPath.toUtf8().toStdString()});
            _tree->setRoot(_root);
            _hasLocalRanges = true;
        } catch (std::exception const& e) {
            std::cerr << "while loading stored ranges: " << e.what() << std::endl;
        }
    }
}

bool RangeLoader::hasLocalRanges() const
{
    return _hasLocalRanges;
}

void RangeLoader::writeLocalRanges()
{
    auto const writablePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation).toUtf8().toStdString();
    auto const fullpath = fs::path{writablePath} / "ranges.hr";
    auto const serialized = prc::equilab::serialize(_root);
    std::ofstream ofs{fullpath.string(), std::ios::trunc | std::ios::binary};
    ofs.write(reinterpret_cast<char const*>(serialized.data()), 2 * serialized.size());
    _hasLocalRanges = true;
    emit hasLocalRangesChanged();
}

void RangeLoader::parseEquilab(QString const &url) {
    fs::path const fullpath{QUrl(url).toLocalFile().toUtf8().toStdString()};
    QtConcurrent::run([this, fullpath]{
           emit parseStarted();
           return prc::equilab::parse(fullpath);
        }).then([this](prc::folder const& f){
        _root = f;
        _tree->setRoot(_root);
        writeLocalRanges();
        emit parseEnded(true);
    }).onFailed([this] (std::exception const& e) { std::cerr << e.what() << std::endl; emit parseEnded(false);});
}

void RangeLoader::parsePio(QString const &url) {
    fs::path const fullpath{QUrl(url).toLocalFile().toUtf8().toStdString()};
    if (!fs::is_directory(fullpath)) {
        std::cerr << fullpath << " is not a directory" << std::endl;
        throw std::runtime_error(fullpath.string() + " is not a directory");
    }
    QtConcurrent::run([this, fullpath]{
           emit parseStarted();
           return prc::pio::parse_folder(fullpath);
        }).then([this](prc::folder const& f){
        _root = f;
        _tree->setRoot(_root);
        writeLocalRanges();
        emit parseEnded(true);
    }).onFailed([this] (std::exception const& e) {
        std::cerr << "OOPS " << e.what() << std::endl;
        emit parseEnded(false);
    });
}
