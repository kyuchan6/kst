/***************************************************************************
 *                                                                         *
 *   copyright : (C) 2003 The University of Toronto                        *
*                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

#include "datasource.h"
#include "string_kst.h"
#include "vector.h"
#include "matrix.h"
#include "kst_export.h"
#include "objectcollection.h"

class QFile;

namespace Kst {

class Relation;
class PlotItemInterface;

class Data {
  protected:
    static Data *_self;
    static void cleanup();
    Data();
    virtual ~Data();

  public:
    static Data *self();
    static void replaceSelf(Data *newInstance);

    /** check that a tag has not been used by any other tags */
    virtual bool tagNameNotUnique(const QString& tag, bool warn = true, void *parent = 0L);
    virtual bool dataTagNameNotUnique(const QString& tag, bool warn = true, void *parent = 0L);
    virtual bool vectorTagNameNotUnique(const QString& tag, bool warn = true, void *parent = 0L);
    virtual bool vectorTagNameNotUniqueInternal(const QString& tag);
    virtual bool matrixTagNameNotUnique(const QString& tag, bool warn = true, void *parent = 0L);
    virtual bool matrixTagNameNotUniqueInternal(const QString& tag);
    virtual bool dataSourceTagNameNotUnique(const QString& tag, bool warn = true, void *parent = 0L);

    virtual bool viewObjectNameNotUnique(const QString& tag);

    virtual void removeCurveFromPlots(Relation *c); // no sharedptr here

    /** Save a vector to a file */
    virtual int vectorToFile(VectorPtr v, QFile *f);
    virtual int vectorsToFile(const VectorList& l, QFile *f, bool interpolate);

    /** The list of plots for the current view. */
    virtual QList<PlotItemInterface*> plotList() const;

    /** Returns the number of rows in the current view's layout.
      * -1 if not in layout.
      */
    virtual int rows() const;

    /** Returns the number of columns in the given view's layout.
      * -1 if not in layout.
      */
    virtual int columns() const;
} KST_EXPORT;

    /** The list of data sources (files) */
    KST_EXPORT extern DataSourceList dataSourceList;

    /** The list of vectors that are being read */
    KST_EXPORT extern VectorCollection vectorList;

    /** The list of Scalars which have been generated */
    KST_EXPORT extern ScalarCollection scalarList;

    /** The list of Strings */
    KST_EXPORT extern StringCollection stringList;

    /** The list of matrices that are being read */
    KST_EXPORT extern MatrixCollection matrixList;

    /** Bad choice for location - maybe move it later */
    KST_EXPORT void *malloc(size_t size);
    KST_EXPORT void *realloc(void *ptr, size_t size);

}

#endif
// vim: ts=2 sw=2 et