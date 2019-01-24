#include "puzzlewnd.h"
#include "ui_puzzlewnd.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QInputDialog>

//---------------------------------------------------------------
#define QPWIDTH  "QPWidth"
#define QPHEIGHT "QPHeight"
#define QPDIR    "QPDir"

//---------------------------------------------------------------
PuzzleWnd::PuzzleWnd( QWidget *parent /* = nullptr*/) : QMainWindow( parent), ui( new Ui::PuzzleWnd)
{
    ui->setupUi( this) ;

    m_pScene = new puzzleScene( ui->pView) ;

    ui->pView->setScene( m_pScene) ;

    resize( m_set.value( QPWIDTH, minimumWidth()).toInt(), m_set.value( QPHEIGHT, minimumHeight()).toInt()) ;

    QAction* pAct = new QAction( "Start", this) ;
    connect( pAct, &QAction::triggered, this, &PuzzleWnd::start) ;
    ui->menuGame->addAction( pAct) ;
}

//---------------------------------------------------------------
PuzzleWnd::~PuzzleWnd()
{
    m_set.setValue( QPWIDTH, width()) ;
    m_set.setValue( QPHEIGHT, height()) ;

    delete ui;
}

//---------------------------------------------------------------
void
PuzzleWnd::start()
{
    QString szDir = m_set.value( QPDIR).toString() ;
    QString szImg = QFileDialog::getOpenFileName( this, tr( "Select image"), szDir, tr("Images (*.png *.xpm *.jpg)")) ;
    if ( szImg.isEmpty()) {
        return ;
    }
    m_set.setValue( QPDIR, szImg.left( szImg.lastIndexOf( "/"))) ;

    bool         bOk ;
    QInputDialog cInput ;

    cInput.setInputMode( QInputDialog::InputMode::IntInput) ;
    int nDiv = cInput.getInt( this, tr("Choose divide"), "", 2, 2, 20, 1, &bOk) ;
    if ( bOk) {
        m_pScene->doPuzzle( szImg, nDiv) ;
    }
}

//---------------------------------------------------------------
void
PuzzleWnd::keyPressEvent( QKeyEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    if ( pEvent->key() == Qt::Key_C) {
        m_pScene->showSol( true) ;
    }
    else if ( pEvent->key() == Qt::Key_H) {
        m_pScene->showSol( false) ;
    }
}
