/*
 * File:   face.cpp
 * Author: art
 *
 * Created on 7 Март 2011 г., 22:17
 */

#include <QFileDialog>
#include <QToolBar>
#include <QMessageBox>
#include <QProgressDialog>
#include <QDockWidget>
#include "face.h"
#    include <Compressor/compressor.h>
#include <ui_face.h>
#include "../FileList/fileList.h"
#include "../CompressorThread/compressorThread.h"
#include "../SettingsPanels/compressSettingsPanel.h"
#include "../SettingsPanels/decompressSetingsPanel.h"
#include "../StatInfoW/statInfoW.h"
#include "../DataUnitsToQString/dataUnitsToQString.h"

Face::Face( ) : sourceFileNames( )
{
        widget = new Ui::face;
	widget->setupUi( this );

	filelist = new FileList;
	setCentralWidget( filelist );

	compressSettingsPanel = new CompressSettingsPanel;
	compressSettingsDock = new QDockWidget( tr( "Compress Settings" ), this );
	compressSettingsDock->setAllowedAreas( Qt::LeftDockWidgetArea );
	compressSettingsDock->setWidget( compressSettingsPanel );
	addDockWidget( Qt::LeftDockWidgetArea, compressSettingsDock );

	compressSettingsDock->hide( );

	decompressSettingsPanel = new DecompressSettingsPanel;
	decompressSettingsDock = new QDockWidget( tr( "Decompress Settings" ), this );
	decompressSettingsDock->setAllowedAreas( Qt::LeftDockWidgetArea );
	decompressSettingsDock->setWidget( decompressSettingsPanel );
	addDockWidget( Qt::LeftDockWidgetArea, decompressSettingsDock );

	decompressSettingsDock->hide( );

	statInfoW = new StatInfoW( this );

	compressThread = new CompressorThread;
	decompressThread = new CompressorThread;
	listArchiveThread = new CompressorThread;

	compressingProgressDialog = new QProgressDialog( "Compressing files...", "Abort", 0, 100, this );
	decompressingProgressDialog = new QProgressDialog( "Decompressing files...", "Abort", 0, 100, this );
	listArchiveContentsProgressDialog = new QProgressDialog( "Reading archive contents...", "Abort", 0, 100, this );

	qRegisterMetaType< CTCompressorStatus::ErrorCode > ( "CTCompressorStatus::ErrorCode" );
	qRegisterMetaType< Compressor::Stat > ( "Compressor::Stat" );

	createActions( );
	createMenus( );
	createToolBars( );
	setupWidgetsConnections( );
	initSettings( );
}

Face::~Face( )
{
	delete compressingProgressDialog;
	delete decompressingProgressDialog;
	delete statInfoW;
        delete widget;
}

void
Face::about( )
{
	const char *htmlText =
		"<HTML>"
		"<p>JAA - <b>J</b>ust <b>A</b>nother <b>A</b>rchiver</p>"
		"<p>Author: Artur Molchanov <a href=""mailto:arturmolchanov@gmail.com"">arturmolchanov@gmail.com</a> </p>"
		"</HTML>";
	QMessageBox::about( this, tr( "About YAA" ), htmlText );
}

void
Face::activateCompressMode( )
{
	decompressAction->setEnabled( false );
	compressAction->setEnabled( true );
	compressSettingsDock->show( );
	decompressSettingsDock->hide( );
}

void
Face::activateDecompressMode( )
{
	compressAction->setEnabled( false );
	decompressAction->setEnabled( true );
	decompressSettingsDock->show( );
	compressSettingsDock->hide( );
}

void
Face::createActions( )
{
	selectFilesToCompressAction = new QAction( tr( "Select files to compress" ), this );
	connect( selectFilesToCompressAction, SIGNAL( triggered( ) ), this, SLOT( selectFilesToCompress( ) ) );

	selectFileToDecompressAction = new QAction( tr( "Select file to decompress" ), this );
	connect( selectFileToDecompressAction, SIGNAL( triggered( ) ), this, SLOT( selectFileToDecompress( ) ) );

	compressAction = new QAction( tr( "Compress" ), this );
	compressAction->setEnabled( false );
	connect( compressAction, SIGNAL( triggered( ) ), this, SLOT( compress( ) ) );

	decompressAction = new QAction( tr( "Decompress" ), this );
	decompressAction->setEnabled( false );
	connect( decompressAction, SIGNAL( triggered( ) ), this, SLOT( decompress( ) ) );

	exitAction = new QAction( tr( "E&xit" ), this );
	connect( exitAction, SIGNAL( triggered( ) ), qApp, SLOT( quit( ) ) );

	aboutQtAction = new QAction( QIcon( ":/images/qt.png" ), tr( "About &Qt" ), this );
	connect( aboutQtAction, SIGNAL( triggered( ) ), qApp, SLOT( aboutQt( ) ) );

	aboutAction = new QAction( QIcon( ":/images/qt.png" ), tr( "About" ), this );
	connect( aboutAction, SIGNAL( triggered( ) ), this, SLOT( about( ) ) );
}

void
Face::createToolBars( )
{
	actionToolBar = addToolBar( tr( "Action" ) );
	actionToolBar->addAction( compressAction );
	actionToolBar->addAction( decompressAction );
}

void
Face::createMenus( )
{
	fileMenu = menuBar( )->addMenu( tr( "File" ) );
	fileMenu->addAction( selectFilesToCompressAction );
	fileMenu->addAction( selectFileToDecompressAction );
	fileMenu->addSeparator( );
	fileMenu->addAction( exitAction );

	helpMenu = menuBar( )->addMenu( tr( "Help" ) );
	helpMenu->addAction( aboutAction );
	helpMenu->addAction( aboutQtAction );
}

void
Face::compress( )
{
	QFileDialog destFileDialog;
	destFileDialog.setWindowTitle( "Select Output File" );

	if ( destFileDialog.exec( ) )
		destFileName = destFileDialog.selectedFiles( )[0];
	else return;

	compressingProgressDialog->setWindowModality( Qt::WindowModal );
	compressingProgressDialog->setAutoClose( false );
	compressingProgressDialog->reset( );

	compressThread->initCompress( sourceFileNames, destFileName, blockSize, compressBaseDir, compressSequence );
	compressingProgressDialog->show( );
	compressThread->start( );
}

void
Face::decompress( )
{
	QFileDialog destDirDialog;
	destDirDialog.setFileMode( QFileDialog::DirectoryOnly );
	destDirDialog.setWindowTitle( "Select Output Folder" );

	if ( destDirDialog.exec( ) )
		destDirName = destDirDialog.selectedFiles( )[0];
	else return;

	while ( !QDir::setCurrent( destDirName ) )
	{
		QMessageBox::critical( this, "Error!", "Cannot change folder to " + destDirName + "\nPlease select other folder!" );
		if ( destDirDialog.exec( ) )
			destDirName = destDirDialog.selectedFiles( )[0];
		else return;
	}
	decompressingProgressDialog->setWindowModality( Qt::WindowModal );
	decompressingProgressDialog->setAutoClose( false );
	decompressingProgressDialog->reset( );

	decompressThread->initDecompress( encodedfileNames[0], keepBrokenFiles );
	decompressingProgressDialog->show( );
	decompressThread->start( );
}

void
Face::displayCompressStatus( int progress, QString fileName, float speed )
{
	compressingProgressDialog->setValue( progress );
	compressingProgressDialog->setLabelText( "Current file: " + fileName + "\n" + "Speed: " + DataUnitsToQString::convertDataSpeed( speed, 2 ) );
}

void
Face::displayDecompressStatus( int progress, QString fileName, float speed )
{
	decompressingProgressDialog->setValue( progress );
	decompressingProgressDialog->setLabelText( "Current file: " + fileName + "\n" + "Speed: " + DataUnitsToQString::convertDataSpeed( speed, 2 ) );
}

void
Face::displayListStatus( int progress, QString fileName, float speed )
{
	listArchiveContentsProgressDialog->setValue( progress );
	listArchiveContentsProgressDialog->setLabelText( "Current file: " + fileName + "\n" + "Speed: " + DataUnitsToQString::convertDataSpeed( speed, 2 ) );
}

void
Face::initSettings( )
{
	compressSequence.clear( );
	compressSequence << Compressor::RLE <<
		Compressor::BWT <<
		Compressor::MTF <<
		Compressor::RLE <<
		Compressor::HUFFMAN <<
		Compressor::NONE <<
		Compressor::NONE <<
		Compressor::NONE;
	blockSize = 900000;
	compressSettingsPanel->set( blockSize / 1000, compressSequence );
	keepBrokenFiles = true;
	decompressSettingsPanel->set( keepBrokenFiles );
}

void
Face::listArchiveContents( )
{
	brokenFileWarningShown = false;
	listArchiveContentsProgressDialog->setWindowModality( Qt::WindowModal );
	listArchiveContentsProgressDialog->setAutoClose( false );

	listArchiveThread->initList( encodedfileNames[0] );
	listArchiveContentsProgressDialog->show( );
	listArchiveThread->start( );
}

void
Face::selectFilesToCompress( )
{
	QFileDialog openFileToCompressDialog;
	openFileToCompressDialog.setFileMode( QFileDialog::ExistingFiles );
	openFileToCompressDialog.setWindowTitle( "Select Files To Compress" );

	if ( openFileToCompressDialog.exec( ) )
	{
		sourceFileNames = openFileToCompressDialog.selectedFiles( );
		compressBaseDir = openFileToCompressDialog.directory( );
	}
	else return;

	while ( !QDir::setCurrent( compressBaseDir.absolutePath( ) + "/" ) )
	{
		QMessageBox::critical( this, "Error!", "Folder " + compressBaseDir.path( ) + " is not accessible" + "\nPlease select other files!" );
		if ( openFileToCompressDialog.exec( ) )
		{
			sourceFileNames = openFileToCompressDialog.selectedFiles( );
			compressBaseDir = openFileToCompressDialog.directory( );
		}
		else return;
	}

	filelist->setFileList( sourceFileNames, compressBaseDir );
	activateCompressMode( );
}

void
Face::selectFileToDecompress( )
{
	QFileDialog openFileToDecompressDialog;
	openFileToDecompressDialog.setWindowTitle( tr( "Select File To Decompress" ) );
	if ( openFileToDecompressDialog.exec( ) )
	{
		encodedfileNames = openFileToDecompressDialog.selectedFiles( );
		decompressBaseDir = openFileToDecompressDialog.directory( );
		listArchiveContents( );
		activateDecompressMode( );
	}
}

void
Face::setCompressSettings( unsigned int blockSize, QList< Compressor::CoderTypes> compressSequence )
{
	this->compressSequence = compressSequence;
	this->blockSize = 1000 * blockSize;
}

void
Face::setDecompressSettings( bool keepBrokenFiles )
{
	this->keepBrokenFiles = keepBrokenFiles;
}

void
Face::setupWidgetsConnections( )
{
	connect( compressSettingsPanel, SIGNAL( settingsChanged( unsigned int, QList< Compressor::CoderTypes> ) ), this, SLOT( setCompressSettings( unsigned int, QList< Compressor::CoderTypes> ) ) );
	connect( compressSettingsPanel, SIGNAL( resetToDefaults( ) ), this, SLOT( initSettings( ) ) );

	connect( decompressSettingsPanel, SIGNAL( settingsChanged( bool ) ), this, SLOT( setDecompressSettings( bool ) ) );
	connect( decompressSettingsPanel, SIGNAL( resetToDefaults( ) ), this, SLOT( initSettings( ) ) );

	connect( compressThread, SIGNAL( progressChanged( int, QString, float ) ), this, SLOT( displayCompressStatus( int, QString, float ) ) );
	connect( compressThread, SIGNAL( info( CTCompressorStatus::ErrorCode, QString, unsigned int ) ), this, SLOT( showInfo( CTCompressorStatus::ErrorCode, QString ) ) );
	connect( compressingProgressDialog, SIGNAL( canceled( ) ), compressThread, SLOT( stop( ) ) );
	connect( compressThread, SIGNAL( finished( ) ), compressingProgressDialog, SLOT( reject( ) ) );
	connect( compressThread, SIGNAL( info( CTCompressorStatus::ErrorCode, QString, unsigned int ) ), filelist, SLOT( showInfo( CTCompressorStatus::ErrorCode, QString, unsigned int ) ) );
	connect( compressThread, SIGNAL( statInfo( Compressor::Stat ) ), this, SLOT( showCompressStatInfo( Compressor::Stat ) ) );

	connect( decompressThread, SIGNAL( progressChanged( int, QString, float ) ), this, SLOT( displayDecompressStatus( int, QString, float ) ) );
	connect( decompressingProgressDialog, SIGNAL( canceled( ) ), decompressThread, SLOT( stop( ) ) );
	connect( decompressThread, SIGNAL( finished( ) ), decompressingProgressDialog, SLOT( reject( ) ) );
	connect( decompressThread, SIGNAL( info( CTCompressorStatus::ErrorCode, QString, unsigned int ) ), filelist, SLOT( showInfo( CTCompressorStatus::ErrorCode, QString, unsigned int ) ) );
	connect( decompressThread, SIGNAL( info( CTCompressorStatus::ErrorCode, QString, unsigned int ) ), this, SLOT( showInfo( CTCompressorStatus::ErrorCode, QString ) ) );
	connect( decompressThread, SIGNAL( statInfo( Compressor::Stat ) ), this, SLOT( showDecompressStatInfo( Compressor::Stat ) ) );

	connect( listArchiveThread, SIGNAL( progressChanged( int, QString, float ) ), this, SLOT( displayListStatus( int, QString, float ) ) );
	connect( listArchiveContentsProgressDialog, SIGNAL( canceled( ) ), listArchiveThread, SLOT( stop( ) ) );
	connect( listArchiveThread, SIGNAL( finished( ) ), listArchiveContentsProgressDialog, SLOT( reject( ) ) );
	connect( listArchiveThread, SIGNAL( info( CTCompressorStatus::ErrorCode, QString, unsigned int ) ), this, SLOT( showInfo( CTCompressorStatus::ErrorCode, QString ) ) );
	connect( listArchiveThread, SIGNAL( info( CTCompressorStatus::ErrorCode, QString, unsigned int ) ), filelist, SLOT( showInfo( CTCompressorStatus::ErrorCode, QString, unsigned int ) ) );
	connect( listArchiveThread, SIGNAL( started( ) ), filelist, SLOT( init( ) ) );
}

void
Face::showCompressStatInfo( Compressor::Stat stat )
{
	if ( !compressingProgressDialog->wasCanceled( ) )
	{
		StatInfoW::StatInfo statInfo;
		statInfo.speed = stat.speed;
		statInfo.blockSize = blockSize;
		statInfo.compressSequence = compressSequence;
		statInfo.inputSize = stat.decodedSize;
		statInfo.outputSize = stat.encodedSize;

		statInfoW->showInfo( statInfo );
		statInfoW->setWindowTitle( "Compressing Statistics" );

		statInfoW->show( );
	}
}

void
Face::showDecompressStatInfo( Compressor::Stat stat )
{
	if ( !decompressingProgressDialog->wasCanceled( ) )
	{
		StatInfoW::StatInfo statInfo;
		statInfo.speed = stat.speed;
		statInfo.blockSize = blockSize;

		QList< Compressor::CoderTypes> emptySeq;

		statInfo.compressSequence = emptySeq;
		statInfo.inputSize = stat.encodedSize;
		statInfo.outputSize = stat.decodedSize;

		statInfoW->showInfo( statInfo );
		statInfoW->setWindowTitle( "Decompressing Statistics" );

		statInfoW->show( );
	}
}

void
Face::showInfo( CTCompressorStatus::ErrorCode error, QString fileName )
{
	switch ( error )
	{
		case CTCompressorStatus::INPUT_FILE_OPEN_ERROR:
			if ( fileName.isEmpty( ) )
			{
				QMessageBox::critical( this, "Error!", "Cannot open input file!" ); //archive file
			}
			else
				QMessageBox::warning( this, "Error!", "Cannot open input file " + fileName + "!" ); //raw file
			break;
		case CTCompressorStatus::INPUT_FILE_CORRUPTED:
		{
			if ( !brokenFileWarningShown )
			{
				brokenFileWarningShown = true;
				QMessageBox::warning( this, "Error!", "Input File Corrupted!" );
			}
		}
			break;
		case CTCompressorStatus::OUTPUT_FILE_WRITE_ERROR:QMessageBox::critical( this, "Error!", "Cannot write to output file " + fileName + "!" );
			break;
		case CTCompressorStatus::DECOMPRESS_FAIL:QMessageBox::critical( this, "Error!", "Decompressing failed!" );
			break;
		default:break;
	}
}

