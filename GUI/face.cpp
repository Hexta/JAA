/******************************************************************************
 * Copyright (c) 2011-2014 Artur Molchanov <artur.molchanov@gmail.com>        *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 ******************************************************************************/

#include "face.h"
#include "Compressor/compressor.h"
#include "ui_face.h"
#include "fileList.h"
#include "compressorThread.h"
#include "compressSettingsPanel.h"
#include "decompressSetingsPanel.h"
#include "statInfoW.h"
#include "dataUnitsToQString.h"

#include <QFileDialog>
#include <QToolBar>
#include <QMessageBox>
#include <QProgressDialog>
#include <QDockWidget>

struct Face::Private {
    Private(QMainWindow* parent) :
        compressSettingsPanel(new CompressSettingsPanel()),
        decompressSettingsPanel(new DecompressSettingsPanel()),
        statInfoW(new StatInfoW(parent)),
        compressThread(new CompressorThread()),
        decompressThread(new CompressorThread()),
        listArchiveThread(new CompressorThread()),
        widget(new Ui::face()),
        filelist(new FileList()),
        m_parent(parent) {
        compressSettingsDock = new QDockWidget(tr("Compress Settings"), m_parent);
        decompressSettingsDock = new QDockWidget(tr("Decompress Settings"), m_parent);

        compressingProgressDialog = new QProgressDialog("Compressing files...",
            "Abort", 0, 100, m_parent);
        decompressingProgressDialog = new QProgressDialog("Decompressing files...",
            "Abort", 0, 100, m_parent);
        listArchiveContentsProgressDialog = new QProgressDialog("Reading archive contents...",
            "Abort", 0, 100, m_parent);

        widget->setupUi(m_parent);

        selectFilesToCompressAction = new QAction(tr("Select files to compress"),
            m_parent);
        selectFileToDecompressAction = new QAction(tr("Select file to decompress"),
            m_parent);

        compressAction = new QAction(tr("Compress"), m_parent);
        decompressAction = new QAction(tr("Decompress"), m_parent);
        exitAction = new QAction(tr("E&xit"), m_parent);
        aboutQtAction = new QAction(QIcon(":/images/qt.png"), tr("About &Qt"),
            m_parent);
        aboutAction = new QAction(QIcon(":/images/qt.png"), tr("About"), m_parent);
    }

    CompressSettingsPanel* compressSettingsPanel;
    DecompressSettingsPanel* decompressSettingsPanel;

    StatInfoW* statInfoW;

    CompressorThread* compressThread;
    CompressorThread* decompressThread;
    CompressorThread* listArchiveThread;

    Ui::face* widget;
    Compressor* compressor;

    QToolBar* actionToolBar;

    FileList* filelist;

    QStringList sourceFileNames;
    QStringList encodedfileNames;

    QString destFileName;
    QString destDirName;

    QDir compressBaseDir;
    QDir decompressBaseDir;

    QDockWidget* compressSettingsDock;
    QDockWidget* decompressSettingsDock;

    QAction* selectFilesToCompressAction;
    QAction* selectFileToDecompressAction;
    QAction* compressAction;
    QAction* decompressAction;
    QAction* exitAction;
    QAction* aboutAction;
    QAction* aboutQtAction;

    QMenu* fileMenu;
    QMenu* helpMenu;

    QProgressDialog* compressingProgressDialog;
    QProgressDialog* decompressingProgressDialog;
    QProgressDialog* listArchiveContentsProgressDialog;

    bool brokenFileWarningShown;

    QList<Compressor::CoderTypes> compressSequence;
    unsigned int blockSize;
    bool keepBrokenFiles;

private:
    QMainWindow* m_parent;
};

Face::Face() :
    d(new Private(this)) {
    setCentralWidget(d->filelist);

    d->compressSettingsDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    d->compressSettingsDock->setWidget(d->compressSettingsPanel);
    addDockWidget(Qt::LeftDockWidgetArea, d->compressSettingsDock);

    d->compressSettingsDock->hide();

    d->decompressSettingsDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    d->decompressSettingsDock->setWidget(d->decompressSettingsPanel);
    addDockWidget(Qt::LeftDockWidgetArea, d->decompressSettingsDock);

    d->decompressSettingsDock->hide();

    qRegisterMetaType<CTCompressorStatus::ErrorCode>("CTCompressorStatus::ErrorCode");
    qRegisterMetaType<Compressor::Stat>("Compressor::Stat");

    createActions();
    createMenus();
    createToolBars();
    setupWidgetsConnections();
    initSettings();
}

Face::~Face() {
}

void Face::about() {
    const char* htmlText =
        "<HTML>"
        "<p>JAA - <b>J</b>ust <b>A</b>nother <b>A</b>rchiver</p>"
        "<p>Author: Artur Molchanov <a href=\"mailto:arturmolchanov@gmail.com\">arturmolchanov@gmail.com</a> </p>"
        "</HTML>";
    QMessageBox::about(this, tr("About YAA"), htmlText);
}

void Face::activateCompressMode() {
    d->decompressAction->setEnabled(false);
    d->compressAction->setEnabled(true);
    d->compressSettingsDock->show();
    d->decompressSettingsDock->hide();
}

void Face::activateDecompressMode() {
    d->compressAction->setEnabled(false);
    d->decompressAction->setEnabled(true);
    d->decompressSettingsDock->show();
    d->compressSettingsDock->hide();
}

void Face::createActions() {
    connect(d->selectFilesToCompressAction, SIGNAL(triggered()), this, SLOT(selectFilesToCompress()));
    connect(d->selectFileToDecompressAction, SIGNAL(triggered()), this, SLOT(selectFileToDecompress()));

    d->compressAction->setEnabled(false);
    d->decompressAction->setEnabled(false);

    connect(d->compressAction, SIGNAL(triggered()), this, SLOT(compress()));
    connect(d->decompressAction, SIGNAL(triggered()), this, SLOT(decompress()));
    connect(d->exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(d->aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(d->aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void Face::createToolBars() {
    d->actionToolBar = addToolBar(tr("Action"));
    d->actionToolBar->addAction(d->compressAction);
    d->actionToolBar->addAction(d->decompressAction);
}

void Face::createMenus() {
    d->fileMenu = menuBar()->addMenu(tr("File"));
    d->fileMenu->addAction(d->selectFilesToCompressAction);
    d->fileMenu->addAction(d->selectFileToDecompressAction);
    d->fileMenu->addSeparator();
    d->fileMenu->addAction(d->exitAction);

    d->helpMenu = menuBar()->addMenu(tr("Help"));
    d->helpMenu->addAction(d->aboutAction);
    d->helpMenu->addAction(d->aboutQtAction);
}

void Face::compress() {
    QFileDialog destFileDialog;
    destFileDialog.setWindowTitle("Select Output File");

    if (destFileDialog.exec())
        d->destFileName = destFileDialog.selectedFiles()[0];
    else return;

    d->compressingProgressDialog->setWindowModality(Qt::WindowModal);
    d->compressingProgressDialog->setAutoClose(false);
    d->compressingProgressDialog->reset();

    d->compressThread->initCompress(d->sourceFileNames, d->destFileName,
        d->blockSize, d->compressBaseDir, d->compressSequence);
    d->compressingProgressDialog->show();
    d->compressThread->start();
}

void Face::decompress() {
    QFileDialog destDirDialog;
    destDirDialog.setFileMode(QFileDialog::DirectoryOnly);
    destDirDialog.setWindowTitle("Select Output Folder");

    if (destDirDialog.exec())
        d->destDirName = destDirDialog.selectedFiles()[0];
    else return;

    while (!QDir::setCurrent(d->destDirName)) {
        QMessageBox::critical(this, "Error!", "Cannot change folder to " +
            d->destDirName + "\nPlease select other folder!");

        if (destDirDialog.exec())
            d->destDirName = destDirDialog.selectedFiles()[0];
        else return;
    }

    d->decompressingProgressDialog->setWindowModality(Qt::WindowModal);
    d->decompressingProgressDialog->setAutoClose(false);
    d->decompressingProgressDialog->reset();

    d->decompressThread->initDecompress(d->encodedfileNames[0], d->keepBrokenFiles);
    d->decompressingProgressDialog->show();
    d->decompressThread->start();
}

void Face::displayCompressStatus(int progress, QString fileName, float speed) {
    d->compressingProgressDialog->setValue(progress);
    d->compressingProgressDialog->setLabelText("Current file: " + fileName + "\n" +
        "Speed: " + DataUnitsToQString::convertDataSpeed(speed, 2));
}

void Face::displayDecompressStatus(int progress, QString fileName, float speed) {
    d->decompressingProgressDialog->setValue(progress);
    d->decompressingProgressDialog->setLabelText("Current file: " + fileName + "\n" +
        "Speed: " + DataUnitsToQString::convertDataSpeed(speed, 2));
}

void Face::displayListStatus(int progress, QString fileName, float speed) {
    d->listArchiveContentsProgressDialog->setValue(progress);
    d->listArchiveContentsProgressDialog->setLabelText("Current file: " + fileName + "\n" +
        "Speed: " + DataUnitsToQString::convertDataSpeed(speed, 2));
}

void Face::initSettings() {
    d->compressSequence.clear();
    d->compressSequence << Compressor::RLE <<
        Compressor::BWT <<
        Compressor::MTF <<
        Compressor::RLE <<
        Compressor::HUFFMAN <<
        Compressor::NONE <<
        Compressor::NONE <<
        Compressor::NONE;
    d->blockSize = 900000;
    d->compressSettingsPanel->set(d->blockSize / 1000, d->compressSequence);
    d->keepBrokenFiles = true;
    d->decompressSettingsPanel->set(d->keepBrokenFiles);
}

void Face::listArchiveContents() {
    d->brokenFileWarningShown = false;
    d->listArchiveContentsProgressDialog->setWindowModality(Qt::WindowModal);
    d->listArchiveContentsProgressDialog->setAutoClose(false);

    d->listArchiveThread->initList(d->encodedfileNames[0]);
    d->listArchiveContentsProgressDialog->show();
    d->listArchiveThread->start();
}

void Face::selectFilesToCompress() {
    QFileDialog openFileToCompressDialog;
    openFileToCompressDialog.setFileMode(QFileDialog::ExistingFiles);
    openFileToCompressDialog.setWindowTitle("Select Files To Compress");

    if (openFileToCompressDialog.exec()) {
        d->sourceFileNames = openFileToCompressDialog.selectedFiles();
        d->compressBaseDir = openFileToCompressDialog.directory();
    } else return;

    while (!QDir::setCurrent(d->compressBaseDir.absolutePath() + "/")) {
        QMessageBox::critical(this, "Error!",
            "Folder " + d->compressBaseDir.path() +
            " is not accessible\nPlease select other files!");
        if (openFileToCompressDialog.exec()) {
            d->sourceFileNames = openFileToCompressDialog.selectedFiles();
            d->compressBaseDir = openFileToCompressDialog.directory();
        } else return;
    }

    d->filelist->setFileList(d->sourceFileNames, d->compressBaseDir);
    activateCompressMode();
}

void Face::selectFileToDecompress() {
    QFileDialog openFileToDecompressDialog;
    openFileToDecompressDialog.setWindowTitle(tr("Select File To Decompress"));
    if (openFileToDecompressDialog.exec()) {
        d->encodedfileNames = openFileToDecompressDialog.selectedFiles();
        d->decompressBaseDir = openFileToDecompressDialog.directory();
        listArchiveContents();
        activateDecompressMode();
    }
}

void Face::setCompressSettings(unsigned int blockSize, QList<Compressor::CoderTypes> compressSequence) {
    d->compressSequence = compressSequence;
    d->blockSize = 1000 * blockSize;
}

void Face::setDecompressSettings(bool keepBrokenFiles) {
    d->keepBrokenFiles = keepBrokenFiles;
}

void Face::setupWidgetsConnections() {
    connect(d->compressSettingsPanel, SIGNAL(settingsChanged(unsigned int,
                QList<Compressor::CoderTypes>)), this,
        SLOT(setCompressSettings(unsigned int, QList<Compressor::CoderTypes>)));
    connect(d->compressSettingsPanel, SIGNAL(resetToDefaults()), this, SLOT(initSettings()));

    connect(d->decompressSettingsPanel, SIGNAL(settingsChanged(bool)), this,
        SLOT(setDecompressSettings(bool)));
    connect(d->decompressSettingsPanel, SIGNAL(resetToDefaults()), this, SLOT(initSettings()));

    connect(d->compressThread,
        SIGNAL(progressChanged(int, QString, float)), this, SLOT(displayCompressStatus(int, QString, float)));
    connect(d->compressThread,
        SIGNAL(info(CTCompressorStatus::ErrorCode, QString,
                unsigned int)), this, SLOT(showInfo(CTCompressorStatus::ErrorCode, QString)));
    connect(d->compressingProgressDialog, SIGNAL(canceled()), d->compressThread, SLOT(stop()));
    connect(d->compressThread, SIGNAL(finished()), d->compressingProgressDialog, SLOT(reject()));
    connect(d->compressThread, SIGNAL(info(CTCompressorStatus::ErrorCode,
                QString,
                unsigned int)), d->filelist,
        SLOT(showInfo(CTCompressorStatus::ErrorCode, QString, unsigned int)));
    connect(d->compressThread, SIGNAL(statInfo(Compressor::Stat)), this,
        SLOT(showCompressStatInfo(Compressor::Stat)));

    connect(d->decompressThread,
        SIGNAL(progressChanged(int, QString,
                float)), this, SLOT(displayDecompressStatus(int, QString, float)));
    connect(d->decompressingProgressDialog, SIGNAL(canceled()), d->decompressThread, SLOT(stop()));
    connect(d->decompressThread, SIGNAL(finished()), d->decompressingProgressDialog, SLOT(reject()));
    connect(d->decompressThread, SIGNAL(info(CTCompressorStatus::ErrorCode,
                QString,
                unsigned int)), d->filelist,
        SLOT(showInfo(CTCompressorStatus::ErrorCode, QString, unsigned int)));
    connect(d->decompressThread, SIGNAL(info(CTCompressorStatus::ErrorCode,
                QString,
                unsigned int)), this, SLOT(showInfo(CTCompressorStatus::ErrorCode, QString)));
    connect(d->decompressThread, SIGNAL(statInfo(Compressor::Stat)), this,
        SLOT(showDecompressStatInfo(Compressor::Stat)));

    connect(d->listArchiveThread,
        SIGNAL(progressChanged(int, QString, float)), this, SLOT(displayListStatus(int, QString, float)));
    connect(d->listArchiveContentsProgressDialog, SIGNAL(canceled()), d->listArchiveThread, SLOT(stop()));
    connect(d->listArchiveThread, SIGNAL(finished()), d->listArchiveContentsProgressDialog, SLOT(reject()));
    connect(d->listArchiveThread, SIGNAL(info(CTCompressorStatus::ErrorCode,
                QString,
                unsigned int)), this, SLOT(showInfo(CTCompressorStatus::ErrorCode, QString)));
    connect(d->listArchiveThread, SIGNAL(info(CTCompressorStatus::ErrorCode,
                QString,
                unsigned int)), d->filelist,
        SLOT(showInfo(CTCompressorStatus::ErrorCode, QString, unsigned int)));
    connect(d->listArchiveThread, SIGNAL(started()), d->filelist, SLOT(init()));
}

void Face::showCompressStatInfo(Compressor::Stat stat) {
    if (!d->compressingProgressDialog->wasCanceled()) {
        StatInfoW::StatInfo statInfo;
        statInfo.speed = stat.speed;
        statInfo.blockSize = d->blockSize;
        statInfo.compressSequence = d->compressSequence;
        statInfo.inputSize = stat.decodedSize;
        statInfo.outputSize = stat.encodedSize;

        d->statInfoW->showInfo(statInfo);
        d->statInfoW->setWindowTitle("Compressing Statistics");

        d->statInfoW->show();
    }
}

void Face::showDecompressStatInfo(Compressor::Stat stat) {
    if (!d->decompressingProgressDialog->wasCanceled()) {
        StatInfoW::StatInfo statInfo;
        statInfo.speed = stat.speed;
        statInfo.blockSize = d->blockSize;

        QList<Compressor::CoderTypes> emptySeq;

        statInfo.compressSequence = emptySeq;
        statInfo.inputSize = stat.encodedSize;
        statInfo.outputSize = stat.decodedSize;

        d->statInfoW->showInfo(statInfo);
        d->statInfoW->setWindowTitle("Decompressing Statistics");

        d->statInfoW->show();
    }
}

void Face::showInfo(CTCompressorStatus::ErrorCode error, QString fileName) {
    switch (error) {
        case CTCompressorStatus::INPUT_FILE_OPEN_ERROR:
            if (fileName.isEmpty()) {
                QMessageBox::critical(this, "Error!", "Cannot open input file!"); // archive file
            } else
                QMessageBox::warning(this, "Error!", "Cannot open input file " + fileName + "!"); // raw file
            break;
        case CTCompressorStatus::INPUT_FILE_CORRUPTED: {
            if (!d->brokenFileWarningShown) {
                d->brokenFileWarningShown = true;
                QMessageBox::warning(this, "Error!", "Input File Corrupted!");
            }
        }
        break;
        case CTCompressorStatus::OUTPUT_FILE_WRITE_ERROR:
            QMessageBox::critical(this, "Error!", "Cannot write to output file " + fileName + "!");
            break;
        case CTCompressorStatus::DECOMPRESS_FAIL:
            QMessageBox::critical(this, "Error!", "Decompressing failed!");
            break;
        default:
            break;
    }
}
