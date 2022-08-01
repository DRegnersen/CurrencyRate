#ifndef CACHE_H
#define CACHE_H

#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTextStream>

#include "Archive.h"

const QString FILENAME = "ARC.CACHE";

class Cache {
   public:
    Cache(QString filename = FILENAME);

    Cache(Archive source, QString filename = FILENAME);

    void set_archive(Archive arc);

    Archive get_archive();

    void save();

    void load();

    bool isEmpty();

    unsigned long long size();

   private:
    QFile file_;

    Archive arc_;
};

#endif  // CACHE_H
