/*
 * properties.h
 * Copyright 2010, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 *
 * This file is part of libtiled.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "tiled_global.h"

#include <QMap>
#include <QString>

namespace Tiled {

/**
 * Collection of properties and their values.
 */
class TILEDSHARED_EXPORT Properties : public QMap<QString,QString>
{
public:
    void merge(const Properties &other);
};

class TILEDSHARED_EXPORT AggregatedPropertyData
{
public:
    explicit AggregatedPropertyData(const QString &value)
        : mValue(value)
        , mPresenceCount(1)
        , mValueConsistent(true)
    {}

    void aggregate(const QString &value)
    {
        mValueConsistent &= value == mValue;
        mPresenceCount += 1;
    }

    const QString &value() const { return mValue; }
    int presenceCount() const { return mPresenceCount; }
    bool valueConsistent() const { return mValueConsistent; }

private:
    QString mValue;
    int mPresenceCount;
    bool mValueConsistent;
};

/**
 * Collection of properties with information about the consistency of their
 * presence and value over several property collections.
 */
class TILEDSHARED_EXPORT AggregatedProperties : public QMap<QString, AggregatedPropertyData>
{
public:
    void aggregate(const Properties &properties);
    int aggregatedCount() { return mAggregatedCount; }

private:
    int mAggregatedCount;
};


} // namespace Tiled

#endif // PROPERTIES_H