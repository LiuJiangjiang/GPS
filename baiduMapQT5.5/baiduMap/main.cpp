#include "mainwindow.h"
#include <QApplication>
#include <QtWebEngineWidgets/QWebEngineView>
#include "rewritebaidumaphtml.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  double lat = 40;
  double lng = 115;

  rewritebaidumaphtml(lat, lng);//update the trajectory of vehichle


  QWebEngineView *view = new QWebEngineView;
  //view->load(QUrl("http://www.baidu.com"));

  view->setUrl(QUrl("file:///home/hirain/QT_learning/baiduMap/sources/baidumap_1.html"));
  view->resize(700,550);
  view->show();

  return a.exec();
}
