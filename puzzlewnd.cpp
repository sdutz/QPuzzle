#include "puzzlewnd.h"
#include "ui_puzzlewnd.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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

    resize( m_set.value( QPWIDTH, minimumWidth()).toInt(), m_set.value( QPHEIGHT, minimumHeight()).toInt()) ;

    createActions() ;
    play() ;
}

//---------------------------------------------------------------
PuzzleWnd::~PuzzleWnd()
{
    m_set.setValue( QPWIDTH,  width()) ;
    m_set.setValue( QPHEIGHT, height()) ;

    delete m_pAdd ;
    delete m_pNext ;
    delete m_pMute ;
    delete m_pStart ;
    delete m_pReload ;
    delete m_playlist ;
    delete ui;
}

//---------------------------------------------------------------
void
PuzzleWnd::createActions()
{
    m_pAdd = new QAction( tr( "Add"), this) ;
    connect( m_pAdd, &QAction::triggered, this, &PuzzleWnd::add) ;
    ui->menuGame->addAction( m_pAdd) ;
    ui->mainToolBar->addAction( m_pAdd) ;

    m_pStart = new QAction( tr( "Start"), this) ;
    connect( m_pStart, &QAction::triggered, this, &PuzzleWnd::start) ;
    ui->menuGame->addAction( m_pStart) ;
    ui->mainToolBar->addAction( m_pStart) ;

    m_pNext = new QAction( tr( "Next"), this) ;
    connect( m_pNext, &QAction::triggered, this, &PuzzleWnd::next) ;
    ui->menuGame->addAction( m_pNext) ;
    ui->mainToolBar->addAction( m_pNext) ;

    m_pReload = new QAction( tr( "Reload"), this) ;
    connect( m_pReload, &QAction::triggered, this, &PuzzleWnd::reload) ;
    ui->menuGame->addAction( m_pReload) ;
    ui->mainToolBar->addAction( m_pReload) ;

    m_pMute = new QAction( tr( "Muted"), this) ;
    m_pMute->setCheckable( true) ;
    connect( m_pMute, &QAction::triggered, this, &PuzzleWnd::mute) ;
    ui->menuGame->addAction( m_pMute) ;
    ui->mainToolBar->addAction( m_pMute) ;
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
PuzzleWnd::mute()
{
    if ( m_player.state() == QMediaPlayer::State::PausedState) {
        m_player.play() ;
    }
    else {
        m_player.pause() ;
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

    start() ;
}

//---------------------------------------------------------------
void
PuzzleWnd::resizeEvent( QResizeEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    ui->pView->fitInView( m_pScene->itemsBoundingRect(), Qt::KeepAspectRatio) ;
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

//---------------------------------------------------------------
void
PuzzleWnd::play()
{
    m_playlist = new QMediaPlaylist( &m_player) ;
    m_playlist->addMedia( QUrl( "qrc:/music/song1.mp3")) ;
    m_player.setPlaylist( m_playlist) ;
    m_player.setVolume( 70) ;
    m_playlist->setPlaybackMode( QMediaPlaylist::Loop) ;
    m_player.play() ;
}
