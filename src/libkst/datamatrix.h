/***************************************************************************
 *                                                                         *
 *   copyright : (C) 2007 The University of Toronto                        *
 *   copyright : (C) 2005  University of British Columbia                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DATAMATRIX_H
#define DATAMATRIX_H

#include "kstmatrix.h"
#include "kstsharedptr.h"
#include "kstdatasource.h"
#include "kst_export.h"

namespace Kst {
   
class KST_EXPORT DataMatrix : public KstMatrix {

  public:
    
    // constructor
    DataMatrix(KstDataSourcePtr file, const QString &field, KstObjectTag tag,
               int xStart, int yStart,
               int xNumSteps, int yNumSteps,
               bool doAve, bool doSkip, int skip);
    
    // constructor to create a saved DataMatrix
    DataMatrix(const QDomElement &e);
    
    // save DataMatrix
    virtual void save(QTextStream &ts, const QString& indent = QString::null);
    
    virtual ~DataMatrix();
    
    // change properties of DataMatrix
    void change(KstDataSourcePtr file, const QString &field,
                KstObjectTag tag,
                int xStart, int yStart,
                int xNumSteps, int yNumSteps,
                bool doAve, bool doSkip, int skip);
    
    // return properties of DataMatrix
    int reqXStart() const;
    int reqYStart() const;
    int reqXNumSteps() const;
    int reqYNumSteps() const;
    QString filename() const;
    const QString& field() const;
    bool xReadToEnd() const;
    bool yReadToEnd() const;
    bool xCountFromEnd() const;
    bool yCountFromEnd() const;
    bool doSkip() const;
    bool doAverage() const;
    int skip() const;
    
    // labels for this matrix
    virtual QString label() const;
    virtual QString fileLabel() const;
    
    // the data source this DataMatrix is using
    KstDataSourcePtr dataSource() const;
    
    // returns true if the file and field is valid; false otherwise 
    bool isValid() const;
    
    // update DataMatrix
    virtual UpdateType update(int update_counter = -1);

    // reload contents of DataMatrix from file
    void reload();
    
    // change the datasource for this matrix
    void changeFile(KstDataSourcePtr file);
    
    // make a "copy" of this DataMatrix 
    KstSharedPtr<DataMatrix> makeDuplicate() const;
    
  private:
    void commonConstructor(KstDataSourcePtr file, const QString &field,
                           int reqXStart, int reqYStart, int reqNX, int reqNY, 
                           bool doAve, bool doSkip, int skip);
    
    // internal update function, called by update()
    KstObject::UpdateType doUpdate(bool force = false);
    
    bool doUpdateSkip(int realXStart, int realYStart, bool force);
    bool doUpdateNoSkip(int realXStart, int realYStart, bool force);
    
    void reset();
    
    // values requested; may be different from actual matrix range
    int _reqXStart, _reqYStart, _reqNX, _reqNY; 
    
    // matrix params since last update - used to determine if update is needed
    int _lastXStart, _lastYStart, _lastNX, _lastNY;
    bool _lastDoAve : 1;
    bool _lastDoSkip : 1;
    int _lastSkip;
    
    double* _aveReadBuffer; // buffer used when performing boxcar filter
    int _aveReadBufferSize; 
    
    KstDataSourcePtr _file;
    QString _field; // field to read from _file
    bool _doAve : 1;
    bool _doSkip : 1;
    int _skip;
    int _samplesPerFrameCache; // cache the samples per frame of the field in datasource
};

typedef KstSharedPtr<DataMatrix> DataMatrixPtr;
typedef KstObjectList<DataMatrixPtr> DataMatrixList;

}
#endif
// vim: ts=2 sw=2 et