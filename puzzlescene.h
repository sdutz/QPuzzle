#pragma once

#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsScene>

//---------------------------------------------------------------
struct puzzleLevel {
    int     nDiv ;
    QString szImg ;

    puzzleLevel() {
        nDiv = 2 ;
    }
} ;


//---------------------------------------------------------------
struct puzzleItem {
    QPoint               ptPos ;
    QGraphicsPixmapItem* pItem ;
} ;

//---------------------------------------------------------------
class puzzleScene : public QGraphicsScene
{
    Q_OBJECT

    public :
        puzzleScene( QGraphicsView *parent = nullptr) ;
        ~puzzleScene() ;

        bool start( int nDiv) ;
        bool next() ;
        void fit() ;
        void resetAll() ;
        bool about() ;
        bool doPuzzle() ;
        void toggleMute() ;
        bool showSol( bool bShow) ;
        void addImage( const QString& szImg) ;

    public slots :
        void swapPos() ;
        void showSol() ;

    protected :
        void mousePressEvent( QGraphicsSceneMouseEvent* pEvent) ;

    private :
        bool isSolved() ;
        void reset() ;
        void initSnd() ;
        void play( bool bUp) ;

    private :
        bool                 m_bMute ;
        int                  m_nStep ;
        QTimer*              m_pAnim ;
        QPointF              m_pMove ;
        QGraphicsItem*       m_pPrev ;
        QGraphicsItem*       m_pCurr ;
        QGraphicsView*       m_pParent ;
        QGraphicsPixmapItem* m_pFull ;
        QVector<puzzleItem>  m_vSol ;
        puzzleLevel          m_lev ;
        puzzleLevel          m_prev ;
        puzzleLevel          m_about ;
        QList<puzzleLevel>   m_lAdded ;
        QList<puzzleLevel>   m_lLevels ;
        QMediaPlaylist*      m_sndPlaylist ;
        QMediaPlayer         m_sndPlayer ;
} ;
