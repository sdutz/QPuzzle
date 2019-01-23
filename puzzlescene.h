#pragma once

#include <QGraphicsScene>

class puzzleScene : public QGraphicsScene
{
    public :
        puzzleScene( QGraphicsView *parent = nullptr) ;
        bool doPuzzle( const QString szFile, int nDiv) ;

    protected :
        void mousePressEvent( QGraphicsSceneMouseEvent* pEvent) ;

    private :
        QGraphicsItem* m_pPrev ;
        QGraphicsView* m_pParent ;
        QGraphicsPixmapItem* m_pFull ;
} ;
