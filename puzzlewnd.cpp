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

    createActions() ;
}

//---------------------------------------------------------------
PuzzleWnd::~PuzzleWnd()
{
    m_set.setValue( QPWIDTH, width()) ;
    m_set.setValue( QPHEIGHT, height()) ;

    delete m_pAdd ;
    delete m_pNext ;
    delete m_pStart ;

    delete ui;
}

//---------------------------------------------------------------
void
PuzzleWnd::createActions()
{
    m_pAdd = new QAction( tr( "Add"), this) ;
    connect( m_pAdd, &QAction::triggered, this, &PuzzleWnd::add) ;
    ui->menuGame->addAction( m_pAdd) ;

    m_pStart = new QAction( tr( "Start"), this) ;
    connect( m_pStart, &QAction::triggered, this, &PuzzleWnd::start) ;
    ui->menuGame->addAction( m_pStart) ;

    m_pNext = new QAction( tr( "Next"), this) ;
    connect( m_pNext, &QAction::triggered, this, &PuzzleWnd::next) ;
    ui->menuGame->addAction( m_pNext) ;
}

//---------------------------------------------------------------
void
PuzzleWnd::start()
{
    bool         bOk ;
    QInputDialog cInput ;

    cInput.setInputMode( QInputDialog::InputMode::IntInput) ;
    int nDiv = cInput.getInt( this, tr("Choose divide"), "", 2, 2, 20, 1, &bOk) ;
    if ( bOk) {
        m_pScene->start( nDiv) ;
    }
}

//---------------------------------------------------------------
void
PuzzleWnd::next()
{
    m_pScene->next() ;
}

//---------------------------------------------------------------
void
PuzzleWnd::add()
{
    QString szDir = m_set.value( QPDIR).toString() ;
    QStringList slImgs = QFileDialog::getOpenFileNames( this, tr( "Select images"),
                                                        szDir, tr("Images (*.png *.xpm *.jpg)")) ;
    if ( slImgs.isEmpty()) {
        return ;
    }

    m_set.setValue( QPDIR, slImgs.first().left( slImgs.first().lastIndexOf( "/"))) ;

    foreach ( QString szImg, slImgs) {
        m_pScene->addImage( szImg) ;
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
