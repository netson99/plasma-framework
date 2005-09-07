/*****************************************************************
Copyright (c) 2000-2001 Matthias Elter <elter@kde.org>
Copyright (c) 2001 John Firebaugh <jfirebaugh@kde.org>
Copyright (c) 2001-2005 Aaron Seigo <aseigo@kde.org>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Steet, Fifth Floor,
Boston, MA 02110-1301, USA.
******************************************************************/

#include <qfileinfo.h>
#include <kdesktopfile.h>
#include <kapplication.h>

#include "appletinfo.h"

namespace Plasma
{

class AppletInfo::Private
{
    public:
        Private()
            : unique(false),
              hidden(false)
        {}

        QString name;
        QString comment;
        QString icon;
        QString lib;
        QString languageBindings;
        QString desktopFile;
        QString desktopFilePath;
        bool unique;
        bool hidden;
};

AppletInfo::AppletInfo(const QString& desktopFile)
{
    d = new Private;
    QFileInfo fi(desktopFile);
    d->desktopFilePath = fi.absFilePath();
    d->desktopFile = fi.fileName();
    KDesktopFile df(desktopFile, true);

    // set the appletssimple attributes
    setName(df.readName());
    setComment(df.readComment());
    setIcon(df.readIcon());

    // library
    setLibrary(df.readEntry("X-KDE-Library"));

    // language the applet is written in
    setLanguageBindings(df.readEntry("X-KDE-LanguageBindings", "native").toLower());

    // is it a unique applet?
    setUnique(df.readBoolEntry("X-KDE-UniqueApplet", false));

    // should it be shown in the gui?
    d->hidden = df.readBoolEntry("Hidden", false);
}

AppletInfo::AppletInfo(const AppletInfo &copy)
{
    d = new Private;
    *d = *copy.d;
}

AppletInfo::~AppletInfo()
{
    delete d;
}

AppletInfo& AppletInfo::operator=(const AppletInfo &rhs)
{
    *d = *rhs.d;

    return *this;
}

QString AppletInfo::name() const
{
    return d->name;
}

QString AppletInfo::comment() const
{
    return d->comment;
}

QString AppletInfo::icon() const
{
    return d->icon;
}

QString AppletInfo::library() const
{
    return d->lib;
}

QString AppletInfo::languageBindings() const
{
    return d->languageBindings;
}

QString AppletInfo::desktopFilePath() const
{
    return d->desktopFilePath;
}

QString AppletInfo::desktopFile() const
{
    return d->desktopFile;
}

QString AppletInfo::generateConfigFileName() const
{
    // generate a config file base name from the library name
    QString configFile = "plasmaApplet_" + d->lib.lower();

    if (d->unique)
    {
        configFile.append("rc");
    }
    else
    {
        configFile.append("_")
                  .append(kapp->randomString(20).lower())
                  .append("_rc");
    }

    return configFile;
}

bool AppletInfo::unique() const
{
    return d->unique;
}

bool AppletInfo::hidden() const
{
    return d->hidden;
}

void AppletInfo::setName(const QString &name)
{
    d->name = name;
}

void AppletInfo::setComment(const QString &comment)
{
    d->comment = comment;
}

void AppletInfo::setIcon(const QString &icon)
{
    d->icon = icon;
}

void AppletInfo::setLibrary(const QString &lib)
{
   d->lib = lib;
}

void AppletInfo::setLanguageBindings(const QString &language)
{
   d->languageBindings = language;
}

void AppletInfo::setUnique(bool u)
{
    d->unique = u;
}

bool AppletInfo::operator!=(const AppletInfo& rhs) const
{
    return library() != rhs.library();
}

bool AppletInfo::operator==(const AppletInfo& rhs) const
{
    return library() == rhs.library();
}

bool AppletInfo::operator<(const AppletInfo& rhs) const
{
    return name().lower() < rhs.name().lower();
}

bool AppletInfo::operator>(const AppletInfo& rhs) const
{
    return name().lower() > rhs.name().lower();
}

bool AppletInfo::operator<=(const AppletInfo& rhs) const
{
    return name().lower() <= rhs.name().lower();
}

} // Plasma namespace
