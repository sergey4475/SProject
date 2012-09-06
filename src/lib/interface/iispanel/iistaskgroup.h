#ifndef IISTASKGROUP_H
#define IISTASKGROUP_H

#include <QtGui>

//#include "iistaskpanel_global.h"
#include "lib_global.h"

class iisTaskPanelScheme;
struct iisIconLabelScheme;

class iisIconLabel;

class LIBSHARED_EXPORT iisTaskGroup : public QFrame
{
  Q_OBJECT

public:
  iisTaskGroup(QWidget *parent, bool hasHeader = false);
  virtual ~iisTaskGroup();

  void setScheme(iisTaskPanelScheme *scheme);

  inline QBoxLayout* groupLayout()
  {
    return (QBoxLayout*)layout();
  }

  void addIconLabel(iisIconLabel *label, bool addToLayout = true);

  QPixmap transparentRender();

protected:
  virtual void paintEvent ( QPaintEvent * event );
  virtual void keyPressEvent ( QKeyEvent * event );
  virtual void keyReleaseEvent ( QKeyEvent * event );

  iisTaskPanelScheme *myScheme;
  iisIconLabelScheme *myLabelScheme;

  bool myHasHeader;
};

#endif // IISTASKGROUP_H