#pragma once

#include <QMainWindow>
#include <QSettings>
#include "puzzlescene.h"

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

    private slots :
        void add() ;
        void next() ;
        void start() ;
        void keyPressEvent( QKeyEvent* pEvent) ;
        void resizeEvent( QResizeEvent* pEvent) ;

    private :
        void createActions() ;

    private :
        Ui::PuzzleWnd *ui ;
        puzzleScene* m_pScene ;
        QSettings    m_set ;
        QAction*     m_pAdd ;
        QAction*     m_pNext ;
        QAction*     m_pStart ;
} ;
