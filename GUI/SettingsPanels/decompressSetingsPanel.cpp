/* 
 * File:   DecompressSetingsPanel.cpp
 * Author: art
 * 
 * Created on 21 Март 2011 г., 13:10
 */

#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include "decompressSetingsPanel.h"

DecompressSettingsPanel::DecompressSettingsPanel( )
{
	keepBrokenFilesCheckbox = new QCheckBox( "Keep broken files", this );
	QGridLayout *grid = new QGridLayout;

	QPushButton *resetToDefaultsButton = new QPushButton( tr( "Reset To Defaults" ) );
	connect( resetToDefaultsButton, SIGNAL( clicked( ) ), this, SIGNAL( resetToDefaults( ) ) );

	grid->addWidget( keepBrokenFilesCheckbox, 0, 0, Qt::AlignTop );
	grid->addWidget( resetToDefaultsButton, 1, 0, Qt::AlignBottom );

	setLayout( grid );
	setupWidgetsConnections( );
}

DecompressSettingsPanel::~DecompressSettingsPanel( ) { }

void
DecompressSettingsPanel::get( )
{
	bool keepBroken = keepBrokenFilesCheckbox->isChecked( );
	emit settingsChanged( keepBroken );
}

void
DecompressSettingsPanel::set( bool keepBroken )
{
	keepBrokenFilesCheckbox->setChecked( keepBroken );
}

void
DecompressSettingsPanel::setupWidgetsConnections( )
{
	connect( keepBrokenFilesCheckbox, SIGNAL( stateChanged( int ) ), this, SLOT( get( ) ) );
}

