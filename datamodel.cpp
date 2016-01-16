#include "datamodel.h"
#include <QDebug>

DataModel::~DataModel()
{
   //delete m_dataManager;
}

bool DataModel::init()
{
    for (auto d : m_dataManager->GetSubjectsList())
    {
        invisibleRootItem()->appendRow(new QStandardItem(d));
    }

    return true; // временно!!!
}

/*bool DataModel::fullInit()
{
    for (auto s : m_dataManager->GetSubjectsList())
    {
        QStandardItem* subject = new QStandardItem(s);
        invisibleRootItem()->appendRow(subject);
        for (auto t : m_dataManager->GetThemesList(s))
        {
            QStandardItem* theme = new QStandardItem(t);
            subject->appendRow(theme);
            for (auto p : m_dataManager->GetImagesList(s, t))
            {
                QStandardItem* image = new QStandardItem(p);
                theme->appendRow(image);
            }
        }
    }

    return true; // временно!!!
}*/

void DataModel::subjectClicked(const QModelIndex& subjectIndex)
{
    auto subjectItem = itemFromIndex(subjectIndex);
    if (subjectItem->hasChildren() && true /* здесь должна быть проверка данных на актуальность! */)
        return;

    QString subjectName = subjectIndex.data(Qt::DisplayRole).toString();
    for (auto d : m_dataManager->GetThemesList(subjectName))
    {
        itemFromIndex(subjectIndex)->appendRow(new QStandardItem(d));
    }
}

void DataModel::themeClicked(const QModelIndex& themeIndex)
{
    auto themeItem = itemFromIndex(themeIndex);
    if (themeItem->hasChildren() && true /* здесь должна быть проверка данных на актуальность! */)
        return;

    QString subjectName = themeItem->parent()->data(Qt::DisplayRole).toString();
    QString themeName = themeIndex.data(Qt::DisplayRole).toString();

    for (auto d : m_dataManager->GetImagesList(subjectName, themeName))
    {
        QImage img = m_dataManager->GetImage(d);
       // img.save(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) +"/"+ d); // for Android
        img.save(QCoreApplication::applicationDirPath()+ "/pictures/" + d); //for linux(windows)
        itemFromIndex(themeIndex)->appendRow(new QStandardItem(d));
    }
}

// всё, что ниже, наверно, можно переделать в одну функцию:

void DataModel::addSubject(const QString& subjectName)
{
    invisibleRootItem()->appendRow(new QStandardItem(subjectName));
}

void DataModel::addTheme(const QModelIndex& subjectIndex, const QString& themeName)
{
    itemFromIndex(subjectIndex)->appendRow(new QStandardItem(themeName));
}

void DataModel::addImage(const QModelIndex& themeIndex, const QString& imageName)
{
    itemFromIndex(themeIndex)->appendRow(new QStandardItem(imageName));
}

/* всё, что ниже, наверно, можно переделать в одну функцию:
 *  void DataModel::delete(const QModelIndex& index)
    {
        itemFromIndex(index.parent())->removeRow(index.row());
    }
 */

void DataModel::deleteSubject(const QModelIndex& subjectIndex)
{
    invisibleRootItem()->removeRow(subjectIndex.row());
}

void DataModel::deleteTheme(const QModelIndex& themeIndex)
{
    itemFromIndex(themeIndex.parent())->removeRow(themeIndex.row());
}

void DataModel::deleteImage(const QModelIndex& imageIndex)
{
    itemFromIndex(imageIndex.parent())->removeRow(imageIndex.row());
}








