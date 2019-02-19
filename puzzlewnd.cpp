#include "puzzlewnd.h"
#include "ui_puzzlewnd.h"
#include "aux.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QInputDialog>

//---------------------------------------------------------------
#define QPDIR    "QPDir"
#define QPWIDTH  "QPWidth"
#define QPHEIGHT "QPHeight"

//---------------------------------------------------------------
PuzzleWnd::PuzzleWnd( QWidget *parent /* = nullptr*/) : QMainWindow( parent), ui( new Ui::PuzzleWnd)
{
    ui->setupUi( this) ;

    m_pScene = new puzzleScene( ui->pView) ;

    ui->pView->setScene( m_pScene) ;
    ui->pView->setParent( this) ;

    resize( m_set.value( QPWIDTH, minimumWidth()).toInt(), m_set.value( QPHEIGHT, minimumHeight()).toInt()) ;

    setAcceptDrops( true) ;
    createActions() ;
    play() ;
}

//---------------------------------------------------------------
PuzzleWnd::~PuzzleWnd()
{
    m_set.setValue( QPWIDTH,  width()) ;
    m_set.setValue( QPHEIGHT, height()) ;

    SAFE_DEL( m_pAdd) ;
    SAFE_DEL( m_pNext) ;
    SAFE_DEL( m_pMute) ;
    SAFE_DEL( m_pReset) ;
    SAFE_DEL( m_pStart) ;
    SAFE_DEL( m_pAbout) ;
    SAFE_DEL( m_pReload) ;
    SAFE_DEL( m_ostPlaylist) ;
    SAFE_DEL( ui) ;
}

//---------------------------------------------------------------
void
PuzzleWnd::createActions()
{
    m_pReset = new QAction( tr( "New"), this) ;
    connect( m_pReset, &QAction::triggered, this, &PuzzleWnd::reset) ;
    ui->menuGame->addAction( m_pReset) ;
    ui->mainToolBar->addAction( m_pReset) ;

    m_pAdd = new QAction( tr( "Add"), this) ;
    connect( m_pAdd, &QAction::triggered, this, &PuzzleWnd::add) ;
    ui->menuGame->addAction( m_pAdd) ;
    ui->mainToolBar->addAction( m_pAdd) ;

    m_pStart = new QAction( tr( "Start"), this) ;
    connect( m_pStart, &QAction::triggered, this, &PuzzleWnd::start) ;
    ui->menuGame->addAction( m_pStart) ;
    ui->mainToolBar->addAction( m_pStart) ;
    m_pStart->setEnabled( false) ;

    m_pNext = new QAction( tr( "Next"), this) ;
    connect( m_pNext, &QAction::triggered, this, &PuzzleWnd::next) ;
    ui->menuGame->addAction( m_pNext) ;
    ui->mainToolBar->addAction( m_pNext) ;
    m_pNext->setEnabled( false) ;

    m_pReload = new QAction( tr( "Reload"), this) ;
    connect( m_pReload, &QAction::triggered, this, &PuzzleWnd::reload) ;
    ui->menuGame->addAction( m_pReload) ;
    ui->mainToolBar->addAction( m_pReload) ;
    m_pReload->setEnabled( false) ;

    m_pMute = new QAction( tr( "Muted"), this) ;
    m_pMute->setCheckable( true) ;
    connect( m_pMute, &QAction::triggered, this, &PuzzleWnd::mute) ;
    ui->menuGame->addAction( m_pMute) ;
    ui->mainToolBar->addAction( m_pMute) ;

    m_pAbout = new QAction( tr( "About"), this) ;
    connect( m_pAbout, &QAction::triggered, this, &PuzzleWnd::about) ;
    ui->menuGame->addAction( m_pAbout) ;
    ui->mainToolBar->addAction( m_pAbout) ;
}

//---------------------------------------------------------------
void
PuzzleWnd::start()
{
    bool         bOk ;
    QInputDialog cInput ;

    cInput.setInputMode( QInputDialog::InputMode::IntInput) ;
    int nDiv = cInput.getInt( this, tr("Choose side pieces"), "", 2, 2, 20, 1, &bOk) ;
    if ( bOk) {
        m_pScene->start( nDiv) ;
        m_pNext->setEnabled( true) ;
        m_pReload->setEnabled( true) ;
    }
}

//---------------------------------------------------------------
void
PuzzleWnd::reset()
{
    m_pScene->resetAll() ;
    m_pStart->setEnabled( false) ;
    m_pNext->setEnabled( false) ;
    m_pReload->setEnabled( false) ;
}

//---------------------------------------------------------------
void
PuzzleWnd::about()
{
    m_pScene->about() ;
}

//---------------------------------------------------------------
void
PuzzleWnd::mute()
{
    if ( m_ostPlayer.state() == QMediaPlayer::State::PausedState) {
        m_ostPlayer.play() ;
    }
    else {
        m_ostPlayer.pause() ;
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
PuzzleWnd::reload()
{
    m_pScene->doPuzzle() ;
}

//---------------------------------------------------------------
void
PuzzleWnd::addUrls( const QList<QUrl> urls)
{
    QUrl url ;

    foreach( url, urls) {
        if ( url.isLocalFile()) {
            m_pScene->addImage( url.toLocalFile()) ;
        }
    }

    m_set.setValue( QPDIR, url.toLocalFile().left( url.toLocalFile().lastIndexOf( "/"))) ;
    m_pStart->setEnabled( true) ;
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

    m_pStart->setEnabled( true) ;
}

//---------------------------------------------------------------
void
PuzzleWnd::resizeEvent( QResizeEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    m_pScene->fit() ;
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
    else if ( pEvent->key() == Qt::Key_M) {
        mute() ;
    }
    else if ( pEvent->key() == Qt::Key_A) {
        add() ;
    }
    else if ( pEvent->key() == Qt::Key_S) {
        start() ;
    }
    else if ( pEvent->key() == Qt::Key_N) {
        next() ;
    }
    else if ( pEvent->key() == Qt::Key_R) {
        reload() ;
    }
}

//---------------------------------------------------------------
void
PuzzleWnd::play()
{
    m_ostPlaylist = new QMediaPlaylist( &m_ostPlayer) ;
    m_ostPlaylist->addMedia( QUrl( "qrc:/music/song1.mp3")) ;
    m_ostPlayer.setPlaylist( m_ostPlaylist) ;
    m_ostPlayer.setVolume( 70) ;
    m_ostPlaylist->setPlaybackMode( QMediaPlaylist::Loop) ;
    m_ostPlayer.play() ;
}
