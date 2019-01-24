#include "puzzlewnd.h"
#include "ui_puzzlewnd.h"
#include <QKeyEvent>

//---------------------------------------------------------------
#define QPWIDTH  "QPWidth"
#define QPHEIGHT "QPHeight"

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
    m_pScene->doPuzzle( "/Users/sdutz/Pictures/04.jpg", 5) ;
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
