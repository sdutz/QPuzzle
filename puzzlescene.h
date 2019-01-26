#pragma once

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
    public :
        puzzleScene( QGraphicsView *parent = nullptr) ;
        bool start( int nDiv) ;
        bool next() ;
        bool showSol( bool bShow) ;
        void addImage( const QString& szImg) ;

    protected :
        void mousePressEvent( QGraphicsSceneMouseEvent* pEvent) ;

    private :
        bool doPuzzle( int nDiv, const QString& szImg) ;
        bool isSolved() ;
        void reset() ;

    private :
        QGraphicsItem*       m_pPrev ;
        QGraphicsView*       m_pParent ;
        QGraphicsPixmapItem* m_pFull ;
        QVector<puzzleItem>  m_vSol ;
        QList<puzzleLevel>   m_lLevels ;
} ;
