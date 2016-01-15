#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QStandardItemModel>

#include "abstractdatamanager.h"

class DataModel : public QStandardItemModel
{
    Q_OBJECT

public:
    DataModel(pAbstractDataManager dataManager)
        : QStandardItemModel()
        , m_dataManager(dataManager)
    { }

    ~DataModel();

    //внутри функции надо добавить обработку ошибок:
    bool init();
    //bool fullInit();

    void addSubject(const QString& subjectName);
    void addTheme(const QModelIndex& subjectIndex, const QString& themeName);
    void addImage(const QModelIndex& themeIndex, const QString& imageName);

    // см.комментарий по эти функциям в .cpp
    void deleteSubject(const QModelIndex& subjectIndex);
    void deleteTheme(const QModelIndex& themeIndex);
    void deleteImage(const QModelIndex& imageIndex);

public slots:
    // внутри функций надо добавить обработку ошибок:
    void subjectClicked(const QModelIndex& subjectIndex);
    void themeClicked(const QModelIndex& themeIndex);

private:
    pAbstractDataManager m_dataManager;
};

#endif // DATAMODEL_H
