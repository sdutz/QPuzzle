#pragma once

#include <QMainWindow>
#include <QSettings>
#include "puzzlescene.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

//---------------------------------------------------------------
namespace Ui {
    class PuzzleWnd ;
}

//---------------------------------------------------------------
class PuzzleWnd : public QMainWindow
{
    Q_OBJECT

    public :
        explicit PuzzleWnd( QWidget *parent = nullptr) ;
        ~PuzzleWnd() ;
        void addUrls( const QList<QUrl> urls) ;

    private slots :
        void add() ;
        void next() ;
        void ostMute() ;
        void sndMute() ;
        void start() ;
        void reset() ;
        void about() ;
        void reload() ;
        void keyPressEvent( QKeyEvent* pEvent) ;
        void resizeEvent( QResizeEvent* pEvent) ;

    private :
        void play() ;
        void createActions() ;

    private :
        Ui::PuzzleWnd *ui ;
        puzzleScene* m_pScene ;
        QMediaPlaylist* m_ostPlaylist ;
        QMediaPlayer m_ostPlayer ;
        QSettings    m_set ;
        QAction*     m_pAdd ;
        QAction*     m_pOstMute ;
        QAction*     m_pSndMute ;
        QAction*     m_pNext ;
        QAction*     m_pReset ;
        QAction*     m_pAbout ;
        QAction*     m_pStart ;
        QAction*     m_pReload ;
} ;
