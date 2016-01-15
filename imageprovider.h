#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QDebug>

#include "abstractdatamanager.h"

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider(pAbstractDataManager dataManager)
        : QQuickImageProvider(QQuickImageProvider::Image)
        , m_dataManager(dataManager)
    {}

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)
    {
        Q_UNUSED(size)
        Q_UNUSED(requestedSize)

        return m_dataManager->GetImage(id);
    }

private:
    pAbstractDataManager m_dataManager;
};

#endif // IMAGEPROVIDER_H
