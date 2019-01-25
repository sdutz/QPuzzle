#pragma once

#include <QGraphicsScene>

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
        bool doPuzzle() ;
        bool isSolved() ;
        void reset() ;

    private :
        int                  m_nDiv ;
        QGraphicsItem*       m_pPrev ;
        QGraphicsView*       m_pParent ;
        QGraphicsPixmapItem* m_pFull ;
        QVector<puzzleItem>  m_vSol ;
        QStringList          m_lsGallery ;
} ;
