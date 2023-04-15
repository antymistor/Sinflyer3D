#ifndef _SINFLYCHART_H_
#define _SINFLYCHART_H_
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QFontDatabase>
#include <QGridLayout>
#include <QTimer>
#include <QDateTime>

#include <queue>
#include <string>
#include "qcustomplot.h"
struct charttype
{
   QString name;
   QColor backgoundcolor;
   QString yAxisLabel;
   QString xAxisLabel;
   float x_min,x_max,y_min,y_max;
   std::vector<std::pair<QString,QColor>> lines;
};
class sinflyerchart:public QCustomPlot
{
   Q_OBJECT
   public:
      sinflyerchart();
      sinflyerchart(charttype &ct_,int index_=1);
      void updatechartstyle(void);
      void setchartstyle(charttype &ct_);
      void setheadindex(const unsigned int& index_);
      
      std::queue<std::string> updatestrs;
   private:
      const static int updatetime=30;     //units ms
      charttype ct;
      unsigned int num_of_lines;
      unsigned int index_of_head;

      QTimer tm_;

   private slots:
      void slotTimeout_();
};

#endif