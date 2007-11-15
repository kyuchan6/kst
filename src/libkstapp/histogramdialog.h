/***************************************************************************
 *                                                                         *
 *   copyright : (C) 2007 The University of Toronto                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H

#include "datadialog.h"
#include "datatab.h"

#include "histogram.h"

#include "ui_histogramtab.h"

#include <QPointer>

#include "kst_export.h"

namespace Kst {

class KST_EXPORT HistogramTab : public DataTab, Ui::HistogramTab {
  Q_OBJECT
  public:
    HistogramTab(QWidget *parent = 0);
    virtual ~HistogramTab();

    void setObjectStore(ObjectStore *store);

    VectorPtr vector() const;
    void setVector(VectorPtr vector);

    double min() const;
    void setMin(const double min);

    double max() const;
    void setMax(const double max);

    int bins() const;
    void setBins(const int bins);

    bool realTimeAutoBin() const;
    void setRealTimeAutoBin(const bool autoBin);

    Histogram::NormalizationType normalizationType() const;
    void setNormalizationType(const Histogram::NormalizationType normalizationType);

    CurveAppearance* curveAppearance() const;
    CurvePlacement* curvePlacement() const;

    void hideCurveOptions();

  private Q_SLOTS:
    void generateAutoBin();
    void updateButtons();
    void selectionChanged();

  Q_SIGNALS:
    void vectorChanged();
};

class KST_EXPORT HistogramDialog : public DataDialog {
  Q_OBJECT
  public:
    HistogramDialog(ObjectPtr dataObject, QWidget *parent = 0);
    virtual ~HistogramDialog();

  protected:
    virtual QString tagString() const;
    virtual ObjectPtr createNewDataObject() const;
    virtual ObjectPtr editExistingDataObject() const;

  private Q_SLOTS:
    void updateButtons();

  private:
    void configureTab(ObjectPtr object);

    HistogramTab *_histogramTab;
};

}

#endif

// vim: ts=2 sw=2 et