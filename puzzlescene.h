#pragma once

#include <QGraphicsScene>

struct puzzleItem {
    QPoint               ptPos ;
    QGraphicsPixmapItem* pItem ;
} ;

class puzzleScene : public QGraphicsScene
{
    public :
        puzzleScene( QGraphicsView *parent = nullptr) ;
        bool doPuzzle( const QString szFile, int nDiv) ;
        bool showSol( bool bShow) ;

    protected :
        void mousePressEvent( QGraphicsSceneMouseEvent* pEvent) ;

    private :
        bool isSolved() ;
        void reset() ;

    private :
        QGraphicsItem*       m_pPrev ;
        QGraphicsView*       m_pParent ;
        QGraphicsPixmapItem* m_pFull ;
        QVector<puzzleItem>  m_vSol ;
} ;
