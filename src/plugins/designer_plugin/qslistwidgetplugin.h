#include <QDesignerCustomWidgetInterface>
#include <QVariant>

#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QtDesigner/QDesignerContainerExtension>
#if QT_VERSION >= 0x040300
#include <QtDesigner/QDesignerDynamicPropertySheetExtension>
#endif

class QSListWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
    QSListWidgetPlugin(QObject *parent = 0);
    
    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);
    
private:
    bool m_initialized;
};
