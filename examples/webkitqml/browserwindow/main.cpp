#include <QGuiApplication>
#include <QQuickWindow>
#include <QDebug>

#include <private/qquickwebview_p.h>
#include <private/qwebloadrequest_p.h>

static const char* loadStatusToString(QQuickWebView::LoadStatus status)
{
    switch (status) {
    case QQuickWebView::LoadStartedStatus:
        return "started";
    case QQuickWebView::LoadStoppedStatus:
        return "stopped";
    case QQuickWebView::LoadSucceededStatus:
        return "succeeded";
    case QQuickWebView::LoadFailedStatus:
        return "failed";
    }
    return "unknown";
}

class BrowserWindow : public QQuickWindow
{
public:
    BrowserWindow()
    {
        m_webView = new QQuickWebView(contentItem());

        QObject::connect(m_webView, &QQuickWebView::loadingChanged, [](QWebLoadRequest* loadRequest) {
            qDebug() << "loadingChanged:" << loadRequest->url() << loadStatusToString(loadRequest->status()) << loadRequest->errorString() << loadRequest->errorCode() << loadRequest->errorDomain();
        });

        m_webView->setUrl(QUrl("https://qt.io"));
        m_webView->setVisible(true);
        m_webView->setFocus(true);
        m_webView->setSize(size());
    }

protected:
    void resizeEvent(QResizeEvent *) final
    {
        m_webView->setSize(size());
    }

private:
    QQuickWebView *m_webView;
};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    BrowserWindow window;
    window.setMinimumSize(QSize(900, 800));
    window.show();

    return app.exec();
}
